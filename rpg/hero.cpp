#include <iostream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "item.h"
#include "unit.h"
#include "inventory.h"
#include "backpack.h"
#include "paperdoll.h"
#include "board.h"
#include "hero.h"
#include "prop.h"
#include "tree.h"
#include "magicbook.h"
#include "magic.h"
#include "car.h"
#include "statistics.h"

#include "sim.h"
extern Sim *sim;

// Default Constructor
Hero::Hero() : Unit(DEFAULT_HERO_SHAPE, -1, -1, DEFAULT_HERO_HP, DEFAULT_HERO_HP_MAX,
                    DEFAULT_HERO_MELEE_ATK, DEFAULT_HERO_RANGE_ATK, DEFAULT_HERO_GOLD,
                    DEFAULT_HERO_EXP, DEFAULT_LEVEL, DEFAULT_MAX_EXP_TO_LEVEL_UP,
                    DEFAULT_HERO_FREEZE) {
    
    viewportRangeRow = DEFAULT_HERO_VIEWPORT_RANGE_ROW;
    viewportRangeCol = DEFAULT_HERO_VIEWPORT_RANGE_COL;
    nightRange = DEFAULT_HERO_NIGHT_RANGE;
    
    def = DEFAULT_HERO_DEF;
    mp = DEFAULT_HERO_MP;
    maxMp = DEFAULT_HERO_MP_MAX;
    heroFacingDirection = MOVE_DIR_NORTH;
    job = DEFAULT_HERO_JOB;
    onCar = false;
    
    initStorage();
    initClassEquipment();
    
    car = NULL;
}

// General Constructor
Hero::Hero(char shape, int row, int col)
    : Unit(shape, row, col, DEFAULT_HERO_HP, DEFAULT_HERO_HP_MAX,
           DEFAULT_HERO_MELEE_ATK, DEFAULT_HERO_RANGE_ATK ,DEFAULT_HERO_GOLD,
           DEFAULT_HERO_EXP, DEFAULT_LEVEL, DEFAULT_MAX_EXP_TO_LEVEL_UP,
           DEFAULT_HERO_FREEZE) {
    viewportRangeRow = DEFAULT_HERO_VIEWPORT_RANGE_ROW;
    viewportRangeCol = DEFAULT_HERO_VIEWPORT_RANGE_COL;
    nightRange = DEFAULT_HERO_NIGHT_RANGE;

    def = DEFAULT_HERO_DEF;
    mp = DEFAULT_HERO_MP;
    maxMp = DEFAULT_HERO_MP_MAX;
    heroFacingDirection = MOVE_DIR_NORTH;
    job = DEFAULT_HERO_JOB;
    onCar = false;
        
    initStorage();
    initClassEquipment();
    
    car = NULL;
}

Hero::Hero(char shape, int hp, int maxHp, int mp, int maxMp, int meeleAtk, int rangeAtk, int def, int job)
    : Unit(shape, row, col, hp, maxHp, meeleAtk, rangeAtk,
       DEFAULT_HERO_GOLD, DEFAULT_HERO_EXP, DEFAULT_LEVEL,
       DEFAULT_MAX_EXP_TO_LEVEL_UP, DEFAULT_HERO_FREEZE) {
    
    viewportRangeRow = DEFAULT_HERO_VIEWPORT_RANGE_ROW;
    viewportRangeCol = DEFAULT_HERO_VIEWPORT_RANGE_COL;
    nightRange = DEFAULT_HERO_NIGHT_RANGE;
   
    this->def = def;
    this->mp = mp;
    this->maxMp = maxMp;
    heroFacingDirection = MOVE_DIR_NORTH;
    this->job = job;
    onCar = false;

    initStorage();
    initClassEquipment();
    
    car = NULL;
}

Hero::Hero(char shape, int hp, int maxHp, int mp, int maxMp, int meeleAtk, int rangeAtk, int gold,
           int exp, int level, int currentMaxExpToLevelUp, bool freeze,
           int viewportRangeRow, int viewportRangeCol, int nightRange, int maxNumSlots, int backpackCapacity)
    : Unit(shape, -1, -1, hp, maxHp, meeleAtk, rangeAtk, gold, exp, level,
           currentMaxExpToLevelUp, freeze) {
    this->viewportRangeRow = viewportRangeRow;
    this->viewportRangeCol = viewportRangeCol;
    this->nightRange = nightRange;
        
    def = DEFAULT_HERO_DEF;
    this->mp = mp;
    this->maxMp = maxMp;
    heroFacingDirection = MOVE_DIR_NORTH;
    job = DEFAULT_HERO_JOB;
    onCar = false;
       
    initStorage();    
    initClassEquipment();
    
    car = NULL;
}

void Hero::initClassEquipment() {
    if (job == HERO_JOB_KNIGHT) {
        slots->setItemAtIndex(0, new Weapon(WEAPON_ONE_HAND_SHAPE, "Wooden Sword", 1000, 1, 15, 500, 1, false, WEAPON_WOOD, HERO_JOB_KNIGHT));
        slots->setItemAtIndex(1, new Weapon(WEAPON_ONE_HAND_SHAPE, "Wooden Sword", 1000, 1, 15, 500, 1, false, WEAPON_WOOD, HERO_JOB_KNIGHT));
    }
    if (job == HERO_JOB_PALADIN) {
        slots->setItemAtIndex(0, new Weapon(WEAPON_TWO_HAND_SHAPE, "Wooden Axe", 2000, 1, 20, 2000, 2, false, WEAPON_WOOD, HERO_JOB_PALADIN));
    }
    if (job == HERO_JOB_WARRIOR) {
        slots->setItemAtIndex(0, new Weapon(WEAPON_TWO_HAND_SHAPE, "Wooden Hammer", 2000, 1, 30, 2000, 2, false, WEAPON_WOOD, HERO_JOB_WARRIOR));
    }
    if (job == HERO_JOB_HUNTER) {
        slots->setItemAtIndex(0, new Weapon(WEAPON_BOW_SHAPE, "Wooden Crossbow", 2000, 1, 20, 1000, 2, true, WEAPON_WOOD, HERO_JOB_HUNTER));
    }
    if (job == HERO_JOB_ARCHER) {
        slots->setItemAtIndex(0, new Weapon(WEAPON_BOW_SHAPE, "Wooden Bow", 2000, 1, 25, 1000, 2, true, WEAPON_WOOD, HERO_JOB_ARCHER));
    }
}

void Hero::initStorage() {
    slots = new Inventory(DEFAULT_SLOTS_MAX_NUM_ITMES);
    backpack = new Backpack(DEFAULT_BACKPACK_CAPACITY);
    paperdoll = new Paperdoll();
    magicbook = new Magicbook();    
}

Hero::~Hero() {
    destroyStorage();
    car = NULL;
}

void Hero::destroyStorage() {
    if (slots != NULL) {
        delete slots;
        slots = NULL;
    }
    if (backpack != NULL) {
        delete backpack;
        backpack = NULL;
    }
    if (paperdoll != NULL) {
        delete paperdoll;
        paperdoll = NULL;
    }
    if (magicbook != NULL) {
        delete magicbook;
        magicbook = NULL;
    }
}

void Hero::printStat(int slotsStartIndex, bool showBackpack, int backpackStartIndex) {
    Unit::printStat(slotsStartIndex, showBackpack, backpackStartIndex);
    
    //--------------------------------------------------------------------------
    // Line #5
    //--------------------------------------------------------------------------
    // Player 1
    if (slots != NULL) {
        cout << "  | Inventory ";
        slots->print();
        cout << setw(40) << " " << "|";
        cout << endl;
    }
    
    //--------------------------------------------------------------------------
    // Line #6
    //--------------------------------------------------------------------------
    // Player 1
    if (slots != NULL) {
        cout << "  |           ";
        slots->printIndex(slotsStartIndex);
        cout << setw(40) << " " << "|";
        cout << endl;
    }
    
    //--------------------------------------------------------------------------
    // Line #7
    //--------------------------------------------------------------------------
    // Player 1
    if (showBackpack) {
        if (backpack != NULL) {
            cout << "  | Backpack  ";
            backpack->print();
            cout << setw(30) << " " << "|";
            cout << endl;
        }
    }
    
    //--------------------------------------------------------------------------
    // Line #8
    //--------------------------------------------------------------------------
    if (showBackpack) {
        if (backpack != NULL) {
            cout << "  |           ";
            backpack->printIndex(backpackStartIndex);
            cout << setw(30) << " " << "|";
            cout << endl;
        }
    }
    
    //--------------------------------------------------------------------------
    // Line #8
    //--------------------------------------------------------------------------
    if (magicbook != NULL) {
        cout << "  | Magicbook ";
        magicbook->print();
        cout << setw(44) << " " << "|";
        cout << endl;
    }
    
    //--------------------------------------------------------------------------
    // Line #9
    //--------------------------------------------------------------------------
    if (paperdoll != NULL) {
        cout << "  | ";
        paperdoll->print();
        cout << " |" << endl;
        cout << "  | ";
        paperdoll->printIndex();
        cout << " |" << endl;
    }
    
    //--------------------------------------------------------------------------
    // Line #9.5
    //--------------------------------------------------------------------------
    if (paperdoll != NULL) {
        Weapon *leftHand = paperdoll->getWeapon(BODY_PART_ID_LEFT_HAND);
        Weapon *rightHand = paperdoll->getWeapon(BODY_PART_ID_RIGHT_HAND);
        
        cout << "  | Left Weapon  :";
        if (leftHand != NULL) {
            leftHand->printPartSpec();
        }
        else {
            cout << setw(46) << " ";
        }
        cout << " |" << endl;
        
        cout << "  | Right Weapon :";
        if (rightHand != NULL) {
            rightHand->printPartSpec();
        }
        else {
            cout << setw(46) << " ";
        }
        cout << " |" << endl;
        
        
        
    }
    
    //--------------------------------------------------------------------------
    // Line #10
    //--------------------------------------------------------------------------
    cout << "  +--------------------------------------------------------------+"<< endl;
}

void Hero::printStatDual(int slotsStartIndex, bool showBackpack, int backpackStartIndex,
                         Unit *unit2, int slotsStartIndex2, bool showBackpack2, int backpackStartIndex2) {
    Unit::printStatDual(slotsStartIndex, showBackpack, backpackStartIndex,
                        unit2, slotsStartIndex2, showBackpack2, backpackStartIndex2);

    Hero *hero2 = (Hero *)unit2;
    
    //--------------------------------------------------------------------------
    // Line #5
    //--------------------------------------------------------------------------
    // Player 1
    if (slots != NULL) {
        cout << "  | Inventory ";
        slots->print();
        cout << setw(40) << " " << "|";
    }
    
    // Gap
    cout << GAP_BETWEEN_PLAYERS_STAT;
    
    // Player 2
    if (hero2->slots != NULL) {
        cout << "  | Inventory ";
        hero2->slots->print();
        cout << setw(40) << " " << "|";
    }
    cout << endl;
    
    //--------------------------------------------------------------------------
    // Line #6
    //--------------------------------------------------------------------------
    // Player 1
    if (slots != NULL) {
        cout << "  |           ";
        slots->printIndex(slotsStartIndex);
        cout << setw(40) << " " << "|";
    }
    
    // Gap
    cout << GAP_BETWEEN_PLAYERS_STAT;
    
    // Player 2
    if (hero2->slots != NULL) {
        cout << "  |           ";
        hero2->slots->printIndex(slotsStartIndex);
        cout << setw(40) << " " << "|";
    }
    cout << endl;
    
    //--------------------------------------------------------------------------
    // Line #7
    //--------------------------------------------------------------------------
    // Player 1
    if (showBackpack) {
        if (backpack != NULL) {
            cout << "  | Backpack  ";
            backpack->print();
            cout << setw(30) << " " << "|";
        }
    }
    else {
        if (showBackpack2) {
            cout << "  |" << setw(62) << " " << "|";
        }
    }
    
    // Gap
    if (showBackpack || showBackpack2) {
        cout << GAP_BETWEEN_PLAYERS_STAT;
    }
    
    // Player 2
    if (showBackpack2) {
        if (hero2->backpack != NULL) {
            cout << "  | Backpack  ";
            hero2->backpack->print();
            cout << setw(30) << " " << "|";
        }
        cout << endl;
    }
    else {
        if (showBackpack) {
            cout << "  |" << setw(62) << " " << "|";
            cout << endl;
        }
    }
    
    //--------------------------------------------------------------------------
    // Line #8
    //--------------------------------------------------------------------------
    if (showBackpack) {
        if (backpack != NULL) {
            cout << "  |           ";
            backpack->printIndex(backpackStartIndex);
            cout << setw(30) << " " << "|";
        }
    }
    else {
        if (showBackpack2) {
            cout << "  |" << setw(62) << " " << "|";
        }
    }
    
    // Gap
    if (showBackpack || showBackpack2) {
        cout << GAP_BETWEEN_PLAYERS_STAT;
    }
    
    // Player 2
    if (showBackpack2) {
        if (hero2->backpack != NULL) {
            cout << "  |           ";
            hero2->backpack->printIndex(backpackStartIndex);
            cout << setw(30) << " " << "|";
        }
        cout << endl;
    }
    else {
        if (showBackpack) {
            cout << "  |" << setw(62) << " " << "|";
            cout << endl;
        }
    }
    
    //--------------------------------------------------------------------------
    // Line #8.5
    //--------------------------------------------------------------------------
    
    if (magicbook != NULL) {
        cout << "  | Magicbook ";
        magicbook->print();
        cout << setw(44) << " " << "|";
    }
    
    // Gap
    cout << GAP_BETWEEN_PLAYERS_STAT;
    
    // Player 2
    if (hero2->magicbook != NULL) {
        cout << "  | Magicbook ";
        hero2->magicbook->print();
        cout << setw(44) << " " << "|";
    }
    cout << endl;
    
    //--------------------------------------------------------------------------
    // Line #9
    //--------------------------------------------------------------------------
    if (paperdoll != NULL) {
        cout << "  | ";
        paperdoll->print();
        cout << " |            | ";
        hero2->paperdoll->print();
        cout << " |" << endl;
        
        cout << "  | ";
        paperdoll->printIndex();
        cout << " |            | ";
        hero2->paperdoll->printIndex();
        cout << " |" << endl;
    }
    
    //--------------------------------------------------------------------------
    // Line #9.5
    //--------------------------------------------------------------------------
    if (paperdoll != NULL) {
        Weapon *leftHand1 = paperdoll->getWeapon(BODY_PART_ID_LEFT_HAND);
        Weapon *rightHand1 = paperdoll->getWeapon(BODY_PART_ID_RIGHT_HAND);
        
        Weapon *leftHand2 = hero2->paperdoll->getWeapon(BODY_PART_ID_LEFT_HAND);
        Weapon *rightHand2 = hero2->paperdoll->getWeapon(BODY_PART_ID_RIGHT_HAND);
        
        cout << "  | Left Weapon  : ";
        if (leftHand1 != NULL) {
            leftHand1->printPartSpec();
        }
        else {
            cout << setw(46) << " ";
        }
        cout << "|            | Left Weapon  : ";
        if (leftHand2 != NULL) {
            leftHand2->printPartSpec();
        }
        else {
            cout << setw(46) << " ";
        }
        cout << "|" << endl;
        
        cout << "  | Right Weapon : ";
        if (rightHand1 != NULL) {
            rightHand1->printPartSpec();
        }
        else {
            cout << setw(46) << " ";
        }
        cout << "|            | Right Weapon : ";
        if (rightHand2 != NULL) {
            rightHand2->printPartSpec();
        }
        else {
            cout << setw(46) << " ";
        }
        cout << "|" << endl;
        
    }
    
    //--------------------------------------------------------------------------
    // Line #10
    //--------------------------------------------------------------------------
    cout << "  +--------------------------------------------------------------+";
    
    // Gap
    cout << GAP_BETWEEN_PLAYERS_STAT;
    
    cout << "  +--------------------------------------------------------------+" << endl;
}

void Hero::showItemsListToSell() {
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Slots <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    
    int curIndexSlots = 0;
    slots->resetIter();
    
    while (slots->hasMore()) {
        Item *curItem = slots->next();
        cout << setw(3) << curIndexSlots << ": ";
        if (curItem != NULL) {
            curItem->printFullSpec();
        }
        else {
            cout << "<< Empty >>";
        }
        cout << endl;
        
        curIndexSlots++;
    }
    
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Backpack <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    
    int curIndexBackpack = 100;
    backpack->resetIter();
    
    while (backpack->hasMore()) {
        Item *curItem = backpack->next();
        cout << setw(3) << curIndexBackpack << ": ";
        curItem->printFullSpec();
        cout << endl;
        
        curIndexBackpack++;
    }
}

int Hero::getViewportRangeRow() {
    return viewportRangeRow;
}

void Hero::setViewportRangeRow(int viewportRangeRow) {
    this->viewportRangeRow = viewportRangeRow;
}

int Hero::getViewportRangeCol() {
    return viewportRangeCol;
}

void Hero::setViewportRangeCol(int viewportRangeCol) {
    this->viewportRangeCol = viewportRangeCol;
}

int Hero::getNightRange() {
    slots->resetIter();
    
    while (slots->hasMore()) {
        Item *curItem = slots->next();
        if (curItem != NULL && curItem->isReusable() && ((ReusableItem *)curItem)->isTorch()) {
            return ((Torch *)curItem)->getRange();
        }
    }
    
    backpack->resetIter();
    
    while (backpack->hasMore()) {
        Item *curItem = backpack->next();
        if (curItem != NULL && curItem->isReusable() && ((ReusableItem *)curItem)->isTorch()) {
            return ((Torch *)curItem)->getRange();
        }
    }

    return nightRange;
}

bool Hero::getOnCar() {
    return onCar;
}

void Hero::setOnCar(int onCar) {
    this->onCar = onCar;
}

int Hero::getJob() {
    return job;
}

bool Hero::isHero() {
    return true;
}

bool Hero::unlock(Prop *prop) {
    int propLockLevel = prop->getLockLevel();

    Key *bestKey = NULL;
    Key *bestKeyFromSlots = slots->checkBestKey();
    Key *bestKeyFromBackpack = backpack->checkBestKey();

    if (bestKeyFromSlots == NULL && bestKeyFromBackpack == NULL) {
        return false;
    }
    else if (bestKeyFromSlots == NULL) {
        if (propLockLevel > bestKeyFromBackpack->getKeyType()) {
            return false;
        }
        bestKey = backpack->getBestKey();
    }
    else if (bestKeyFromBackpack == NULL) {
        if (propLockLevel > bestKeyFromSlots->getKeyType()) {
            return false;
        }
        bestKey = slots->getBestKey();
    }
    else { // both keys are not null
        if (bestKeyFromSlots->getKeyType() < bestKeyFromBackpack->getKeyType()) {
            if (propLockLevel > bestKeyFromBackpack->getKeyType()) {
                return false;
            }
            bestKey = backpack->getBestKey();
        }
        else {
            if (propLockLevel > bestKeyFromSlots->getKeyType()) {
                return false;
            }
            bestKey = slots->getBestKey();
        }
    }
    
    int keyType = -1;
    keyType = bestKey->getKeyType();

    int openChestChance = -1;
    
    #define UNLOCK_PERC_RANGE 100
    if (propLockLevel == keyType) {
        openChestChance = 33;
    }
    else if (keyType - propLockLevel == 1) {
        openChestChance = 60;
    }
    else if (keyType - propLockLevel == 2) {
        openChestChance = 75;
    }
    else if (keyType - propLockLevel == 3) {
        openChestChance = 90;
    }
    
    if (openChestChance == -1) {
        return false;
    }
    
    int temp = rand() % UNLOCK_PERC_RANGE;
    
    if (temp < openChestChance) {
        return true;
    }
    
    return false;
    
}

Inventory *Hero::getSlots() {
    return slots;
}

bool Hero::useItemInSlots(int indexOfItem) {
    if (slots != NULL) {
        return slots->use(indexOfItem, this);
    }
    return false;
}

void Hero::addPotion(int amount) {
    slots->addPotion(amount, this);
}

bool Hero::buyPotion(int amount) {
    if (slots->buyPotion(amount, this)) {
        return true;
    } else {
        return false;
    }
}

Magicbook *Hero::getMagicbook() {
    return magicbook;
}

bool Hero::useMagicInMagicbook(int indexOfItem) {
    if (magicbook != NULL) {
        return magicbook->cast(indexOfItem, this);
    }
    return false;
}

bool Hero::addMagicToMagicbook(Magic *magic) {
    return magicbook->add(magic);
}

Car *Hero::getCar() {
    return car;
}

void Hero::getInCar(Car *car) {
    this->car = car;
    sim->board->setUnit(row, col, NULL);
    row = car->getRow();
    col = car->getCol();
    
    onCar = true;
    car->setIdle(false);
}

void Hero::getOffCar() {
    car = NULL;
    onCar = false;
}

void Hero::setHeroFacingDirection(int heroFacingDirection) {
    this->heroFacingDirection = heroFacingDirection;
}

Weapon *Hero::getRightHand() {
    return paperdoll->getWeapon(BODY_PART_ID_RIGHT_HAND);
}

Weapon *Hero::getLeftHand() {
    return paperdoll->getWeapon(BODY_PART_ID_LEFT_HAND);
}

bool Hero::moveItemSlotToBackpack(int indexSlotItem) {
    if (slots == NULL) {
        cout << "error: this unit does not have slots!!" << endl;
        return false;
    }
    
    if (backpack == NULL) {
        cout << "error: this unit does not have a backpack!!" << endl;
        return false;
    }
    
    if (indexSlotItem < 0 || indexSlotItem >= slots->getMaxNumItems()) {
        cout << "error: you entered an invalid index of the slots!!" << endl;
        return false;
    }
    
    // check whether the slot has an item or not.
    if (slots->get(indexSlotItem) == NULL) {
        cout << "error: you MUST enter the index of the slot which has an item!!" << endl;
        return false;
    }
    
    // check whether the backpack is full.
    if (backpack->isFull()) {
        cout << "error: the backpack is full!!" << endl;
        return false;
    }
    
    backpack->push(slots->remove(indexSlotItem));
    return true;
}

bool Hero::moveItemBackpackToSlot(int indexBackpack, int indexSlotItem) {
    if (slots == NULL) {
        cout << "error: this unit does not have slots!!" << endl;
        return false;
    }
    
    if (backpack == NULL) {
        cout << "error: this unit does not have a backpack!!" << endl;
        return false;
    }
    
    if (indexSlotItem < 0 || indexSlotItem >= slots->getMaxNumItems()) {
        cout << "error: you entered an invalid index of the slots!!" << endl;
        return false;
    }
    
    if (indexBackpack < 0 || indexBackpack >= backpack->size()) {
        cout << "error: you entered an invalid index of the backpack item!!" << endl;
        return false;
    }
    
    // check whether the index of the slot is empty.
    if (slots->get(indexSlotItem) != NULL) {
        cout << "error: the index of the slots is occupied!!" << endl;
        return false;
    }
    
    slots->setItemAtIndex(indexSlotItem, backpack->removeItemAt(indexBackpack));
    return true;
}

bool Hero::moveItemSlotToSlot(int indexSlotItem, int indexSlotItem2) {
    
    if (slots == NULL) {
        cout << "error: this unit does not have a slot!!" << endl;
        return false;
    }
    
    if (indexSlotItem < 0 || indexSlotItem >= slots->getMaxNumItems()) {
        cout << "error: you entered an invalid index of the slots!!" << endl;
        return false;
    }
    
    if (indexSlotItem2 < 0 || indexSlotItem2 >= slots->getMaxNumItems()) {
        cout << "error: you entered an invalid index of the slot item!!" << endl;
        return false;
    }
    
    // check whether the backpack has an item or not.
    if (slots->get(indexSlotItem) == NULL) {
        cout << "error: you MUST enter the index of the slot which has an item!!" << endl;
        return false;
    }
    
    // check whether the index of the slot is empty.
    if (slots->get(indexSlotItem2) != NULL) {
        cout << "error: the index of the slots is occupied!!" << endl;
        return false;
    }
    
    slots->setItemAtIndex(indexSlotItem2, slots->remove(indexSlotItem));
    return true;
}

bool Hero::equip(Item *item) {
    if (paperdoll == NULL || !isHero()) {
        return false;
    }
    
    return paperdoll->equip(item, this);
}

Item *Hero::unequip(int bodyPartID) {
    if (paperdoll == NULL || !isHero()) {
        return NULL;
    }
    
    return paperdoll->unequip(bodyPartID, this);
}

bool Hero::hasRoom() {
    return !(slots->isFull() && backpack->isFull());
}

// pre-condition: hasRoom() == true
void Hero::receiveItem(Item *item) {
    if (!slots->isFull()) {
        slots->add(item);
    }
    else if (!backpack->isFull()) {
        backpack->push(item);
    }
}

Item *Hero::removeItemByIndex(int index) {
    // is the index for slots
    if (index >= 0 && index < slots->capacity()) {
        return slots->remove(index);
    }
    // is the index for backpack
    else if (index >= 100 && index < backpack->size()+100) {
        index -= 100;
        return backpack->removeItemAt(index);
    }
    
    return NULL;
}

void Hero::effect(Unit *unit, Item *item, Prop *prop, int skillNumber) {
    if (unit != NULL) {
        for (int i = 0; i < magicbook->capacity(); i++) {
            if (magicbook != NULL && magicbook->get(i) != NULL && magicbook->getSkillNumberAtIndex(i) == skillNumber) {
                magicbook->get(i)->effect(this, unit, item, prop);
            }
        }
    }
}

void Hero::freezeMons(int startRow, int startCol) {
    for (int i = startRow-1; i <= startRow+1; i++) {
        for (int j = startCol-1; j <= startCol+1; j++) {
            if (sim->board->validate(i, j) &&
                sim->board->getUnit(i, j) != NULL &&
                !sim->board->getUnit(i, j)->isBoss() &&
                sim->board->getUnit(i, j)->isMon()) {
                sim->board->getUnit(i, j)->setFreeze(true);
            }
        }
    }
}

void Hero::unfreezeMons(int startRow, int startCol) {
    for (int i = startRow-1; i <= startRow+1; i++) {
        for (int j = startCol-1; j <= startCol+1; j++) {
            if (sim->board->validate(i, j) &&
                sim->board->getUnit(i, j) != NULL &&
                !sim->board->getUnit(i, j)->isBoss() &&
                sim->board->getUnit(i, j)->isMon()) {
                sim->board->getUnit(i, j)->setFreeze(false);
            }
        }
    }
}

bool Hero::rangeAttack(int dir) {
    if (onCar) {
        return false;
    }
    
    if ((getRightHand() != NULL && getRightHand()->getRangeAttack())
        || (getLeftHand() != NULL && getLeftHand()->getRangeAttack())) {
        
        Arrow *arrow = new Arrow(getRangeAtk(), heroFacingDirection, this);
        
        if (dir == MOVE_DIR_NORTH) {
            if (sim->board->validate(row-1, col)) {
                sim->board->setThrowingItem(row-1, col, arrow);
                return true;
            }
        }
        else if (dir == MOVE_DIR_EAST) {
            if (sim->board->validate(row, col+1)) {
                sim->board->setThrowingItem(row, col+1, arrow);
                return true;
            }
        }
        else if (dir == MOVE_DIR_SOUTH) {
            if (sim->board->validate(row+1, col)) {
                sim->board->setThrowingItem(row+1, col, arrow);
                return true;
            }
        }
        else if (dir == MOVE_DIR_WEST) {
            if (sim->board->validate(row, col-1)) {
                sim->board->setThrowingItem(row, col-1, arrow);
                return true;
            }
        }
    }
    
    return false;
}

void Hero::move(int moveDir) {
    if (onCar) {
        car->changeDirection(moveDir);
        return;
    }
    
    if (heroFacingDirection != moveDir) {
        heroFacingDirection = moveDir;
        return;
    }
    else {
        heroFacingDirection = moveDir;
    }
    
    // move hero
    bool moved = false;
    int prevRow = row;
    int prevCol = col;
    int nextRow = row;
    int nextCol = col;
    
    Unit *unit = sim->board->getUnit(row, col);
    
    if (moveDir == MOVE_DIR_NORTH) {
        nextRow = row - 1;
    }
    else if (moveDir == MOVE_DIR_EAST) {
        nextCol = col + 1;
    }
    else if (moveDir == MOVE_DIR_SOUTH) {
        nextRow = row + 1;
    }
    else if (moveDir == MOVE_DIR_WEST) {
        nextCol = col - 1;
    }
    
    if (sim->board->isClimbable(nextRow, nextCol)) {
        moved = true;
    }
    
    
    if (moved && !onCar) {
        sim->board->setUnit(prevRow, prevCol, NULL);
        sim->board->setUnit(nextRow, nextCol, unit);
        sim->stat->totalDistHeroMoved++;
        unitCurDir = moveDir;
    }
    if (!moved) {
        if (sim->board->validate(nextRow, nextCol) &&
            sim->board->getProp(nextRow, nextCol) != NULL &&
            sim->board->getProp(nextRow, nextCol)->isChest()) {
            sim->board->getProp(nextRow, nextCol)->trigger(nextRow, nextCol, this);
        }
    }
    
    // interact with other units: buy, sell, battle...
    if (!moved) {
        if (sim->board->validate(nextRow, nextCol) &&
            sim->board->getUnit(nextRow, nextCol) != NULL) {
            sim->board->getUnit(nextRow, nextCol)->interact(this);
        }
    }
    
    // pick up item
    if (moved) {
        Item *item = sim->board->getItem(row, col);
        
        if (item != NULL && item->canPickUp() && (!slots->isFull() || !backpack->isFull())) {
            sim->board->setItem(row, col, NULL);
            if (!slots->isFull()) {
                slots->add(item);
            }
            else if (!backpack->isFull()) {
                backpack->push(item);
            }
        }
    }
    
    // unfreeze/freeze mons
    if (moved) {
        unfreezeMons(prevRow, prevCol);
        freezeMons(nextRow, nextCol);
    }
    
    if (moved) {
        if (sim->board->getProp(row, col) != NULL && sim->board->getProp(nextRow, nextCol)->isExit()) {
            sim->board->setExited(true);
        }
    }
}

string Hero::getID() {
    return string(UNIT_ID_HERO);
}

void Hero::save(ostream &out) {
    Unit::save(out);
    out << "#-------------------- class Hero" << endl;
    
    out << "# viewportRangeRow" << endl;
    out << viewportRangeRow << endl;
    
    
    out << "# viewportRangeCol" << endl;
    out << viewportRangeCol << endl;
    
    
    out << "# job" << endl;
    out << job << endl;
    
    
    out << "# nightRange" << endl;
    out << nightRange << endl;
    
    
    out << "# onCar" << endl;
    out << onCar << endl;
    
    out << "#--------------------------------------- slots" << endl;
    slots->save(out);
    
    out << "#--------------------------------------- backpack" << endl;
    backpack->save(out);

    out << "#--------------------------------------- paperdoll" << endl;
    paperdoll->save(out);

    out << "#--------------------------------------- magicbook" << endl;
    magicbook->save(out);
    
    // skip car
}

/*
 Inventory *slots;
 Backpack *backpack;
 Paperdoll *paperdoll;
 Magicbook *magicbook;
 Car *car;
*/
void Hero::load(istream &in) {
    cout << "Hero::load(): started" << endl;;
    
    Unit::load(in);
    char buf[MAX_LEN_BUF];
    
    destroyStorage();
    
    initStorage();

    //out << "#-------------------- class Hero" << endl;
    in.getline(buf, 80); // skip comment
    cout << "Hero::load(): buf=" << buf << endl;

    //out << "# viewportRangeRow" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << viewportRangeRow << endl;
    in >> viewportRangeRow;
    in.get(); // skip enter code.
    
    //out << "# viewportRangeCol" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << viewportRangeCol << endl;
    in >> viewportRangeCol;
    in.get(); // skip enter code.
    
    //out << "# job" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << job << endl;
    in >> job;
    in.get(); // skip enter code.
    
    //out << "# nightRange" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << nightRange << endl;
    in >> nightRange;
    in.get(); // skip enter code.
    
    //out << "# onCar" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << onCar << endl;
    in >> onCar;
    in.get(); // skip enter code.
    
    cout << "Hero::load(): Loading slots" << endl;

    //out << "#--------------------------------------- slots" << endl;
    in.getline(buf, 80); // skip comment
    cout << "Hero::load(): buf=" << buf << endl;

    slots->load(in);
    
    cout << "Hero::load(): Loading backpack" << endl;

    //out << "#--------------------------------------- backpack" << endl;
    in.getline(buf, 80); // skip comment
    cout << "Hero::load(): buf=" << buf << endl;

    backpack->load(in);
    
    cout << "Hero::load(): Loading paperdoll" << endl;

    //out << "#--------------------------------------- paperdoll" << endl;
    in.getline(buf, 80); // skip comment
    cout << "Hero::load(): buf=" << buf << endl;

    paperdoll->load(in);
    
    cout << "Hero::load(): Loading magicbook" << endl;

    //out << "#--------------------------------------- magicbook" << endl;
    in.getline(buf, 80); // skip comment
    cout << "Hero::load(): buf=" << buf << endl;

    magicbook->load(in);
    
    // skip car
    car = NULL;
}