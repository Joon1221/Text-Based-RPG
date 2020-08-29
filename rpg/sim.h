#ifndef SIM_H
#define SIM_H

class Board;
class Hero;
class EventQueue;
class Statistics;

class Sim {
public:
    int time;
    bool day;
    
    Board *board;
    Hero *hero;
    
    EventQueue *eq;
    Statistics *stat;
    
    Sim();
    virtual ~Sim();
};

#endif