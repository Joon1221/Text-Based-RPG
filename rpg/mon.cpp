#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "hero.h"
#include "board.h"
#include "mon.h"
#include "statistics.h"

#include "sim.h"
extern Sim *sim;

// Default Constructor
Mon::Mon()
    : Unit(DEFAULT_MON_SHAPE, -1, -1, DEFAULT_MON_HP, DEFAULT_MON_HP_MAX,
           DEFAULT_MON_MELEE_ATK, DEFAULT_MON_RANGE_ATK,
           DEFAULT_MON_GOLD, DEFAULT_MON_EXP,
           DEFAULT_LEVEL, DEFAULT_MAX_EXP_TO_LEVEL_UP, DEFAULT_MON_FREEZE) {
    range = DEFAULT_MON_RANGE;
    def = DEFAULT_MON_DEF;
}
// General Constructor
Mon::Mon(char shape, int hp, int maxHp, int meeleAtk, int rangeAtk,
         int gold, int exp, int level, int currentMaxExpToLevelUp,
         bool freeze, int range)
    : Unit(shape, -1, -1, hp, maxHp, meeleAtk, rangeAtk, gold, exp, level,
           currentMaxExpToLevelUp, freeze) {
    this->range = range;
}

Mon::~Mon() {
}

void Mon::print() {
#ifdef ANSI_COLOR_OUTPUT
    cout << CYAN;
#endif
    cout << shape;
#ifdef ANSI_COLOR_OUTPUT
    cout << RESET;
#endif
}

void Mon::setRange(int range) {
    this->range = range;
}

void Mon::move(int moveDir) {
    if (freeze) {
        return;
    }
#ifdef BOSS_IQ_80
    if (moveOrFollowHuman(moveDir)) {
        return;
    }
#endif
    
    // move boss
    bool moved = false;
    int prevRow = row;
    int prevCol = col;
    int nextRow = row;
    int nextCol = col;
    
    Unit *unit = sim->board->getUnit(row, col);
    
    if (moveDir == MOVE_DIR_NORTH && sim->board->isClimbable(row-1, col)) {
        nextRow = row - 1;
        moved = true;
    }
    else if (moveDir == MOVE_DIR_EAST && sim->board->isClimbable(row, col+1)) {
        nextCol = col + 1;
        moved = true;
    }
    else if (moveDir == MOVE_DIR_SOUTH && sim->board->isClimbable(row+1, col)) {
        nextRow = row + 1;
        moved = true;
    }
    else if (moveDir == MOVE_DIR_WEST && sim->board->isClimbable(row, col-1)) {
        nextCol = col - 1;
        moved = true;
    }
    
    if (moved) {
        sim->board->setUnit(prevRow, prevCol, NULL);
        sim->board->setUnit(nextRow, nextCol, unit);
        unitCurDir = moveDir;
    }
}

bool Mon::isMon() {
    return true;
}

bool Mon::moveOrFollowHuman(int moveDir) {
    bool foundHero = false;
    int heroRow = -1;
    int heroCol = -1;
    Hero *hero = NULL;
    
    for (int i = row-range; i <= row+range && !foundHero; i++) {
        for (int j = col-range; j <= col+range && !foundHero; j++) {
            if (sim->board->validate(i, j) &&
                sim->board->getUnit(i, j) != NULL &&
                sim->board->getUnit(i, j)->isHero()) {
                foundHero = true;
                heroRow = i;
                heroCol = j;
                hero = (Hero *)sim->board->getUnit(i, j);
            }
        }
    }
    
    if (foundHero) {
        int rowDir = (heroRow - row == 0)? 0: ((heroRow - row < 0)? -1: 1);
        int colDir = (heroCol - col == 0)? 0: ((heroCol - col < 0)? -1: 1);

        // rowDir과 colDir중에 더 긴 diff를 가진 쪽것만 add한다.
        int rowDiff = abs(heroRow - row);
        int colDiff = abs(heroCol - col);
        
        int nextRow = row+((rowDiff > colDiff)?rowDir:0);
        int nextCol = col+((rowDiff <= colDiff)?colDir:0);
        
        if (nextRow == heroRow && nextCol == heroCol) { // adjacent -> hit hero
            if (meleeAtk - hero->getDef()/2 > 0) {
                hero->decHp(meleeAtk - hero->getDef()/2);
            }
            return true;
        }
        else {
            if (sim->board->validate(nextRow, nextCol) &&
                sim->board->getUnit(nextRow, nextCol) == NULL &&
                sim->board->isClimbable(nextRow, nextCol)) {
                sim->board->setUnit(row, col, NULL);
                sim->board->setUnit(nextRow, nextCol, this);
                return true;
            }
        }
    }

    return false;
}

void Mon::interact(Unit *unit) {
    if (isDead()) {
        return;
    }
    
    if (unit == NULL) {
        return;
    }
    
    ((Hero *)unit)->setUnitEngaged(this);
    setUnitEngaged(unit);
    
    if (unit->getMeleeAtk() - def/2 > 0) {
        sim->stat->totalMonsNumAtkedTotal++;
        sim->stat->totalMonsDmgTotal += unit->getMeleeAtk() - def/2;
        sim->stat->totalMonsDmgAbsorb += def/2;

        decHp(unit->getMeleeAtk() - def/2);
    }
    else {
        sim->stat->totalMonsNumAtkedTotal++;
        sim->stat->totalMonsDmgAbsorb += unit->getMeleeAtk();
    }
    //cout << "Hero hit the monster! " << hero->getAtk() << " point(s)!! Monster's HP is " << enemy->getHp() << "!!" << endl;
    
    if (!isDead()) {
        if (meleeAtk - unit->getDef()/2 > 0) {
            unit->decHp(meleeAtk - unit->getDef());
        }
    }
    else {
        //cout << "Monster died!! Congratulation!!" << endl;
        unit->incGold(gold);
        unit->incExp(exp);
        
        int randNum = rand() % 4;
        cout << randNum;
        if (randNum == 1) {
            unit->addPotion(1);
        }
    }
}

string Mon::getID() {
    return string(UNIT_ID_MON);
}

void Mon::save(ostream &out) {
    Unit::save(out);
    out << "#-------------------- class Mon" << endl;
    
    out << "# range" << endl;
    out << range << endl;
}

void Mon::load(istream &in) {
    Unit::load(in);
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Mon" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# range" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << range << endl;
    in >> range;
    in.get(); // skip enter code.
    
}
