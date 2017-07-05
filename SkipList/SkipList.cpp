#include "SkipList.h"
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <vector>


SkipList::~SkipList() {
	this->clear();
}
SkipList::SkipList(const SkipList& list) {
	return;
}

Node* SkipList::Search(int key, bool small) { // search function (called by delete)
	Node *cur = root;
	int comparisons = 0;
	//traverse list
	while (cur != nullptr) {
		comparisons++;
		while (cur->key < key) { //traverse to the right
			comparisons++;
			cur = cur->next;
		}
		comparisons++;
		if (cur->key == key) { //found key
			if (small) {
				cout << comparisons << " comparisons" << endl;
			}
			totalDeleteComparisons += comparisons; // add up comparisons
			return cur;
		}
		else { // move down one layer
			cur = cur->prev;
			cur = cur->down;
			if (cur) {
				cur = cur->next;
			}
		}
	}
	//didnt find key
	cout << "Key not found" << endl;
	return nullptr;
}
void SkipList::Insert(int key, int count, bool small) { // insert function
	
	vector<Node*> vec;
	int comparisons = 0;

	if (count >= level) { // add a layer to the skip list
		count = level;
		level++;
		Node *newRoot = new Node(numeric_limits<int>::min());
		Node *newTail = new Node(numeric_limits<int>::max());

		newRoot->next = newTail;
		newTail->prev = newRoot;

		newRoot->down = root;
		newTail->down = tail;

		root->up = newRoot;
		tail->up = newTail;

		root = newRoot;
		tail = newTail;
	}

	Node *tmp = root;
	count = level - count - 1;
	for (int i = 0; i < count; i++) { // move down to correct starting position for inserting key
		tmp = tmp->down;
	}
	while (tmp != nullptr) { // traverse list
		comparisons++;
		if (key > tmp->key) { // travers to the right
			tmp = tmp->next;
		}
		else { // found correct spot
			Node *a = new Node(key);
			a->next = tmp;
			a->prev = tmp->prev;
			tmp->prev = a;
			(a->prev)->next = a;
			vec.push_back(a);

			tmp = a->prev;
			tmp = tmp->down; // move down one layer
		}
	}
	if (vec.size() > 1) { // connect the newly added node to its bretheren that are above and below it
		vec.at(0)->down = vec.at(1);
		vec.at(vec.size() - 1)->up = vec.at(vec.size() - 2);
		for (int i = 1; i < vec.size() - 1; i++) {
			vec.at(i)->up = vec.at(i - 1);
			vec.at(i)->down = vec.at(i + 1);
		}
	}
	if (small) { // list is small, print comparisons
		cout << comparisons << " comparisons" << endl;
	}
	totalInsertComparisons += comparisons; // add up comparisons
}
void SkipList::Delete(vector<int> values) { //delete function
	bool small = false;
	for (int i = values.size() - 1; i >= 0; i--) { // list is small, print comparisons
		if (values.size() <= 16) {
			cout << "Deleting " << values.at(i) << " from skiplist, ";
			small = true;
		}
		Node * deleteNode = Search(values.at(i), small); // call search function

		if (deleteNode) { // found node
			while (deleteNode->down) {// while the node has more nodes below it keep deleting and traversing downwards
				if (!(deleteNode->prev->prev) && !(deleteNode->next->next)) {
					root = deleteNode->prev->down;
					tail = deleteNode->next->down;
					delete deleteNode->prev;
					delete deleteNode->next;
				}
				else {// make sure everthing gets patched up before a deletion
					(deleteNode->prev)->next = deleteNode->next;
					(deleteNode->next)->prev = deleteNode->prev;
				}
				deleteNode = deleteNode->down;
				delete deleteNode->up;
			}
			(deleteNode->prev)->next = deleteNode->next;
			(deleteNode->next)->prev = deleteNode->prev;
			delete deleteNode;
		}
	}

}
void SkipList::clear() { // called by destructor
	Node* current = root;
		while (current != nullptr) {
			Node* deleteNode = current;
			if (current->next == nullptr) {
				if (current->down) {
					current = current->down;
					while (current->prev != nullptr) {
						current = current->prev;
					}
				}
				else {
					current = nullptr;
				}
			}
			else {
				current = current->next;
			}
			delete deleteNode;
		}
}

ostream& operator<<(ostream& out, const SkipList& list) { // output operator overload
	Node *cur = list.root;
	if (cur->getNext()->getNext() == nullptr && cur->getDown() == nullptr) {
		out << "List is empty" << endl;
	}
	while(cur != nullptr) {
		if (cur->getKey() < -9999999) { // i dont expect any numbers smaller than this
			out << "-Infinity, ";
		}
 		else if (cur->getKey() > 9999999) { // or larger than this
			out << "Infinity" << endl;
		}
		else {
			out << cur->getKey() << ", ";
		}
		if (cur->getNext() == nullptr) {
			if (cur->getDown()) {
				cur = cur->getDown();
				while (cur->getPrev() != nullptr) {
					cur = cur->getPrev();
				}
			}
			else {
				cur = cur->getDown();
			}
		}
		else {
			cur = cur->getNext();
		}
	}
	return out;
}