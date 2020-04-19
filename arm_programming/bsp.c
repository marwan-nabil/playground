/* Board Support Package */
#include "CMSIS/tm4c_cmsis.h"


__stackless void assert_failed(char const *file, int line)
{
    /* damage control functionality here */
    NVIC_SystemReset();
}


void SysTick_Handler(void)
{
    
}