#include "std_lib_facilities.h"
vector<string> names;
vector<int> scores;
bool is_name_unique(const string& name);
int the_index_of(const string& name);
int main() {
	vector<string> names;
	vector<int> scores;
	int score=0;
	string name = "";

	cout << "Please enter name and a score\n >>";
	while (cin >> name ) {
		// if user is querying
		if (!(cin >> score)) {
			if (is_name_unique(name))
				cout << "for name " << name << " the score is " << scores[the_index_of(name)];
				//cout << the_index_of(name);
			else {
				cout << "no such name exists !\n";
				continue;
			}
		}

		// check for name uniqeness
		if (!is_name_unique(name)) {
			cout << "\nPlease enter a unique name !\n >>";
			continue;
		}
		// check for end of input
		if (name == "NoName" && score == 0)
			break;
		// register the inputs
		names.push_back(name);
		scores.push_back(score);
		cout << "Please enter name and a score\n >>";
	}

	// output stage
	for (unsigned int i = 0; i < names.size();i++) {
		cout << "name = " << names[i] << " score= " << scores[i] << "\n";
	}
	return 0;
}


// problematic function : always return -1
int the_index_of(const string& name) {
	for (int i = 0; i < names.size(); i++) {
		if (name.compare(names[i]) ==0 )
			return i;
	}
	return -1;
}

bool is_name_unique(const string& name) {
	for (string x : names) {
		if (x == name)
			return false;
	}
	return true;
}