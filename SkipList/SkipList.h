#pragma once

#include "Node.h"
#include <ostream>
#include <limits>
#include <vector>

using namespace std;

class SkipList {
private:
	Node *root;
	Node *tail;
	int level;
	int totalInsertComparisons = 0;
	int totalDeleteComparisons = 0;

public:
	SkipList() { 
		root = new Node(numeric_limits<int>::min());
		tail = new Node(numeric_limits<int>::max());
		root->next = tail;
		tail->prev = root;
		level = 1;
	}
	~SkipList();
	SkipList(const SkipList& list);
	SkipList& operator=(const SkipList& list);
	Node* getRoot() { return root; }
	Node* Search(int key, bool small);
	void Insert(int key, int heads, bool small);
	void Delete(vector<int> values);
	void clear();
	int getLevel() {
		return level;
	}
	void setLevel(int lvl) {
		level = lvl;
	}
	int getInsertComps() {
		return totalInsertComparisons;
	}
	int getDeleteComps() {
		return totalDeleteComparisons;
	}

	friend ostream& operator<<(ostream&, const SkipList&);
};
