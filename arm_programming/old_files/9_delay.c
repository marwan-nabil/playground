#include "delay.h"

void delay(int iterations){
    volatile int counter = 0;
    while(counter < iterations){
        ++counter;
    }
}