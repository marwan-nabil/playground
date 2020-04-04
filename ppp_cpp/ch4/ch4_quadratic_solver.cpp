#include "std_lib_facilities.h"
int main() {
	cout << "enter the parameters a b c of a quadratic equation : ";
	double a, b, c;
	cin >> a >> b >> c;
	double x1 = (-b + sqrt(b*b-4*a*c)) / 2 * a;
	double x2 = (-b - sqrt(b*b - 4 * a*c)) / 2 * a;
	cout << "\nthe results are x1 = " << x1 << " and x2= " << x2;
	return 0;
}