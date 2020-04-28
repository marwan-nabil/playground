#include "std_lib_facilities.h"

int main() {


	vector<char> decisions;
	char in_char;
	cout << "we'll play rock paper cissors , we need you to enter a series of choices to emulate random computer behaviour : ";
	while (cin.get(in_char)) {
		decisions.push_back(in_char);
	}
	random_shuffle(decisions.begin(), decisions.end());

	char user_choice,comp_choice;
	for (int i = 0; i <= 1;i++) {
		cout << "\nplay (r/p/s): ";
		cin >> user_choice;
		comp_choice = decisions.front();
		random_shuffle(decisions.begin(), decisions.end());

		switch (user_choice) {
		case 'r':
			if (comp_choice == 'p')
				cout << "\ncomputer wins!";
			else if(comp_choice=='s')
				cout << "\nplayer wins!";
			else
				cout << "\nno winner!";
			break;
		case 'p':
			if (comp_choice == 's')
				cout << "\ncomputer wins!";
			else if (comp_choice == 'r')
				cout << "\nplayer wins!";
			else
				cout << "\nno winner!";
			break;
		case 's':
			if (comp_choice == 'r')
				cout << "\ncomputer wins!";
			else if (comp_choice == 'p')
				cout << "\nplayer wins!" ;
			else
				cout << "\nno winner!";
			break;
		default:
			cout << "\nenter a valid choice !!";
		}
	}
	return 0;
}