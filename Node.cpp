#include "Node.h"

Node::Node() : _value( 0 ), _next(nullptr){
	std::mutex node_mutex;
}
