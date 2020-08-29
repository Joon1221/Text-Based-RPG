#ifndef STATISTICS_H
#define STATISTICS_H

class StatLogEvent;

class Statistics {
private:
    StatLogEvent *statLogEvent;

public:
    int totalDistHeroMoved;
    
    int totalMonsNumAtkedTotal;
    int totalMonsDmgTotal;
    int totalMonsDmgAbsorb;
    
    //int numMonsAttackedByHero;
    //int numMonsDied;
    //int numBossesAttackedByHero;
    //int numBossesDied;
    //int numUsePortals;
    //int totalMonsCountDef;
    //int totalMonsDef;
    //int totalMonsCountAtk;
    //int totalMonsAtk;
    
public:
    Statistics();
    virtual ~Statistics();
    
    void reset();
    
    void startLog();
    void printSnapshot(ostream &out);
    void endLog();
};

#endif
