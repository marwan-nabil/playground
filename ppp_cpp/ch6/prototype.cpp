// implementing a simple calculator using a traditional arithmetic grammar
// i'll make a simple lexer and a recursive descent parser for the input
#include "std_lib_facilities.h"

// lexer stuff
enum token_kind {NUMBER, PLUS, MINUS, MUL, DIV, OPEN_PAREN, CLOSE_PAREN, END_INPUT};

class Token {
public:
  enum token_kind kind;
  double value;
};

Token get_token()
{
  
}

// parser stuff

double expression()
{
  
}

double term()
{
  
}

double primary()
{
  
}


int main()
{
  vector<Token> token_buffer;
  // store all tokenn first
  while(cin)
	{
	  token_buffer.push_back(get_token());
	}
  return 0;
}
