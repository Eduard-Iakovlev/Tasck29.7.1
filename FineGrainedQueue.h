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

private:
	Node* head;
	Node* end;
	std::mutex* queue_mutex;
	int _size = 1;
};

