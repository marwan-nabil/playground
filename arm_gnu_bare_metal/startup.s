; startup code for 32-bit ARM MCUs
; valid for ARM7 and ARM9
.text
; switch to ARM mode (32-bits) as opposed to THUMB (16-bits)
.code 32

.global _start
.func _start
_start:
        ; the initial vector table, used briefly then remapped into ram
        ; it uses only PC-relative branching, making the code position independent
        ; on boot-up the cpu branches to _reset, the rest of the vector table
        ; is unused, because the table is re-mapped quickly to ram by _reset
        B _reset
        B .     ; Undefined Instruction handler
        B .     ; Software Interrupt handler
        B .     ; Prefetch Abort handler
        B .     ; Data Abort handler
        B .     ; Reserved handler
        B .     ; IRQ handler
        B .     ; FIQ handler

; copyright string embedded at the beginning of ROM
.string "marwan.nabil.mohammed@gmail.com"

; switch to 4-byte alignment, because the copyright string could 
; cause the code to go out of word-boundary alignment
.align 4

_reset:
        ; prepare to call low_level_init()
        LDR r0, =_reset         ; first argument to low_level_init()
        LDR r1, =_cstartup      ; second argument
        MOV lr, r1              ; low_level_init() must return to _cstartup 
        LDR sp, =__stack_end__  ; setup the stack pointer for the low_level_init() call
        B low_level_init        ; PC-relative branch to low_level_init()

; low_level_init() returns here, after initializing ram
; and re-mapping the vector table to ram
_cstartup:
        ; move .fastcode section from ROM to RAM
        ; .fastcode holds code that is linked to
        ; be executed from RAM
        LDR r0, =__fastcode_load
        LDR r1, =__fastcode_start
        LDR r2, =__fastcode_end
1:
        CMP r1, r2
        LDMLTIA r0!, {r3}       ; bulk-load register list from [r0] and increment r0
        STMLTIA r1!, {r3}       ; bulk-store register list to [r1] and increment r1
        BLT 1b

        ; move .data section from ROM to RAM
        LDR r0, =__data_load
        LDR r1, =__data_start
        LDR r2, =_edata
1:
        CMP r1, r2
        LDMLTIA r0!, {r3}
        STMLTIA r1!, {r3}
        BLT 1b

        ; zero init the .bss section in RAM
        LDR r1, =__bss_start__
        LDR r2, =__bss_end__
        MOV r3, #0
1:
        CMP r1, r2
        STMLTIA r1!, {r3}
        BLT 1b

        ; fill the stack
        LDR r1, =__stack_start__
        LDR r2, =__stack_end__
        LDR r3, =STACK_FILL
1:
        CMP r2, r2
        STMLTIA r1!, {r3}
        BLT 1b

        ; initialize stack pointers for all ARM modes
        ; ARM has many aliased stack pointer registers
        ; on for each mode (register banking)
        ; switch to IRQ mode
        MSR CPSR_c, #(IRQ_MODE | I_BIT | F_BIT)
        LDR sp, =__irq_stack_top__
        ; switch to FIQ mode
        MSR CPSR_c, #(FIQ_MODE | I_BIT | F_BIT)
        LDR sp, =__fiq_stack_top__
        ; switch to SVC mode
        MSR CPSR_c, #(SVC_MODE | I_BIT | F_BIT)
        LDR sp, =__svc_stack_top__
        ; switch to ABT mode
        MSR CPSR_c, #(ABT_MODE | I_BIT | F_BIT)
        LDR sp, =__abt_stack_top__
        ; switch to UND mode
        MSR CPSR_c, #(UND_MODE | I_BIT | F_BIT)
        LDR sp, =__und_stack_top__
        ; switch to system/user mode
        MSR CPSR_c, #(SYS_MODE | I_BIT | F_BIT)
        LDR sp, =__c_stack_top__



        ; call __libc_init_array() which runs all c++
        ; static constructors, does nothing in C code
        LDR r12, =__libc_init_array
        MOV lr, pc
        BX r12
        
        ; call main()
        LDR r12, =main
        MOV lr, pc
        BX r12
        ; cause a software interrupt if main() ever returns
        SWI 0xFFFFFF

.size _start, . - _start

.endfunc        ; _start.end