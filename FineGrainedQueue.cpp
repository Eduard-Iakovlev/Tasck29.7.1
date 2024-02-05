#include "FineGrainedQueue.h"
#include <future>
#include <conio.h>
#include <iostream>
#include "Data.h"

FineGrainedQueue::FineGrainedQueue(){
    Node* new_node = new Node();

    new_node->_value = rand() % 99;
    head = new_node;
    end = new_node;
    for (int i = 0; i < 4; i++) {
        push_back();
    }
    show();
    std::cout << " To exit, press ESC\n";

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

    if (pos > _size) {
        queue_mutex.lock();
        push_back(value);
        queue_mutex.unlock();
        return;
    }

    Node* new_node = new Node();
    Node* prev, * cur;

    queue_mutex.lock();
    prev = this->head;

    new_node->_value = value;
    new_node->_next = nullptr;

    cur = head;
    int cur_pos = 1;

    while (cur_pos < pos - 1) {
        prev = prev->_next;
        cur_pos++;
    }
    cur = prev->_next;

    prev->node_mutex.lock();
    cur->node_mutex.lock();
    queue_mutex.unlock();
    prev->_next = new_node;
    new_node->_next = cur;
    prev->node_mutex.unlock();
    cur->node_mutex.unlock();
    _size++;
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

void FineGrainedQueue::enter_data() {
    Data<int> data('0', '9');
    std::cout << "\n Enter data: \n";

    std::cout << " value-1 = ";
    _val1 = data.input();
    data.clear();
    std::cout << " position-1 = ";
    _pos1 = data.input();
    data.clear();
    std::cout << std::endl;

    std::cout << " value-2 = ";
    _val2 = data.input();
    data.clear();
    std::cout << " position-2 = ";
    _pos2 = data.input();
    data.clear();
    std::cout << std::endl;

    std::cout << " value-3 = ";
    _val3 = data.input();
    data.clear();
    std::cout << " position-3 = ";
    _pos3 = data.input();
    data.clear();
    std::cout << std::endl;
}

void FineGrainedQueue::menu(){ 
    if (_getch() == _menu) exit(0);
}

void FineGrainedQueue::start(){
    while (true) {
        enter_data();

        std::future<void> insert1 = std::async(std::launch::async, &FineGrainedQueue::insertIntoMiddle, this, _val1, _pos1);
        std::future<void> insert2 = std::async(std::launch::async, &FineGrainedQueue::insertIntoMiddle, this, _val2, _pos2);
        std::future<void> insert3 = std::async(std::launch::async, &FineGrainedQueue::insertIntoMiddle, this, _val3, _pos3);
        
        insert1.wait();
        insert2.wait();
        insert3.wait();
        show();
        std::cout << " To exit, press ESC\n to continue, press enykey";
        menu();
    }
}
