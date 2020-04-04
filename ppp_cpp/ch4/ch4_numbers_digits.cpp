#include "std_lib_facilities.h"

int main() {
	vector<string> numbers = { "zero","one","two","three","four","five","six","seven","eight","nine" };
	string input;
	cout << "enter a number or a digit  : ";
	int index;
	while (cin >> input) {
		if (input.size() == 1) {
			index = stoi(input);
			input = numbers[index];
			cout << "\nthe number is : " << input;
		}
		else {
			int i = 0;
			for (string s : numbers) {
				if (input == s) {
					cout << "\nthe digit is " << i;
					break;
				}
				i++;
			}
		}

		cout << "\nenter another number or digit  : ";
	}
	return 0;
}