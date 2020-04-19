#include <stdint.h>
#include "CMSIS/tm4c_cmsis.h"

/* LED bits positions on the GPIO port */
#define RED_LED     (1U<<1)
#define BLUE_LED    (1U<<2)
#define GREEN_LED   (1U<<3)

/* powers up GPIO port F and configures it for output */
void mcu_setup(void);
/* introduces a spin-lock delay */
void delay(volatile int iterations);


typedef struct {
    uint16_t x;
    uint8_t  y;
} Point;

typedef struct {
    Point top_left;
    Point bottom_right;
} Window;

typedef struct {
    Point corners[3];
} Triangle;

Point p1, p2;
Window w;
Triangle t;

/* entry point */
int main()
{
    p1.x = sizeof(Point);
    p1.y = 0xAAU;
    
    mcu_setup();
    
    // turn on the blue led
    GPIOF_HS->DATA_Bits[BLUE_LED] = BLUE_LED;
    
    // blink the red led
    while(1)
    {
        // turn on
        // use bit-addressing with array indexing syntax
        GPIOF_HS->DATA_Bits[RED_LED] = RED_LED;
        // wait a little while
        delay(1000000);
        // turn off
        GPIOF_HS->DATA_Bits[RED_LED] = 0;
        // wait a little while
        delay(500000);
    }
    
    // return 0;
}


void mcu_setup(){
    // enable the GPIO port F (clock gating control register)
    SYSCTL->RCGC2 |= 0x00000020;
    // enable AHB for GPIO port F
    SYSCTL->GPIOHSCTL = (1U << 5);
    // set GPIO port F's data direction as output for 3 pins
    GPIOF_HS->DIR |= 0x0000000e;
    // set GPIO port F's digital enable for 3 bits
    GPIOF_HS->DEN |= 0x0000000e;
}


void delay(volatile int iterations){
    while(iterations > 0){
        --iterations;
    }
}
