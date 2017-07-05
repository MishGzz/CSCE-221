#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "SkipList.h"

using namespace std;

int main(int argc, char* argv[]) {
	srand(time(NULL));
	ifstream in;
	vector<int> values;

	SkipList list;
	
	string file = argv[1];
	in.open("files/" + file);
	if (!in.good()) {
		cerr << "There was an error opening the document." << endl;
	}

	int key;

	while (in >> key) {
		//cout << key << endl;
		values.push_back(key);
	}

	//small lists
	if (values.size() <= 16) {
		cout << "Input data:" << endl;
		for (int i = 0; i < values.size(); i++) {
			cout << values.at(i) << endl;
		}
		cout << "Create skiplist:" << endl;
		for (int i = 0; i < values.size(); i++) {
			int heads = rand() % 2;
			int count = 0;
			while (heads != 0) {
				count++;
				heads = rand() % 2;
			}
			if (count >= list.getLevel()) {
				cout << "Adding " << values.at(i) << " to skiplist at level " << list.getLevel() << ", ";
			}
			else {
				cout << "Adding " << values.at(i) << " to skiplist at level " << count << ", ";
			}
			list.Insert(values.at(i), count, true); // adding values
		}
		cout << list << endl;
		cout << "Delete skiplist:" << endl;
	}
	//large lists
	else {
		for (int i = 0; i < values.size(); i++) {
			int heads = rand() % 2;
			int count = 0;
			while (heads != 0) {
				count++;
				heads = rand() % 2;
			}
			list.Insert(values.at(i), count, false); //adding values
		}
	}
	list.Delete(values); // delete values from the list

	cout << "Average insert cost: " << list.getInsertComps()/values.size() << endl;
	cout << "Average delete cost: " << list.getDeleteComps()/values.size() << endl;
	cout << "program ended..." << endl;

	//system("pause");
}