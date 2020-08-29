#include <iostream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "item.h"
#include "prop.h"
#include "inventory.h"
#include "backpack.h"
#include "paperdoll.h"
#include "unit.h"
#include "hero.h"
#include "mon.h"
#include "boss.h"
#include "merchant.h"
#include "dragon.h"
#include "car.h"

// Default Constructor
Unit::Unit() {
    shape = DEFAULT_UNIT_SHAPE;
    hp = DEFAULT_UNIT_HP;
    maxHp = DEFAULT_UNIT_HP_MAX;
    meleeAtk = DEFAULT_UNIT_MELEE_ATK;
    rangeAtk = DEFAULT_UNIT_RANGE_ATK;
    gold = DEFAULT_UNIT_GOLD;
    exp = DEFAULT_UNIT_EXP;
    level = DEFAULT_LEVEL;
    currentMaxExpToLevelUp = DEFAULT_MAX_EXP_TO_LEVEL_UP;
    
    freeze = DEFAULT_UNIT_FREEZE;
    
    unitEngaged = NULL;
    
    unitCurDir = -1;
}
// General Constructor
Unit::Unit(char shape, int row, int col, int hp, int maxHp, int meleeAtk, int rangeAtk,int gold, int exp, int level, int currentMaxExpToLevelUp, bool freeze) {
    this->shape = shape;
    this->row = row;
    this->col = col;
    this->hp = hp;
    this->maxHp = maxHp;
    this->meleeAtk = meleeAtk;
    this->rangeAtk = rangeAtk;
    this->gold = gold;
    this->exp = exp;
    this->level = level;
    this->currentMaxExpToLevelUp = currentMaxExpToLevelUp;
    
    this->freeze = freeze;
    
    unitEngaged = NULL;
    
    unitCurDir = -1;
}

Unit::~Unit() {
}

// this function reset hp when this unit is respawned.
void Unit::reset() {
    hp = maxHp;
    freeze = false;
}

void Unit::print() {
    cout << shape;
}

void Unit::printStat() {
    // N/A
}

void Unit::printStat(int slotsStartIndex, bool showBackpack, int backpackStartIndex) {
    
    //--------------------------------------------------------------------------
    // Line #1
    //--------------------------------------------------------------------------
    cout << "  +--------------------------------------------------------------+" << endl;
    
    //--------------------------------------------------------------------------
    // Line #2
    //--------------------------------------------------------------------------
    // Player 1
    cout << right << shape << " | HP[" << setw(4) << hp << "/" << setw(4) << maxHp
    << "] MP[" << setw(4) << mp << "/" << setw(4) << maxMp
    << "] DEF[" << setw(3) << def << "] GOLD[" << setw(6) << gold
    << "] Lvl[" << setw(2) << level << "]    |" << endl;
    
    //--------------------------------------------------------------------------
    // Line #2.5
    //--------------------------------------------------------------------------
    
    // Player 1
    cout << "  | EXP[" << setw(5) << exp << "/" << setw(5) << currentMaxExpToLevelUp
    << "] MeleeATK[" << setw(3) << meleeAtk
    << "] RangeATK[" << setw(3) << rangeAtk << "]"<< setw(18) <<  "|" << endl;
    
    
    //--------------------------------------------------------------------------
    // Line #3
    //--------------------------------------------------------------------------
    // Player 1
    if (unitEngaged != NULL) {
        unitEngaged->print();
        cout << " | HP[" << setw(4) << unitEngaged->getHp() << "/" << setw(4) << unitEngaged->getMaxHp()
        << "] ATK[" << setw(3) << unitEngaged->getMeleeAtk() << "]";
        cout << setw(39) << left << " <<< The Monster engaged!!!" << "|";
        cout << right << endl;
        
        if (unitEngaged->isDead()) {
            unitEngaged = NULL;
        }
    }
    
    //--------------------------------------------------------------------------
    // Line #4
    //--------------------------------------------------------------------------
    cout << "  +--------------------------------------------------------------+" << endl;
    
}

void Unit::printStatDual(int slotsStartIndex, bool showBackpack, int backpackStartIndex,
            Unit *unit2, int slotsStartIndex2, bool showBackpack2, int backpackStartIndex2) {
    
    //--------------------------------------------------------------------------
    // Line #1
    //--------------------------------------------------------------------------
    cout << "  +--------------------------------------------------------------+";
    
    // Gap
    cout << GAP_BETWEEN_PLAYERS_STAT;

    cout << "  +--------------------------------------------------------------+" << endl;

    //--------------------------------------------------------------------------
    // Line #2
    //--------------------------------------------------------------------------
    // Player 1
    cout << right << shape << " | HP[" << setw(4) << hp << "/" << setw(4) << maxHp
    << "] MP[" << setw(4) << mp << "/" << setw(4) << maxMp
    << "] DEF[" << setw(3) << def << "] GOLD[" << setw(6) << gold
    << "] Lvl[" << setw(2) << level << "]    |";
    
    // Gap
    cout << GAP_BETWEEN_PLAYERS_STAT;
    
    // Player 2
    cout << unit2->shape << " | HP[" << setw(4) << unit2->hp << "/" << setw(4) << unit2->maxHp
    << "] MP[" << setw(4) << unit2->mp << "/" << setw(4) << unit2->maxMp
    << "] DEF[" << setw(3) << unit2->def << "] GOLD[" << setw(6) << unit2->gold
    << "] Lvl[" << setw(2) << unit2->level << "]    |" << endl;
    
    //--------------------------------------------------------------------------
    // Line #2.5
    //--------------------------------------------------------------------------
    
    // Player 1
    cout << "  | EXP[" << setw(5) << exp << "/" << setw(5) << currentMaxExpToLevelUp
    << "] MeleeATK[" << setw(3) << meleeAtk
    << "] RangeATK[" << setw(3) << rangeAtk << "]"<< setw(18) <<  "|";

    
    // Gap
    cout << GAP_BETWEEN_PLAYERS_STAT;
    
    
   
    // Player 2
    cout << "  | EXP[" << setw(5) << unit2->exp << "/" << setw(5) << unit2->currentMaxExpToLevelUp
    << "] MeleeATK[" << setw(3) << unit2->meleeAtk
    << "] RangeATK[" << setw(3) << unit2->rangeAtk << "]"<< setw(18) <<  "|";
    cout << endl;
    
    //--------------------------------------------------------------------------
    // Line #3
    //--------------------------------------------------------------------------
    
    // Player 1
    if (unitEngaged != NULL) {
        unitEngaged->print();
        cout << " | HP[" << setw(4) << unitEngaged->getHp() << "/" << setw(4) << unitEngaged->getMaxHp()
        << "] ATK[" << setw(3) << unitEngaged->getMeleeAtk() << "] DEF[" << setw(3) << unitEngaged->getDef() << "]";
        cout << setw(31) << left << " <<< Engaged!!!               |" << right;
        
        if (unitEngaged->isDead()) {
            unitEngaged = NULL;
        }
    }
    else {
        cout << "  |" << setw(62) << " " << "|";
    }

    // Gap
    cout << GAP_BETWEEN_PLAYERS_STAT;

    // Player 2
    if (unit2->unitEngaged != NULL) {
        unit2->unitEngaged->print();
        cout << " | HP[" << setw(4) << unit2->unitEngaged->getHp() << "/" << setw(4) << unit2->unitEngaged->getMaxHp()
        << "] ATK[" << setw(3) << unit2->unitEngaged->getMeleeAtk() << "] DEF[" << setw(3) << unit2->unitEngaged->getDef() << "]";
        cout << setw(31) << left << " <<< Engaged!!!               |" << right;

        if (unit2->unitEngaged->isDead()) {
            unit2->unitEngaged = NULL;
        }
    }
    else {
        cout << "  |" << setw(62) << " " << "|";
    }
    cout << endl;
    
    //--------------------------------------------------------------------------
    // Line #4
    //--------------------------------------------------------------------------
    cout << "  +--------------------------------------------------------------+";
    
    // Gap
    cout << GAP_BETWEEN_PLAYERS_STAT;
    
    cout << "  +--------------------------------------------------------------+" << endl;
}

void Unit::showItemsListToSell() {
    // N/A
}

void Unit::setShape(char shape) {
    this->shape = shape;
}

int Unit::getRow() {
    return row;
}

void Unit::setRow(int row) {
    this->row = row;
}

int Unit::getCol() {
    return col;
}

void Unit::setCol(int col) {
    this->col = col;
}

int Unit::getHp() {
    return hp;
}

void Unit::setHp(int hp) {
    if (hp > maxHp) {
        this->hp = maxHp;
    }
    else {
        this->hp = hp;
    }
}

void Unit::incHp(int hpToInc) {
    if (hp + hpToInc > maxHp) {
        hp = maxHp;
    }
    else {
        hp += hpToInc;
    }
}

void Unit::decHp(int hpToDec) {
    if (hp - hpToDec < 0) {
        hp = 0;
    }
    else {
        hp -= hpToDec;
    }
}

int Unit::getMaxHp() {
    return maxHp;
}

void Unit::setMaxHp(int maxHp) {
    this->maxHp = maxHp;
}

int Unit::getMp() {
    return mp;
}

void Unit::setMp(int mp) {
    if (mp > maxMp) {
        this->mp = maxMp;
    }
    else {
        this->mp = mp;
    }
}

void Unit::incMp(int mpToInc) {
    if (mp + mpToInc > maxMp) {
        mp = maxMp;
    }
    else {
        mp += mpToInc;
    }
}

void Unit::decMp(int mpToDec) {
    if (mp - mpToDec < 0) {
        mp = 0;
    }
    else {
        mp -= mpToDec;
    }
}

int Unit::getMaxMp() {
    return maxMp;
}

void Unit::setMaxMp(int maxMp) {
    this->maxMp = maxMp;
}


int Unit::getMeleeAtk() {
    return meleeAtk;
}

void Unit::incMeleeAtk(int atkToInc) {
    meleeAtk += atkToInc;
}

void Unit::decMeleeAtk(int atkToDec) {
    meleeAtk -= atkToDec;
}

int Unit::getRangeAtk() {
    return rangeAtk;
}

void Unit::incRangeAtk(int atkToInc) {
    rangeAtk += atkToInc;
}

void Unit::decRangeAtk(int atkToDec) {
    rangeAtk -= atkToDec;
}

int Unit::getDef() {
    return def;
}

void Unit::incDef(int defToInc) {
    def += defToInc;
}

void Unit::decDef(int defToDec) {
    def -= defToDec;
}

int Unit::getGold() {
    return gold;
}

void Unit::setGold(int gold) {
    this->gold = gold;
}

void Unit::incGold(int goldToInc) {
    gold += goldToInc;
}

void Unit::decGold(int goldToDec) {
    gold -= goldToDec;
}

int Unit::getExp() {
    return exp;
}

void Unit::setExp(int exp) {
    this->exp = exp;
}

void Unit::incExp(int expToInc) {
    exp += expToInc;
    int levelbefore = level;
    if (exp >= currentMaxExpToLevelUp) {
        level++;
        exp = 0;
        currentMaxExpToLevelUp = level * NEXT_LEVEL_MAX_EXP_INCREMENTAL; // increase next max exp by NEXT_LEVEL_MAX_EXP_INCREMENTAL
    }
    
    if(level > levelbefore) {
        meleeAtk += NEXT_LEVEL_ATK_INCREMENTAL;
        def += NEXT_LEVEL_DEF_INCREMENTAL;
        maxHp += NEXT_LEVEL_MAX_HP_INCREMENTAL; // increase next hp by NEXT_LEVEL_HP_INCREMENTAL
        hp = maxHp;
        maxMp += NEXT_LEVEL_MAX_MP_INCREMENTAL; // increase next atk by NEXT_LEVEL_MP_INCREMENTAL
        mp = maxMp;
        
        levelbefore = level;
    }
}

void Unit::decExp(int expToDec) {
    exp -= expToDec;
}

int Unit::getCurrentMaxExpToLevelUp() {
    return currentMaxExpToLevelUp;
}
void Unit::setCurrentMaxExpToLevelUp(int currentMaxExpToLevelUp) {
    this->currentMaxExpToLevelUp = currentMaxExpToLevelUp;
}

int Unit::getLevel() {
    return level;
}
void Unit:: setLevel(int level) {
    this->level = level;
}


bool Unit::getFreeze() {
    return freeze;
}

void Unit::setFreeze(bool freeze) {
    this->freeze = freeze;
}

int Unit::getDir() {
    return 0;
}

void Unit::setDir(int dir) {
    return;
}

int Unit::getPrevDir() {
    return 0;
}

void Unit::setPrevDir(int prevDir) {
    return;
}

bool Unit::getIdle() {
    return false;
}

void Unit::setIdle(int idle) {
    return;
}

bool Unit::getOnCar() {
    return false;
}

void Unit::setOnCar(int onCar) {
    return;
}

int Unit::getViewportRangeRow() {
    return 0;
}

void Unit::setViewportRangeRow(int viewportRangeRow) {
    // N/A
}

int Unit::getViewportRangeCol() {
    return 0;
}

void Unit::setViewportRangeCol(int viewportRangeCol) {
    // N/A
}

int Unit::getNightRange() {
    return 0;
}

Unit *Unit::getUnitEngaged() {
    return unitEngaged;
}

void Unit::setUnitEngaged(Unit *unitEngaged) {
    this->unitEngaged = unitEngaged;
}

bool Unit::isDead() {
    return hp == 0;
}

void Unit::changeDirection(int moveDir) {
    
}

int Unit::getHeroFacingDirection() {
    return heroFacingDirection;
}

void Unit::setHeroFacingDirection(int heroFacingDirection) {
    this->heroFacingDirection = heroFacingDirection;
}

bool Unit::isHero() {
    // N/A
    return false;
}

bool Unit::isMon() {
    // N/A
    return false;
}

bool Unit::isBoss() {
    // N/A
    return false;
}

bool Unit::isMerchant() {
    // N/A
    return false;
}

bool Unit::isCar() {
    // N/A
    return false;
}

bool Unit::isDragon() {
    // N/A
    return false;
}

bool Unit::unlock(Prop *prop) {
    // N/A
    return false;
}

int Unit::getJob() {
    // N/A
    return -1;
}

Inventory *Unit::getSlots() {
    // N/A
    return NULL;
}

bool Unit::pickUp(Item *item) {
    // N/A
    return false;
}

bool Unit::useItemInSlots(int indexOfItem) {
    // N/A
    return false;
}

void Unit::addPotion(int amount) {
    // N/A
}

bool Unit::buyPotion(int amount) {
    // N/A
    return false;
}

Magicbook *Unit::getMagicbook() {
    // N/A
    return NULL;
}

bool Unit::useMagicInMagicbook(int indexOfItem) {
    // N/A
    return false;
}

bool Unit::addMagicToMagicbook(Magic *magic) {
    // N/A
    return false;
}

Car *Unit::getCar() {
    return NULL;
}

void Unit::getInCar(Car *car) {
    return;
}

void Unit::getOffCar() {
    return;
}

Weapon *Unit::getRightHand() {
    // N/A
    return NULL;
}

Weapon *Unit::getLeftHand() {
    // N/A
    return NULL;
}

bool Unit::moveItemSlotToBackpack(int indexSlotItem) {
    // N/A
    return false;
}

bool Unit::moveItemBackpackToSlot(int indexBackpack, int indexSlotItem) {
    // N/A
    return false;
}

bool Unit::moveItemSlotToSlot(int indexSlotItem, int indexSlotItem2) {
    // N/A
    return false;
}

bool Unit::equip(Item *item) {
    // N/A
    return false;
}

Item *Unit::unequip(int bodyPartID) {
    // N/A
    return NULL;
}

void Unit::interact(Unit *unit) {
    // N/A
}

bool Unit::hasRoom() {
    // N/A
    return false;
}

void Unit::receiveItem(Item *item) {
    // N/A
}

Item *Unit::removeItemByIndex(int index) {
    // N/A
    return NULL;
}

void Unit::effect(Unit *unit, Item *item, Prop *prop, int skillNumber) {
    // N/A
}

bool Unit::rangeAttack(int dir) {
    // N/A
    return false;
}


void Unit::save(ostream &out) {
    
    out << "#-------------------- class Unit" << endl;
    
    out << "# shape" << endl;
    out << shape << endl;
    
    out << "# unitCurDir" << endl;
    out << unitCurDir << endl;
    
    out << "# row" << endl;
    out << row << endl;
    
    
    out << "# col" << endl;
    out << col << endl;
    
    
    out << "# hp" << endl;
    out << hp << endl;
    
    
    out << "# maxHp" << endl;
    out << maxHp << endl;
    
    
    out << "# mp" << endl;
    out << mp << endl;
    
    
    out << "# maxMp" << endl;
    out << maxMp << endl;
    
    
    out << "# meleeAtk" << endl;
    out << meleeAtk << endl;
    
    
    out << "# rangeAtk" << endl;
    out << rangeAtk << endl;
    
    
    out << "# def" << endl;
    out << def << endl;
    
    
    out << "# gold" << endl;
    out << gold << endl;
    
    
    out << "# exp" << endl;
    out << exp << endl;
    
    
    out << "# currentMaxExpToLevelUp" << endl;
    out << currentMaxExpToLevelUp << endl;
    
    
    out << "# level" << endl;
    out << level << endl;
    
    
    out << "# freeze" << endl;
    out << freeze << endl;
    
    
    out << "# heroFacingDirection" << endl;
    out << heroFacingDirection << endl;

    // skip unitEngaged
}

void Unit::load(istream &in) {
    cout << "Unit::load(): started" << endl;;

    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Unit" << endl;
    in.getline(buf, 80); // skip comment
    cout << "Unit::load(): buf=" << buf << endl;

    //out << "# shape" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << shape << endl;
    in >> shape;
    in.get(); // skip enter code.
    
    //out << "# unitCurDir" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << unitCurDir << endl;
    in >> unitCurDir;
    in.get(); // skip enter code.
    
    //out << "# row" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << row << endl;
    in >> row;
    in.get(); // skip enter code.
    
    //out << "# col" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << col << endl;
    in >> col;
    in.get(); // skip enter code.
    
    //out << "# hp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << hp << endl;
    in >> hp;
    in.get(); // skip enter code.
    
    //out << "# maxHp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxHp << endl;
    in >> maxHp;
    in.get(); // skip enter code.
    
    //out << "# mp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << mp << endl;
    in >> mp;
    in.get(); // skip enter code.
    
    //out << "# maxMp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxMp << endl;
    in >> maxMp;
    in.get(); // skip enter code.
    
    //out << "# meleeAtk" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << meleeAtk << endl;
    in >> meleeAtk;
    in.get(); // skip enter code.
    
    //out << "# rangeAtk" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << rangeAtk << endl;
    in >> rangeAtk;
    in.get(); // skip enter code.
    
    //out << "# def" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << def << endl;
    in >> def;
    in.get(); // skip enter code.
    
    //out << "# gold" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << gold << endl;
    in >> gold;
    in.get(); // skip enter code.
    
    //out << "# exp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << exp << endl;
    in >> exp;
    in.get(); // skip enter code.
    
    //out << "# currentMaxExpToLevelUp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << currentMaxExpToLevelUp << endl;
    in >> currentMaxExpToLevelUp;
    in.get(); // skip enter code.
    
    //out << "# level" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << level << endl;
    in >> level;
    in.get(); // skip enter code.
    
    //out << "# freeze" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << freeze << endl;
    in >> freeze;
    in.get(); // skip enter code.
    
    //out << "# heroFacingDirection" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Unit::load(): buf=" << buf << endl;
    //out << heroFacingDirection << endl;
    in >> heroFacingDirection;
    in.get(); // skip enter code.
    
    // skip unitEngaged
    unitEngaged = NULL;
}

Unit *createUnitByShape(char shape, int row, int col) {
    if (shape == DEFAULT_HERO_SHAPE) {
        return new Hero();
    }
    else if (shape == DEFAULT_MON_SHAPE) {
        return new Mon();
    }
    else if (shape == DEFAULT_BOSS_SHAPE) {
        return new Boss();
    }
    else if (shape == DEFAULT_MERCHANT_SHAPE) {
        return new Merchant();
    }
    else if (shape == DEFAULT_CAR_SHAPE) {
        return new Car();
    }
    else if (shape == DEFAULT_DRAGON_SHAPE) {
        return createDragon(row, col, DRAGON_LEN);
    }
    
    return NULL;
}