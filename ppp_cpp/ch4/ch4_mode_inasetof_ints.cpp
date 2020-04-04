#include "std_lib_facilities.h"
int main() {
	vector<int> intvector;
	cout << "enter a set of ints :";
	int i;
	// fill in the set of ints
	while (cin >> i) {
		intvector.push_back(i);
	}
	struct histogram {
		int num;
		int freq;
	};
	vector<histogram> hist;
	// deternine max and min of range of input ints
	int max = 0;
	int min = 0;
	for (int x : intvector) {
		if (x >= max)
			max = x;
		else if (x <= min)
			min = x;
	}
	//fill in histogram values
	for (int i = min; i <= max; i++) {
		histogram h;
		h.num = i;
		h.freq = 0;
		hist.push_back(h);
	}
	//fill in histogram frequencies
	for (int i = 0; i < hist.size(); i++) {
		for (int j = 0; j < intvector.size(); j++) {
			if (intvector[j] == hist[i].num)
				++hist[i].freq;
		}
	}
	//print out the histogram list
	cout << "value" << "  " << "freq" << "\n";
	for (int i = 0; i < hist.size(); i++) {
		cout << hist[i].num << "  " << hist[i].freq<<"\n";
	}

	//determine the mode and print it
	max = 0;
	int mode = 0;
	for (histogram x : hist) {
		if (x.freq >= max) {
			mode = x.num;
			max = x.freq;
		}
	}
	cout << "the mode is " << mode<<"\n";
	return 0;
}