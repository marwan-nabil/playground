int counter = 0;
int main()
{
    int *p_int = &counter;
    while(*p_int < 21)
    {
        (*p_int)++;
    }
    
    p_int = (int *) 0x20000002;
    *p_int = 0xCAFEBABE;
    
    return 0;
}
