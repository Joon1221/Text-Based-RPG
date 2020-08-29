#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "event.h"
#include "eventqueue.h"
#include "statistics.h"
#include "sim.h"
extern Sim *sim;

Statistics::Statistics() {
    statLogEvent = NULL;
    
    reset();
}

Statistics::~Statistics() {
    // statLogEvent will be deleted by eventQueue or endLog().
}

void Statistics::reset() {
    totalDistHeroMoved = 0;
    
    totalMonsNumAtkedTotal = 0;
    totalMonsDmgTotal = 0;
    totalMonsDmgAbsorb = 0;
    
//    numMonsAttackedByHero = 0;
//    numMonsDied = 0;
//    numBossesAttackedByHero = 0;
//    numBossesDied = 0;
//    numUsePortals = 0;
}

#define LOG_COLUMN_WIDTH 10
void Statistics::startLog() {
    statLogEvent = new StatLogEvent(sim->time, STAT_LOG_FILENAME);
    sim->eq->enqueue(statLogEvent);
    
    // save the current item.
    string logFilename = STAT_LOG_FILENAME;
    ofstream logFile;
    logFile.open(logFilename.c_str());
    logFile << setw(LOG_COLUMN_WIDTH) << "Time"
            << setw(LOG_COLUMN_WIDTH) << "DistMoved"
            << setw(LOG_COLUMN_WIDTH) << "NumAtked"
            << setw(LOG_COLUMN_WIDTH) << "DmgTotal"
            << setw(LOG_COLUMN_WIDTH) << "DmgAbsorb"
//            << setw(LOG_COLUMN_WIDTH) << "MonsAtked"
//            << setw(LOG_COLUMN_WIDTH) << "MonsDied"
//            << setw(LOG_COLUMN_WIDTH) << "BossAtked"
//            << setw(LOG_COLUMN_WIDTH) << "BossDied"
//            << setw(LOG_COLUMN_WIDTH) << "Portals"
            << endl;
    logFile.close();
}

void Statistics::printSnapshot(ostream &out) {
    out << setw(LOG_COLUMN_WIDTH) << sim->time
        << setw(LOG_COLUMN_WIDTH) << totalDistHeroMoved
        << setw(LOG_COLUMN_WIDTH) << totalMonsNumAtkedTotal
        << setw(LOG_COLUMN_WIDTH) << totalMonsDmgTotal
        << setw(LOG_COLUMN_WIDTH) << totalMonsDmgAbsorb
//        << setw(LOG_COLUMN_WIDTH) << numMonsAttackedByHero
//        << setw(LOG_COLUMN_WIDTH) << numMonsDied
//        << setw(LOG_COLUMN_WIDTH) << numBossesAttackedByHero
//        << setw(LOG_COLUMN_WIDTH) << numBossesDied
//        << setw(LOG_COLUMN_WIDTH) << numUsePortals
        << endl;
}

void Statistics::endLog() {
    statLogEvent->setSelfDestroy(true);
}
