#include "lm4f120h5qr.h"
#include "delay.h"

#define RED_LED     (1U<<1)
#define BLUE_LED    (1U<<2)
#define GREEN_LED   (1U<<3)

unsigned fact(unsigned n);
void mcu_setup(void);
int *swap(int *x, int *y);


int main()
{
    mcu_setup();
    
    // play with recursive function fact()
    // unsigned x = fact(0);
    // x = 2U + 3U * fact(1U);
    // this call causes a write beyond array bounds and
    // invalidates the LR (return address) of the function
    // (void) fact(7U);
    
    // turn on the blue led
    GPIO_PORTF_AHB_DATA_BITS_R[BLUE_LED] = BLUE_LED;
    
    // blink the red led
    while(1)
    {
        // try swap
        int x = 1000000, y = 1000000 / 2;
        // p : pointer to array that holds old x & y values
        int *p = swap(&x, &y);
        
        // turn on
        // this time we use bit-addressing with array indexing syntax
        GPIO_PORTF_AHB_DATA_BITS_R[RED_LED] = RED_LED;
        // wait a little while
        delay(p[0]);
        // turn off
        GPIO_PORTF_AHB_DATA_BITS_R[RED_LED] = 0;
        // wait a little while
        delay(p[1]);
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


unsigned fact(unsigned n){
    // stack breaking modification
    // unsigned foo[100];
    
    unsigned foo[6];
    // no array bounds checking could result in corruption of stack
    // on values of n > 5
    foo[n] = n;
    
    if(n == 0U)
    {
        return 1U;
    }
    else
    {
        return foo[n] * fact(n - 1U);
    }
}


int *swap(int *x, int *y){
    // global variable, persistent through calls
    static int tmp[2];
    tmp[0] = *x;
    tmp[1] = *y;

    *x = tmp[1];
    *y = tmp[0];
    return tmp;
}

