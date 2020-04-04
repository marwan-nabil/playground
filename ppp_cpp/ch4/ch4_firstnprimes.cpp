#include "std_lib_facilities.h"

vector<int> primes;
bool check_primacy(int n);


int main() {
	cout << "enter the number of primes you want to get : ";
	int n = 0;
	cin >> n;
	int i = 2;
	primes = { 2 };
	while (primes.size() < n) {
		check_primacy(i);
		i++;
	}

	for (unsigned int i = 0; i < primes.size(); i++)
		cout << primes[i] << " \n";
	return 0;
}


bool check_primacy(int n) {
	for (int i : primes) {
		if (n%i == 0)
			return false;
	}
	primes.push_back(n);
	return true;
}