#include "std_lib_facilities.h"
int main() {
	vector<int> primes;
	int p = 2;
	int max=0;
	int pindex=0;
	bool end = false;
	cout << "enter the max for prime detector : ";
	cin >> max;
	// filling out our initial list
	for (int i = 2; i <= max; i++)
		primes.push_back(i);
	// marking non-primes by zeroing
	while(!end){

		for (int j=pindex+p; j < primes.size();j+=p) {
			primes[j] = 0; // number marked
		}

		for (int i = 0; i < primes.size(); i++) {
			if (primes[i] != 0 && primes[i]>p) {
				p = primes[i];
				pindex = i;
				break;
			}
			else if (i == primes.size() - 1)
				end = true;
		}
	}

	for (int i : primes) {
		if (i != 0) {
			cout << i << "\n";
		}
	}
	return 0;
}