#include "std_lib_facilities.h"

int main() {
	cout << "enter two real operands followed by an operator (+  -  *  /): ";
	double o1, o2, result;
	string operation;
	char op;
	cin >> o1 >> o2 >> op;
	switch (op) {
	case '+':
		operation = "sum";
		result = o1 + o2;
		break;
	case '-':
		operation = "difference";
		result = o1 - o2;
		break;
	case '*':
		operation = "multiplication";
		result = o1 * o2;
		break;
	case '/':
		operation = "ratio";
		result = o1 / o2;
		break;
	default:
		simple_error("\nplease enter a valid operator !!\n");
	}
	cout << "\nthe result of the " << operation << " of " << o1 << " " << op << " " << o2 <<" is : " << result;
	return 0;
}
