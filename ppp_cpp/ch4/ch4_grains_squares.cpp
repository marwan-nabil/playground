#include "std_lib_facilities.h"
int main() {
	int i;
	int cumsum=0;
	for (i = 0; i < 64;i++) {
		cumsum += pow(2, i);
		cout << "\nyou are on the number " << i + 1 << " square, and have " << cumsum << " grains .";
		if (cumsum >= 1000)
			break;
	}
	cout << "\nyou need at least " << i+1 << " squares to get over a 1000 grains";

	cumsum = 0;
	for (i = 0; i < 64; i++) {
		cumsum += pow(2, i);
		cout << "\nyou are on the number " << i + 1 << " square, and have " << cumsum << " grains .";
		if (cumsum >= 1000000)
			break;
	}
	cout << "\nyou need at least " << i + 1 << " squares to get over a 1000000 grains";



	return 0;
}