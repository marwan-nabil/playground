#include "delay.h"

void delay(volatile int iterations){
    while(iterations > 0){
        --iterations;
    }
}