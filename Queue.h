#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <iostream>

struct Request {
    std::string studentID;
    std::string courseCode;
};

struct NodeQ {
    Request data;
    NodeQ* next;
};

class RegistrationQueue {
private:
    NodeQ *frontPtr, *backPtr; // cite: 98

public:
    RegistrationQueue() : frontPtr(nullptr), backPtr(nullptr) {} // cite: 107
    ~RegistrationQueue() { clearQueue(); }

    bool isEmpty() const { return frontPtr == nullptr; } // cite: 114
    
    // Function 1: Enqueue (Apply)
    void enqueue(std::string sid, std::string code); 
    
    // Function 2: Dequeue (Process)
    Request dequeue(); 

    // Function 3: View (Traverse)
    void displayQueue() const;

    // Function 4: Clear (Destroy)
    void clearQueue(); 
};

#endif