#pragma once
#include "Node.h"

class FineGrainedQueue{
public:
	FineGrainedQueue();
	void push_back();
	void push_back(int value);
	bool is_empty();
	void insertIntoMiddle(int value, int pos);
	void show();
	void enter_data();
	void menu();
	void start();

private:
	Node* head;
	Node* end;
	std::mutex queue_mutex;
	int _size = 1;
	int _val1, _val2, _val3;
	int _pos1, _pos2, _pos3;
	const char _menu = 27;
};

