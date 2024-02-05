#include "FineGrainedQueue.h"
#include <iostream>

FineGrainedQueue::FineGrainedQueue(){
    std::mutex queue_mutex;
    Node* new_node = new Node();

    new_node->_value = rand() % 99;
    head = new_node;
    end = new_node;
    for (int i = 0; i < 4; i++) {
        push_back();
    }
    show();
}

void FineGrainedQueue::push_back(){
    Node* new_node = new Node();
    new_node->_value = rand() % 99;
    end->_next = new_node;
    end = new_node;
    _size++;
}
void FineGrainedQueue::push_back(int value){
    Node* new_node = new Node();
    new_node->_value = value;
    end->_next = new_node;
    end = new_node;
    _size++;
}

bool FineGrainedQueue::is_empty(){
    return head == nullptr;
}

void FineGrainedQueue::insertIntoMiddle(int value, int pos){

    queue_mutex->lock();

    if (pos > _size) {
        push_back(value);
        queue_mutex->unlock();
        show();
        return;
    }

    Node* new_node = new Node();
    Node* prev, * cur;

    prev = this->head;

    new_node->_value = value;
    new_node->_next = nullptr;
    new_node->node_mutex = new std::mutex();

    cur = head;
    int cur_pos = 1;

    while (cur_pos < pos - 1) {
        prev = prev->_next;
        cur_pos++;
    }
    cur = prev->_next;

    //std::lock(prev->node_mutex, cur->node_mutex);
    //std::lock_guard<std::mutex> prev_lock(prev->node_mutex, std::adopt_lock);
    //std::lock_guard<std::mutex> cur_lock(cur->node_mutex, std::adopt_lock);
    prev->node_mutex->lock();
    cur->node_mutex->lock();
    queue_mutex->unlock();
    prev->_next = new_node;
    new_node->_next = cur;
    prev->node_mutex->unlock();
    cur->node_mutex->unlock();

    show();
}

void FineGrainedQueue::show(){
    Node* new_node = head;
    if (is_empty()) return;
    std::cout << " List:" << std::endl;
    while (new_node->_next != nullptr) {
        std::cout << new_node->_value << " ";
        new_node = new_node->_next;
    }
    std::cout << new_node->_value;
    std::cout << "\n size = " << _size << " elements" << std::endl;

}
