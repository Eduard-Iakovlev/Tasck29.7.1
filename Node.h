#pragma once
#include <mutex>


struct Node{
	Node();
	int _value;
	Node* _next;
	std::mutex node_mutex;
};

