#include <iostream>
#include <assert.h>

using namespace std;

#include "event.h"
#include "eventqueue.h"

//------------------------------------------------------------------------------
// class TileNode
//------------------------------------------------------------------------------
EQNode::EQNode() { // 사실 만들 필요 없다. 얘는..
    event = NULL;
    next = NULL;
}

EQNode::EQNode(Event *event) { // 주로 이것을 쓸 것임.
    this->event = event;
    next = NULL;
}

//------------------------------------------------------------------------------
// class TileSet
//------------------------------------------------------------------------------
EventQueue::EventQueue() {
    head = NULL;
    numNodes = 0;
}

EventQueue::~EventQueue() {
    if (head != NULL) { // size() > 0
        if (head->next == NULL) { // size() == 1
            delete head;
            head = NULL;
            numNodes = 0;
        }
        else { // size() > 1
            EQNode *current = head;
            
            while (current != NULL) {
                EQNode *next = current->next;
                delete current;
                
                current = next;
            }
            head = NULL;
            numNodes = 0;
        }
    }
}

void EventQueue::print() {
    EQNode *current = head;
    
    while (current != NULL) {
        current->event->print();
        if (current->next != NULL) {
            cout << "->";
        }
        else {
            cout << "-||";
        }
        
        current = current->next;
    }
    cout << endl;
}

// pre-condition: the given tile is not NULL && find(tile) == NULL
void EventQueue::enqueue(Event *event) { // prepend
    assert(event != NULL);
    
    EQNode *newNode = new EQNode(event);
    numNodes++; // 어차피 무조건 넣을 것이므로..
        
    if (head == NULL) { // size() == 0
        head = newNode;
    }
    else if (head->next == NULL) { // size() == 1
        if (event->time < head->event->time) { // prepend
            newNode->next = head;
            head = newNode;
        }
        else { // append
            head->next = newNode;
        }
    }
    else { // size() > 1
        EQNode *prev = NULL;
        EQNode *current = head;
        
        while (current != NULL) {
            if (event->time < current->event->time) {
                break;
            }
            
            prev = current;
            current = current->next;
        }
        
        // 끼워넣을 장소
        if (prev == NULL) { // prepend
            newNode->next = head;
            head = newNode;
        }
        else if (current == NULL) { // append
            prev->next = newNode;
        }
        else { // insert the new node between prev and current
            prev->next = newNode;
            newNode->next = current;
        }
    }
}

// pre-condition: size() > 0
Event *EventQueue::dequeue() {
    assert(size() > 0);
    
    Event *eventToReturn = head->event;
    EQNode *nodeToRemove = head;
    
    head = head->next;
    
    delete nodeToRemove;
    numNodes--;
    
    return eventToReturn;
}

// pre-condition: size() > 0
Event *EventQueue::peek() {
    assert(size() > 0);
    
    return head->event;
}

int EventQueue::size() {
    return numNodes;
}
