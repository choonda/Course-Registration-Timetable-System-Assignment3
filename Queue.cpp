#include "Queue.h"

// 1. Apply for Course (Insert to Back)
void RegistrationQueue::enqueue(std::string sid, std::string code) {
    NodeQ* newNode = new NodeQ; // cite: 134
    newNode->data.studentID = sid;
    newNode->data.courseCode = code;
    newNode->next = nullptr; // cite: 135

    if (isEmpty()) {
        frontPtr = backPtr = newNode; // cite: 136
    } else {
        backPtr->next = newNode; // cite: 138
        backPtr = newNode; // cite: 139
    }
}

// 2. Process Request (Remove from Front)
Request RegistrationQueue::dequeue() {
    if (isEmpty()) return {"", ""};

    NodeQ* temp = frontPtr; // cite: 164
    Request data = temp->data;
    frontPtr = frontPtr->next; // cite: 165

    if (frontPtr == nullptr) backPtr = nullptr; // cite: 192

    delete temp; // cite: 167
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
    NodeQ* temp = frontPtr; // cite: 110
    while (temp) { // cite: 111
        frontPtr = temp->next; // cite: 112
        delete temp; // cite: 113
        temp = frontPtr;
    }
    backPtr = nullptr;
}