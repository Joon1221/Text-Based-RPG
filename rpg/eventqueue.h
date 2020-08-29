#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

class Event;

class EQNode {
public:
    Event *event;
    EQNode *next;
    
    EQNode();
    EQNode(Event *event);
};

class EventQueue {
private:
    EQNode *head;
    int numNodes;
    
public:
    EventQueue();
    virtual ~EventQueue();
    
    void print();
    
    // pre-condition: the given event is not null
    void enqueue(Event *event); // insert
    // pre-condition: size() > 0
    Event *dequeue();
    // pre-condition: size() > 0
    Event *peek();
    
    int size();

};

#endif
