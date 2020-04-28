#include "std_lib_facilities.h"

vector<int> primes;
bool check_primacy(int n);

int main() {
	int max = 0;
	cout << "enter a max for prime detector : ";
	cin >> max;
	primes = { 2 };
	for (int i = 2; i <= max; i++) {
		check_primacy(i);
	}
	for (unsigned int i = 0; i < primes.size(); i++)
		cout << primes[i] << " \n";
	return 0;
}

bool check_primacy(int n) {
	for (int i : primes) {
		if (n%i == 0 )
			return false;
	}
	primes.push_back(n);
	return true;
}