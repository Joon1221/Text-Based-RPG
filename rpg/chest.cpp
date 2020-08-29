#include <iostream>

using namespace std;

#include "main.h"
#include "prop.h"
#include "chest.h"
#include "item.h"
#include "unit.h"
#include "board.h"

#include "sim.h"
extern Sim *sim;

Chest::Chest() : Prop(DEFAULT_CHEST_SHAPE, DEFAULT_CHEST_CLIMBABLE) {
    initChest(DEFAULT_CHEST_LOCKED, DEFAULT_CHEST_LOCK_LEVEL);
}

Chest::Chest(char shape, bool locked, int lockLevel) : Prop(shape, DEFAULT_CHEST_CLIMBABLE) {
    initChest(locked, lockLevel);
}

void Chest::initChest(bool locked, int lockLevel) {
    this->locked = locked;
    this->lockLevel = lockLevel;
    
    numItems = lockLevel + 1;
    
    for (int i = 0; i < numItems; i++) {
        int temp = rand() % 4;
        
        if (temp == 0) {
            itemToDrop[i] = new Potion();
        }
        else if (temp == 1) {
            itemToDrop[i] = getRandomKey();
        }
        else if (temp == 2) {
            itemToDrop[i] = getRandomWeapon();
        }
        else if (temp == 3) {
            itemToDrop[i] = getRandomArmor();
        }
    }
}

Chest::~Chest() {
    for (int i = 0; i < numItems; i++) {
        delete itemToDrop[i];
        itemToDrop[i] = NULL;
    }
}

/*
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      // Black 
#define RED     "\033[31m"      // Red 
#define GREEN   "\033[32m"      // Green 
#define YELLOW  "\033[33m"      // Yellow 
#define BLUE    "\033[34m"      // Blue 
#define MAGENTA "\033[35m"      // Magenta 
#define CYAN    "\033[36m"      // Cyan 
#define WHITE   "\033[37m"      // White 
#define BOLDBLACK   "\033[1m\033[30m"      // Bold Black 
#define BOLDRED     "\033[1m\033[31m"      // Bold Red 
#define BOLDGREEN   "\033[1m\033[32m"      // Bold Green 
#define BOLDYELLOW  "\033[1m\033[33m"      // Bold Yellow 
#define BOLDBLUE    "\033[1m\033[34m"      // Bold Blue 
#define BOLDMAGENTA "\033[1m\033[35m"      // Bold Magenta 
#define BOLDCYAN    "\033[1m\033[36m"      // Bold Cyan 
#define BOLDWHITE   "\033[1m\033[37m"      // Bold White 
*/
void Chest::print() {
#ifdef ANSI_COLOR_OUTPUT
    if (lockLevel == CHEST_RUSTY) {
        cout << BOLDYELLOW;
    }
    else if (lockLevel == CHEST_BRONZE) {
        cout << BOLDRED;
    }
    else if (lockLevel == CHEST_SILVER) {
        cout << BOLDBLUE;
    }
    else { // if (lockLevel == CHEST_GOLD) {
        cout << BOLDMAGENTA;
    }
#endif
    cout << shape;
#ifdef ANSI_COLOR_OUTPUT
    cout << RESET;
#endif
}

void Chest::unlock() {
    locked = false;
}

void Chest::lock() {
    locked = true;
}

bool Chest::isLocked() {
    return locked;
}

bool Chest::isChest() {
    return true;
}

int Chest::getLockLevel() {
    return lockLevel;
}

bool Chest::trigger(int row, int col, Unit *unit) {
    if (!sim->board->validate(row, col)) {
        return false;
    }

    if (!unit->unlock(this)) {
        return false;
    }
    
    sim->board->setProp(row, col, NULL);
    sim->board->setItem(row, col, itemToDrop[0]);
    for (int indexItem = 1; indexItem < numItems; indexItem++) {
        for (int i = row-1; i <= row+1; i++) {
            for (int j = col-1; j <= col+1; j++) {
                if (sim->board->validate(i, j) &&
                    sim->board->getProp(i, j) == NULL &&
                    sim->board->getItem(i, j) == NULL) {
                    sim->board->setItem(i, j, itemToDrop[indexItem]);
                    itemToDrop[indexItem] = NULL;
                }
            }
        }
    }
    numItems = 0;
    
    delete this; // self destroy

    return true;
}

string Chest::getID() {
    return string(PROP_ID_CHEST);
}

void Chest::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class Chest" << endl;
    
    out << "# locked" << endl;
    out << locked << endl;
    
    out << "# lockLevel" << endl;
    out << lockLevel << endl;

    //??????????????????????????????????????????????????????????????????????????
    // save  Item *itemToDrop[MAX_ITEMS_CHEST];
    //??????????????????????????????????????????????????????????????????????????
    
    out << "# numItems" << endl;
    out << numItems << endl;
}

void Chest::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Chest" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# locked" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << locked << endl;
    in >> locked;
    in.get(); // skip enter code.

    //out << "# lockLevel" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << lockLevel << endl;
    in >> lockLevel;
    in.get(); // skip enter code.

    //??????????????????????????????????????????????????????????????????????????
    // load  Item *itemToDrop[MAX_ITEMS_CHEST];
    //??????????????????????????????????????????????????????????????????????????

    //out << "# numItems" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numItems << endl;
    in >> numItems;
    in.get(); // skip enter code.
}

Chest *getRandomChest() {
    int rangeRusty = (5 - CHEST_RUSTY) * (5 - CHEST_RUSTY);
    int rangeBronze = (5 - CHEST_BRONZE) * (5 - CHEST_BRONZE);
    int rangeSilver = (5 - CHEST_SILVER) * (5 - CHEST_SILVER);
    int rangeGold = (5 - CHEST_GOLD) * (5 - CHEST_GOLD);
    
    int total = rangeRusty + rangeBronze + rangeSilver + rangeGold;
    
    int randVal = rand() % total;
    
    int chestType = -1;
    
    if (randVal >= 0 && randVal < rangeRusty) {
        chestType = CHEST_RUSTY;
    }
    else if (randVal >= rangeRusty && randVal < (rangeRusty + rangeBronze)) {
        chestType = CHEST_BRONZE;
    }
    else if (randVal >= (rangeRusty + rangeBronze) && randVal < (rangeRusty + rangeBronze + rangeSilver)) {
        chestType = CHEST_SILVER;
    }
    else {
        chestType = CHEST_GOLD;
    }
    
    if (chestType == CHEST_RUSTY) {
        return new Chest(DEFAULT_CHEST_SHAPE, DEFAULT_CHEST_LOCKED, CHEST_RUSTY);
        //return new Chest((char)('0'+CHEST_RUSTY), DEFAULT_CHEST_LOCKED, CHEST_RUSTY);
    }
    else if (chestType == CHEST_BRONZE) {
        return new Chest(DEFAULT_CHEST_SHAPE, DEFAULT_CHEST_LOCKED, CHEST_BRONZE);
        //return new Chest((char)('0'+CHEST_BRONZE), DEFAULT_CHEST_LOCKED, CHEST_BRONZE);
    }
    else if (chestType == CHEST_SILVER) {
        return new Chest(DEFAULT_CHEST_SHAPE, DEFAULT_CHEST_LOCKED, CHEST_SILVER);
        //return new Chest((char)('0'+CHEST_SILVER), DEFAULT_CHEST_LOCKED, CHEST_SILVER);
    }
    else { // if (chestType == CHEST_GOLD) {
        return new Chest(DEFAULT_CHEST_SHAPE, DEFAULT_CHEST_LOCKED, CHEST_GOLD);
        //return new Chest((char)('0'+CHEST_GOLD), DEFAULT_CHEST_LOCKED, CHEST_GOLD);
    }
}
