#include "lm4f120h5qr.h"
#include "delay.h"

#define RED_LED     (1U<<1)
#define BLUE_LED    (1U<<2)
#define GREEN_LED   (1U<<3)

unsigned fact(unsigned n);


int main()
{
    // play with recursive function
    unsigned x = fact(0);
    x = 2U + 3U * fact(1U);
    (void) fact(5U);
    
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


unsigned fact(unsigned n){
    if(n == 0U)
    {
        return 1U;
    }
    else
    {
        return n * fact(n - 1U);
    }
}


