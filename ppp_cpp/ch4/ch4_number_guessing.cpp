#include "std_lib_facilities.h"

int main() {
	cout << "think about a number from 1 to 100 : ";
	double half = 50;
	double range = 100;
	char choice=NULL;

	while (range>0.78125) {
		cout << "\nis the number over or equal to " << half << " \"o\" or under " << half << " \"u\" ? : ";
		cin >> choice;
		if (choice == 'o') {
			range /= 2.0; // the new range after some choice
			half = half + range / 2.0; // the new half after an over choice
		}
		else if (choice == 'u') {
			range /= 2; // the new range after some choice
			half = half - range / 2.0; // the new half after an under choice
		}
		else
			simple_error("\nYou should always enter valid answers ..");
	}
	int guess = half +1 ;
	cout << "\nyour guess is : " << guess;

	return 0;
}