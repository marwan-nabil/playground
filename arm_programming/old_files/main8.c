#include "lm4f120h5qr.h"

#define RED_LED     (1U<<1)
#define BLUE_LED    (1U<<2)
#define GREEN_LED   (1U<<3)


void delay(int iterations);


void delay(int iterations){
    volatile int counter = 0;
    while(counter < iterations){
        ++counter;
    }
}


int main()
{
    // enable the GPIO port F (clock gating control register)
    SYSCTL_RCGCGPIO_R |= 0x00000020;
    // enable AHB for GPIO port F
    SYSCTL_GPIOHBCTL_R = (1U << 5);
    // set GPIO port F's data direction as output for 3 pins
    GPIO_PORTF_AHB_DIR_R |= 0x0000000e;
    // set GPIO port F's digital enable for 3 bits
    GPIO_PORTF_AHB_DEN_R |= 0x0000000e;
    
    // turn on the blue led
    GPIO_PORTF_AHB_DATA_BITS_R[BLUE_LED] = BLUE_LED;
    
    // blink the red led
    while(1)
    {
        // turn on
        // this time we use bit-addressing with array indexing syntax
        GPIO_PORTF_AHB_DATA_BITS_R[RED_LED] = RED_LED;
        // wait a little while
        delay(1000000);
        // turn off
        GPIO_PORTF_AHB_DATA_BITS_R[RED_LED] = 0;
        // wait a little while
        delay(1000000);
    }
    
    return 0;
}
