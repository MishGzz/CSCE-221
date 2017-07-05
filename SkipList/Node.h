#pragma once
#ifndef NODE_h
#define NODE_h


struct Node {
private:
	friend class SkipList;
	int key;
	Node *next;
	Node *prev;
	Node *down;
	Node *up;
public:
	//constructor
	Node(int key = 0, int level = 0, Node *next = nullptr, Node *prev = nullptr, Node *up = nullptr, Node *down = nullptr)
		: key(key), next(next), prev(prev), up(up), down(down) {}
	//member functions
	Node *getNext() {
		if (next) {
			return next;
		}
		else {
			return nullptr;
		}
	}
	Node *getPrev() {
		if (prev) {
			return prev;
		}
		else {
			return nullptr;
		}
	}
	Node *getDown() {
		if (down) {
			return down;
		}
		else {
			return nullptr;
		}
	}
	Node *getUp() {
		if (up) {
			return up;
		}
		else {
			return nullptr;
		}
	}
	int getKey() {
		return key;
	}
};
#endif
