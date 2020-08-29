#include <iostream>

using namespace std;

#include "board.h"
#include "eventqueue.h"
#include "statistics.h"
#include "sim.h"

Sim::Sim() {
    time = 0;
    day = true;
    
    board = NULL;
    hero = NULL;
    
    eq = new EventQueue();
    stat = new Statistics();
}

Sim::~Sim() {
    if (board != NULL) {
        delete board;
        board = NULL;
    }
    if (eq != NULL) {
        delete eq;
        eq = NULL;
    }
    if (stat != NULL) {
        delete stat;
        stat = NULL;
    }
}
