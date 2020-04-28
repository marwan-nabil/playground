#include "std_lib_facilities.h"
int main() {
	string s1, s2;
	int o1, o2;
	int result;
	string operation;
	char op;
	vector<string> numbers = { "zero","one","two","three","four","five","six","seven","eight","nine" };

	cout << "enter two single digit or number operands followed by an operator (+  -  *  /): ";
	cin >> s1 >> s2 >> op;

	// converting the operands to proper integers
	if (s1.size() == 1) {
		o1 = stoi(s1);
	}
	else {
		int i = 0;
		for (string s : numbers) {
			if (s1 == s) {
				o1 = i;
				break;
			}
			i++;
		}
	}

	if (s2.size() == 1) {
		o2 = stoi(s2);
	}
	else {
		int i = 0;
		for (string s : numbers) {
			if (s2 == s) {
				o2 = i;
				break;
			}
			i++;
		}
	}

	// switching over the operations
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
	cout << "\nthe result of the " << operation << " of " << o1 << " " << op << " " << o2 << " is : " << result;



	return 0;
}