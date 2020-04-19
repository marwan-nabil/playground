#include "lm4f120h5qr.h"

//// memory-mapped register that controls GPIO power state
//#define RCGCGPIO (*((unsigned int *) 0x400FE608))
//// GPIO port F's memory base address
//#define GPIOF_BASE 0x40025000
//// GPIO port F's data direction register
//#define GPIOF_DDIR (*((unsigned int *) (GPIOF_BASE + 0x400)))
//// GPIO port F's digital enable register
//#define GPIOF_DEN (*((unsigned int *) (GPIOF_BASE + 0x51C)))
//// GPIO port F's data register
//#define GPIOF_DATA (*((unsigned int *) (GPIOF_BASE + 0x3FC)))

int main()
{
    // enable the GPIO port F
    SYSCTL_RCGCGPIO_R = 0x00000020;
    // set GPIO port F's data direction as output for 3 pins
    GPIO_PORTF_DIR_R = 0x0000000e;
    // set GPIO port F's digital enable for 3 bits
    GPIO_PORTF_DEN_R = 0x0000000e;
    
    // blink LED with color red
    while(1)
    {
        // turn on
        GPIO_PORTF_DATA_R = 0x00000020;
        // wait a little while
        for(volatile int i =0; i<1000000; i++){
            ;
        }
        // turn off
        GPIO_PORTF_DATA_R = 0x00000000;
        // wait a little while
        for(volatile int i =0; i<1000000; i++){
            ;
        }
    }
    
    return 0;
}
