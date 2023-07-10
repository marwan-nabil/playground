//             [ (   (   {  )                 ]
// top:                  ^


// (  (   )  }   )

int main()
{
    char last_paren;
    char last_curly;

    char *array = " {    (  {  }   )  }   ";

    // stack stack1;
    push(stack1, array[0]);

// stack1 =   [  {                    ]
// top:          ^

    char stack_top = peek();
    char next_char = array[1];

    if(next_char == '(')
    {
        if(stack_top == '}' || stack_top == ')')
        {
            return false;
        }
    }

    if(last_paren == '(' && last_curly == ')')
    {
                
    }
    else if(last == '(')
    {

    }
    else if(last == ')')
    {

    }


    if(element_to_push == ')')
    {
        last_paren = ')';
    }

}