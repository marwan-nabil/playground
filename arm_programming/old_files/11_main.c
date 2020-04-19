#include <stdint.h>
#include "lm4f120h5qr.h"
#include "delay.h"

#define RED_LED     (1U<<1)
#define BLUE_LED    (1U<<2)
#define GREEN_LED   (1U<<3)


void mcu_setup(void);


// experiments with standard int types
uint8_t     u8a,    u8b;
uint16_t    u16c,   u16d;
uint32_t    u32e,   u32f;

int8_t     s8;
int16_t    s16;
int32_t    s32;


int main()
{
    u8a     = sizeof(u8a);
    u16c    = sizeof(u16c);
    u32e    = sizeof(u32e);
    
    u8a  = 0xa1U;
    u16c = 0xc1c2U;
    u32e = 0xe1e2e3e4U;
    
    u8b     = u8a;
    u16d    = u16c;
    u32f    = u32e;
    
    // integer promotion
    u16c = 40000u;
    u16d = 50000u;
    // u32e = u16c + u16d; // causes unsigned overflow on 16-bit machines
    // solution for u16 overflow
    u32e = (uint32_t) u16c + u16d; // the other operand would be promoted to u32
    
    // implicit signed to unsigned cast
    u16c = 100;
    // all rhs operands are implicitly cast to u32 on 32-bit machines
    // before subtraction, then recast to s32 before assignment
    // this produces unexpected result on 16-bit machines
    // where rhs is implicitly cast to u16 before subtraction
    // then zero extended and cast to s32 before assignment
    // s32  = 10 - u16c;
    s32  = 10 - (int16_t) u16c; // solution: make the whole operation signed
    
    // implicit signed to unsigned cast causes problems
    // if(u32e > -1) // always false
    if((int32_t) u32e > -1) // solution: don't mix signed and unsigned
    {
        u8a = 1U;
    }
    else
    {
        u8a = 0U;
    }
    
    u8a = 0xFFU;
    // u8a in promoted first to u32, then will be complemented producing
    // 0xffffff00 causing the whole expression to be always false
    // if(~u8a == 0x00U)
    if((uint8_t) (~u8a) == 0x00U) // solution: reverse cast the complement to u8
    {
        u8b = 1U;
    }
    
    mcu_setup();
    
    // turn on the blue led
    GPIO_PORTF_AHB_DATA_BITS_R[BLUE_LED] = BLUE_LED;
    
    // blink the red led
    while(1)
    {
        // turn on
        // use bit-addressing with array indexing syntax
        GPIO_PORTF_AHB_DATA_BITS_R[RED_LED] = RED_LED;
        // wait a little while
        delay(1000000);
        // turn off
        GPIO_PORTF_AHB_DATA_BITS_R[RED_LED] = 0;
        // wait a little while
        delay(500000);
    }
    
    // return 0;
}


void mcu_setup(){
    // enable the GPIO port F (clock gating control register)
    SYSCTL_RCGCGPIO_R |= 0x00000020;
    // enable AHB for GPIO port F
    SYSCTL_GPIOHBCTL_R = (1U << 5);
    // set GPIO port F's data direction as output for 3 pins
    GPIO_PORTF_AHB_DIR_R |= 0x0000000e;
    // set GPIO port F's digital enable for 3 bits
    GPIO_PORTF_AHB_DEN_R |= 0x0000000e;
}
