#include "FineGrainedQueue.h"
#include <iostream>

FineGrainedQueue::FineGrainedQueue(){
    Node* new_node = new Node();

    new_node->_value = rand() % 99;
    head = new_node;
    end = new_node;
    for (int i = 0; i < 5; i++) {
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
    Node* prev;
    std::mutex node_mutex;

    new_node->_value = value;
    prev = end;
    //end->node_mutex->lock();
    prev->_next = new_node;
    //end->_next = new_node;
    //end = new_node;
    prev = new_node;
    end->node_mutex->unlock();
    _size++;
}

bool FineGrainedQueue::is_empty(){
    return head == nullptr;
}

void FineGrainedQueue::insertIntoMiddle(int value, int pos){
    std::mutex queue_mutex;
    std::mutex node_mutex;

    queue_mutex.lock();

    if (pos > _size) {
        push_back(value);
        queue_mutex.unlock();
        return;
    }

    Node* new_node = new Node();
    Node* prev, * cur;
    //std::lock_guard<std::mutex> lock(*queue_mutex);

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

    prev->node_mutex->lock();
    cur->node_mutex->lock();
    queue_mutex.unlock();
    prev->_next = new_node;
    new_node->_next = cur;
    prev->node_mutex->unlock();
    cur->node_mutex->unlock();

    //if (prev->_next != nullptr) {
     //   std::lock(prev->node_mutex, cur->node_mutex);
    //    std::lock_guard<std::mutex> current_lock(*current->node_mutex, std::adopt_lock);
    //    std::lock_guard<std::mutex> next_lock(*current->_next->node_mutex, std::adopt_lock);
    //    new_node->_next = cur;
    //    prev->_next = new_node;
    //}
    //else {
    //    std::lock_guard<std::mutex> current_lock(*prev->node_mutex);
    //    prev->_next = new_node;
    //}
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
    std::cout << "\n size = " << _size << " elements" << std::endl;

}
