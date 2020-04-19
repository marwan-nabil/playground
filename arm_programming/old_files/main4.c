int main()
{
    // address of a memory-mapped register that 
    // controls GPIO port F's power state
    unsigned int *p_GPIOF_clock_gate_register = (unsigned int *) 0x400FE608;
    // address of GPIO port F's data direction register
    unsigned int *p_GPIOF_direction_register = (unsigned int *) 0x4002551c;
    // address of GPIO port E's data direction register
    unsigned int *p_GPIOE_direction_register = (unsigned int *) 0x40025400;
    // address of GPIO port F's data register
    unsigned int *p_GPIOF_data_register =  (unsigned int *) 0x400253fc;
    
    // enable the GPIO port F
    *p_GPIOF_clock_gate_register = 0x00000020;
    // set GPIO port F's data direction as output for 3 pins
    *p_GPIOF_direction_register = 0x0000000e;
    // set GPIO port E's data direction as output for 3 pins
    *p_GPIOE_direction_register = 0x0000000e;
    
    // blink LED with color red
    while(1)
    {
        // turn on
        *p_GPIOF_data_register = 0x00000020;
        // wait a little while
        for(int i =0; i<1000000; i++){
            ;
        }
        // turn off
        *p_GPIOF_data_register = 0x00000000;
        // wait a little while
        for(int i =0; i<1000000; i++){
            ;
        }
    }
    
    return 0;
}
