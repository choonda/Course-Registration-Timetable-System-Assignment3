#include "Queue.h"
#include <iostream>

// 1. Apply for Course (Insert to Back)
void RegistrationQueue::enqueue(std::string sid, std::string code) {
    NodeQ* newNode = new NodeQ; 
    newNode->data.studentID = sid;
    newNode->data.courseCode = code;
    newNode->next = nullptr; 

    if (isEmpty()) {
        frontPtr = backPtr = newNode; 
    } else {
        backPtr->next = newNode; 
        backPtr = newNode; 
    }
}

// 2. Process Request (Remove from Front)
Request RegistrationQueue::dequeue() {
    if (isEmpty()) return {"", ""};

    NodeQ* temp = frontPtr;
    Request data = temp->data;
    frontPtr = frontPtr->next; 

    if (frontPtr == nullptr) backPtr = nullptr; 

    delete temp;
    return data;
}

// 3. View All Pending Requests
void RegistrationQueue::displayQueue() const {
    if (isEmpty()) {
        std::cout << "Queue is empty.\n";
        return;
    }
    NodeQ* curr = frontPtr;
    int pos = 1;
    while (curr) {
        std::cout << pos++ << ". Student: " << curr->data.studentID 
                  << " -> Course: " << curr->data.courseCode << "\n";
        curr = curr->next;
    }
}

// 4. Clear All Requests (Destroy Queue)
void RegistrationQueue::clearQueue() {
    NodeQ* temp = frontPtr; 
    while (temp) { 
        frontPtr = temp->next; 
        delete temp; 
        temp = frontPtr;
    }
    backPtr = nullptr;
}