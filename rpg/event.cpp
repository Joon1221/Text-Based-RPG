#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <string>

using namespace std;

#include "main.h"
#include "unit.h"
#include "mon.h"
#include "board.h"
#include "event.h"
#include "eventqueue.h"
#include "statistics.h"
#include "item.h"

#include "sim.h"
extern Sim *sim;

Event::Event() {
    time = 0;
}

Event::Event(int time) {
    this->time = time;
}

Event::~Event() {
}

void Event::print() {
    cout << "time: " << time << endl;
}

//==============================================================================
// class MonRespawnEvent
//==============================================================================

MonRespawnEvent::MonRespawnEvent() : Event() {
    mon = NULL;
}

MonRespawnEvent::MonRespawnEvent(int time, Mon *mon) : Event(time) {
    this->mon = mon;
}

MonRespawnEvent::~MonRespawnEvent() {
}

void MonRespawnEvent::trigger() {
    mon->reset();
    
    while (true) {
        int randRow = rand() % sim->board->getRowSize();
        int randCol = rand() % sim->board->getColSize();
        
        if (sim->board->getUnit(randRow, randCol) == NULL &&
            sim->board->getItem(randRow, randCol) == NULL &&
            sim->board->getProp(randRow, randCol) == NULL) {
            sim->board->setUnit(randRow, randCol, mon);
            break;
        }
    }
    delete this; // destroy me
}

//==============================================================================
// class DayAndNightEvent
//==============================================================================

DayAndNightEvent::DayAndNightEvent() : Event() {
}

DayAndNightEvent::DayAndNightEvent(int time) : Event(time) {
}

DayAndNightEvent::~DayAndNightEvent() {
}

void DayAndNightEvent::trigger() {
    sim->day = !sim->day;
    
    time = sim->time + DAY_AND_NIGHT_EVENT_INTERVAL;
    sim->eq->enqueue(this);
}

//==============================================================================
// class TimeBombEvent
//==============================================================================

TimeBombEvent::TimeBombEvent() : Event() {
    timeBomb = NULL;
}

TimeBombEvent::TimeBombEvent(int time, TimeBomb *timeBomb) : Event(time) {
    this->timeBomb = timeBomb;
}

TimeBombEvent::~TimeBombEvent() {
}

void TimeBombEvent::trigger() {
    timeBomb->trigger();
    delete this;
}

//==============================================================================
// class BossRushEvent
//==============================================================================

BossRushEvent::BossRushEvent() : Event() {
}

BossRushEvent::BossRushEvent(int time) : Event(time) {
}

BossRushEvent::~BossRushEvent() {
}

void BossRushEvent::trigger() {
    sim->board->bossRush();
    delete this;
}

//------------------------------------------------------------------------------
// class StatLogEvent
//------------------------------------------------------------------------------

StatLogEvent::StatLogEvent() : Event() {
    destroy = false;
}

StatLogEvent::StatLogEvent(const StatLogEvent &other) : Event(other) {
}

StatLogEvent::StatLogEvent(int time, string logFilename) : Event(time) {
    this->time = time;
    this->logFilename = logFilename;
    destroy = false;
}

StatLogEvent::~StatLogEvent() {
}

void StatLogEvent::setSelfDestroy(bool destroy) {
    this->destroy = destroy;
}

void StatLogEvent::trigger() {
    if (destroy) {
        delete this;
    }
    else {
        // save the current item.
        ofstream logFile;
        logFile.open(logFilename.c_str(), ofstream::out | ofstream::app);
        sim->stat->printSnapshot(logFile);
        logFile.close();
        
        // re-scheduling
        time += STAT_LOG_EVENT_INTERVAL;
        sim->eq->enqueue(this);
    }
}
