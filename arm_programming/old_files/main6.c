#include "lm4f120h5qr.h"

#define RED_LED     (1U<<1)
#define BLUE_LED    (1U<<2)
#define GREEN_LED   (1U<<3)

int main()
{
    // enable the GPIO port F (clock gating control register)
    SYSCTL_RCGCGPIO_R |= 0x00000020;
    // set GPIO port F's data direction as output for 3 pins
    GPIO_PORTF_DIR_R |= 0x0000000e;
    // set GPIO port F's digital enable for 3 bits
    GPIO_PORTF_DEN_R |= 0x0000000e;
    
    // turn on the blue led
    GPIO_PORTF_DATA_R |= BLUE_LED;
    // blink the red led
    while(1)
    {
        // turn on
        GPIO_PORTF_DATA_R |= RED_LED;
        // wait a little while
        for(volatile int i =0; i<1000000; i++){
            ;
        }
        // turn off
        GPIO_PORTF_DATA_R &= ~RED_LED;
        // wait a little while
        for(volatile int i =0; i<1000000; i++){
            ;
        }
    }
    
    return 0;
}
