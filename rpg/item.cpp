#include <iostream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "unit.h"
#include "prop.h"
#include "board.h"
#include "item.h"
#include "magic.h"
#include "event.h"
#include "eventqueue.h"

#include "sim.h"
extern Sim *sim;

//==============================================================================
// 1st Generation
//==============================================================================

// Default Constructor
Item::Item() {
    shape = DEFAULT_ITEM_SHAPE;
    name = DEFAULT_ITEM_NAME;
    price = DEFAULT_ITEM_PRICE;
    level = DEFAULT_ITEM_LEVEL;
    
    row = -1;
    col = -1;
    
    disposed = false;
    moved = false;
    processed = false;
    disposable = false;
    
    pickUp = true;
}

// Copy Constructor
Item::Item(Item &other) {
    //*this = other;
    shape = other.shape;
    name = other.name;
    price = other.price;
    level = other.level;
    
    row = other.row;
    col = other.row;

    disposed = other.disposed;
    moved = other.moved;
    processed = other.processed;
    disposable = other.disposable;
    
    pickUp = other.pickUp;
}

// General Constructor
Item::Item(char shape, string name, int price, bool disposable, int level) {
    this->shape = shape;
    this->name = name;
    this->price = price;
    this->level = level;
    
    row = -1;
    col = -1;

    disposed = false;
    moved = false;
    processed = false;
    this->disposable = disposable;
    
    pickUp = true;
}

Item::~Item() {}

Item &Item::operator=(Item &other) {
    shape = other.shape;
    name = other.name;
    price = other.price;
    level = other.level;
    
    disposed = other.disposed;
    moved = other.moved;
    processed = other.processed;
    disposable = other.disposable;
    
    return *this;
}

void Item::print() {
    print(cout);
}

void Item::print(ostream &out) {
    out << shape;
}

void Item::printPartSpec() {
    cout << "[";
    print(cout);
    cout << "] ";
    
    cout << setw(20) << left << name << right;
}

void Item::printFullSpec() {
    cout << "(";
    print(cout);
    cout << ") " << setw(20) << left << name << right << " Price(" << setw(6) << price << " g) Level(" << setw(2) << level << ")";
}

char Item::getShape() {
    return shape;
}

string Item::getName() {
    return name;
}

int Item::getPrice() {
    return price;
}

int Item::getLevel() {
    return level;
}

int Item::getRow() {
    return row;
}

void Item::setRow(int row) {
    this->row = row;
}

int Item::getCol() {
    return col;
}

void Item::setCol(int col) {
    this->col = col;
}

void Item::setMoved(bool moved) {
    this->moved = moved;
}

bool Item::isConsumable() {
    return false;
}

bool Item::isEquipable() {
    return false;
}

bool Item::isReusable() {
    return false;
}

void Item::trigger() {
    // N/A
}

bool Item::hasBeenDisposed() {
    return disposed;
}

bool Item::hasBeenMoved() {
    return moved;
}

bool Item::hasBeenProcessed() {
    return processed;
}

void Item::resetProcessed() {
    processed = false;
}

void Item::dispose() {
    if (disposable) {
        disposed = true;
    }
}

bool Item::canPickUp() {
    return pickUp;
}

bool Item::move(int row, int col) {
    // N/A
    return false;
}

void Item::effect(Unit *unit, Item *item, Prop *prop) {
    // N/A
}

ostream &operator<<(ostream &out, Item &item) {
    item.print(out);
    return out;
}

Item *createRandItem() {
    int randType = rand() % NUM_ITEM_TYPES;
    
    if (randType == ITEM_TYPE_POTION) {
        return new Potion();
    }
    else if (randType == ITEM_TYPE_WEAPON) {
        return getRandomWeapon();
    }
    else if (randType == ITEM_TYPE_ARMOR) {
        return getRandomArmor();
    }
    else if (randType == ITEM_TYPE_KEY) {
        return getRandomKey();
    }
    else if (randType == ITEM_TYPE_BOMB) {
        return new Bomb();
    }
    else if (randType == ITEM_TYPE_MAGICSCROLL) {
        return new Magicscroll();
    }
    else if (randType == ITEM_TYPE_TORCH) {
        return new Torch();
    }
    else {
        return new TimeBomb();
    }
}

Item *createItemByShape(char shape) {
    if (shape == DEFAULT_POTION_SHAPE) {
        return new Potion();
    }
    else if (isWeapon(shape)) {
        return getRandomWeapon(shape);
    }
    else if (isArmor(shape)) {
        return getRandomArmor(shape);
    }
    else if (shape == DEFAULT_KEY_SHAPE) {
        return new Key();
    }
    else if (shape == DEFAULT_BOMB_SHAPE) {
        return new Bomb();
    }
    else if (shape == DEFAULT_MAGICSCROLL_SHAPE) {
        return new Magicscroll();
    }
    else if (shape == DEFAULT_TORCH_SHAPE) {
        return new Torch();
    }
    else if (shape == DEFAULT_TIMEBOMB_SHAPE) {
        return new TimeBomb();
    }
    
    return NULL;
}

Item *createItemByID(string itemID) {
    if (itemID == ITEM_ID_POTION) {
        return new Potion();
    }
    else if (itemID == ITEM_ID_WEAPON) {
        return new Weapon();
    }
    else if (itemID == ITEM_ID_ARMOR) {
        return new Armor();
    }
    else if (itemID == ITEM_ID_KEY) {
        return new Key();
    }
    else if (itemID == ITEM_ID_BOMB) {
        return new Bomb();
    }
    else if (itemID == ITEM_ID_MAGICSCROLL) {
        return new Magicscroll();
    }
    else if (itemID == ITEM_ID_TORCH) {
        return new Torch();
    }
    else if (itemID == ITEM_ID_TIMEBOMB) {
        return new TimeBomb();
    }
    
    return NULL;
}

void Item::save(ostream &out) {
    out << "#-------------------- class Item" << endl;
    
    out << "# shape" << endl;
    out << shape << endl;
    
    out << "# name" << endl;
    out << name << endl;
    
    out << "# price" << endl;
    out << price << endl;
    
    out << "# level" << endl;
    out << level << endl;
    
    out << "# disposed" << endl;
    out << disposed << endl;
    
    out << "# moved" << endl;
    out << moved << endl;
    
    out << "# processed" << endl;
    out << processed << endl;
    
    out << "# disposable" << endl;
    out << disposable << endl;

}

void Item::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Item" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# shape" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << shape << endl;
    in >> shape;
    in.get(); // skip enter code.
    
    //out << "# name" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << name << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    name = buf;
//    in.get(); // skip enter code. <- getline() reads enter code.
    
    //out << "# price" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << price << endl;
    in >> price;
    in.get(); // skip enter code.
    
    //out << "# level" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << level << endl;
    in >> level;
    in.get(); // skip enter code.
    
    //out << "# disposed" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << disposed << endl;
    in >> disposed;
    in.get(); // skip enter code.
    
    //out << "# moved" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << moved << endl;
    in >> moved;
    in.get(); // skip enter code.
    
    //out << "# processed" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << processed << endl;
    in >> processed;
    in.get(); // skip enter code.
    
    //out << "# disposable" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << disposable << endl;
    in >> disposable;
    in.get(); // skip enter code.
    
    // * We don't save or load board.
}
//==============================================================================
// 2nd Generation
//==============================================================================

//------------------------------------------------------------------------------
// class ConsumableItem
//------------------------------------------------------------------------------

ConsumableItem::ConsumableItem() : Item() {
}

ConsumableItem::ConsumableItem(ConsumableItem &other) : Item(other) {
    //*this = other;
}

ConsumableItem::ConsumableItem(char shape, string name, int price, bool disposable, int level) : Item(shape, name, price, disposable, level) {
}

Item &ConsumableItem::operator=(Item &other) {
    Item::operator=(other);
    
    return *this;
}

void ConsumableItem::printFullSpec() {
    Item::printFullSpec();
}

bool ConsumableItem::isConsumable() {
    return true;
}

bool ConsumableItem::isKey() {
    return false;
}

void ConsumableItem::save(ostream &out) {
    Item::save(out);
    
    out << "#-------------------- class ConsumableItem" << endl;
}

void ConsumableItem::load(istream &in) {
    Item::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class ConsumableItem" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class EquipableItem
//------------------------------------------------------------------------------

EquipableItem::EquipableItem() : Item() {
}

EquipableItem::EquipableItem(EquipableItem &other) : Item(other) {
    *this = other;
}

EquipableItem::EquipableItem(char shape, string name, int price, bool disposable, int level) : Item(shape, name, price, disposable, level) {
}

Item &EquipableItem::operator=(Item &other) {
    Item::operator=(other);

    return *this;
}

void EquipableItem::printFullSpec() {
    Item::printFullSpec();
}

bool EquipableItem::isEquipable() {
    return true;
}

bool EquipableItem::isArmor() {
    return false;
}

bool EquipableItem::isWeapon() {
    return false;
}

bool EquipableItem::getRangeAttack() {
    return false;
}

void EquipableItem::save(ostream &out) {
    Item::save(out);
    
    out << "#-------------------- class EquippableItem" << endl;
}

void EquipableItem::load(istream &in) {
    Item::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class EquippableItem" << endl;
    in.getline(buf, 80); // skip comment
}

//------------------------------------------------------------------------------
// class ReusableItem
//------------------------------------------------------------------------------

ReusableItem::ReusableItem() : Item() {
}

ReusableItem::ReusableItem(ReusableItem &other) : Item(other) {
    *this = other;
}

ReusableItem::ReusableItem(char shape, string name, int price, bool disposable, int level) : Item(shape, name, price, disposable, level) {
}

Item &ReusableItem::operator=(Item &other) {
    Item::operator=(other);
    
    return *this;
}

void ReusableItem::printFullSpec() {
    Item::printFullSpec();
}

bool ReusableItem::isReusable() {
    return true;
}

bool ReusableItem::isTorch() {
    return false;
}

void ReusableItem::save(ostream &out) {
    Item::save(out);
    
    out << "#-------------------- class ReusableItem" << endl;
}

void ReusableItem::load(istream &in) {
    Item::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class ReusableItem" << endl;
    in.getline(buf, 80); // skip comment
}

//==============================================================================
// 3rd Generation
//==============================================================================

//------------------------------------------------------------------------------
// class Potion
//------------------------------------------------------------------------------

// Default Constructor
Potion::Potion() : ConsumableItem(DEFAULT_POTION_SHAPE, DEFAULT_POTION_NAME, DEFAULT_POTION_PRICE, false, DEFAULT_POTION_LEVEL) {
    
    int randNum = rand() % 10;
    if (randNum >= 0 && randNum <= 3) {
        hp = DEFAULT_POTION_HP_TO_INC;
        mp = 0;
        potionType = POTION_HP;
    }
    else if (randNum >= 4 && randNum <= 7) {
        mp = DEFAULT_POTION_MP_TO_INC;
        hp = 0;
        potionType = POTION_MP;
    }
    else { // if (randNum >= 8) {
        mp = DEFAULT_POTION_MP_TO_INC;
        hp = DEFAULT_POTION_HP_TO_INC;
        potionType = POTION_SPECIAL;
    }
    
    disposed = false;
}

Potion::Potion(Potion &other) : ConsumableItem(other) {
    *this = other;
}

Potion::Potion(char shape, string name, int price, int level, int hp, int mp, int potionType) : ConsumableItem(shape, name, price, false, level) {
    this->hp = hp;
    this->mp = mp;
    disposed = false;
    this->potionType = potionType;
}

Potion::~Potion() {}

Item &Potion::operator=(Item &other) {
    ConsumableItem::operator=(other);
    
    hp = ((Potion &)other).hp;
    mp = ((Potion &)other).mp;
    potionType = ((Potion &)other).potionType;

    return *this;
}

void Potion::printFullSpec() {
    ConsumableItem::printFullSpec();
    if (potionType == POTION_HP) {
        cout << " HP(" << hp << ")";
    }
    else if (potionType == POTION_MP) {
        cout << " MP(" << mp << ")";
    }
    else if (potionType == POTION_SPECIAL) {
        cout << " HP(" << hp << ") MP(" << mp << ")";
    }
}

void Potion::print(ostream &out) {
#ifdef ANSI_COLOR_OUTPUT
    if (potionType == POTION_HP) {
        out << BOLDRED;
    }
    else if (potionType == POTION_MP) {
        out << BOLDBLUE;
    }
    else if (potionType == POTION_SPECIAL) {
        out << BOLDMAGENTA;
    }
    
#endif
    out << shape;
#ifdef ANSI_COLOR_OUTPUT
    out << RESET;
#endif
}

bool Potion::use(Unit *unit) {
    if (unit != NULL && unit->isHero()) {
        if (potionType == POTION_HP) {
            unit->incHp(hp);
        }
        else if (potionType == POTION_MP) {
            unit->incMp(mp);
        }
        else if (potionType == POTION_SPECIAL) {
            unit->incHp(hp);
            unit->incMp(mp);
        }
        disposed = true;
        return true;
    }
    return false;
}

Item *Potion::clone() {
    return new Potion(*this);
}

string Potion::getID() {
    return string(ITEM_ID_POTION);
}

void Potion::save(ostream &out) {
    ConsumableItem::save(out);
    
    out << "#-------------------- class Potion" << endl;

    out << "# hp" << endl;
    out << hp << endl;
    
    out << "# mp" << endl;
    out << mp << endl;
    
    out << "# potionType" << endl;
    out << potionType << endl;
    
}

void Potion::load(istream &in) {
    ConsumableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Potion" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# hp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << hp << endl;
    in >> hp;
    in.get(); // skip enter code.
    
    //out << "# mp" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << mp << endl;
    in >> mp;
    in.get(); // skip enter code.
    
    //out << "# potionType" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << potionType << endl;
    in >> potionType;
    in.get(); // skip enter code.
}

//------------------------------------------------------------------------------
// class Key
//------------------------------------------------------------------------------

// Default Constructor
Key::Key() : ConsumableItem(DEFAULT_KEY_SHAPE, DEFAULT_KEY_NAME, DEFAULT_KEY_PRICE, false, DEFAULT_KEY_LEVEL) {
    keyType = DEFAULT_KEY_TYPE;
}

Key::Key(Key &other) : ConsumableItem(other) {
    *this = other;
}

Key::Key(char shape, string name, int price, int level, int keyType) : ConsumableItem(shape, name, price, false, level) {
    this->keyType = keyType;
}

Key::~Key() {}

Item &Key::operator=(Item &other) {
    ConsumableItem::operator=(other);
    
    keyType = ((Key &)other).keyType;

    return *this;
}

void Key::printFullSpec() {
    ConsumableItem::printFullSpec();
    
    cout << " KeyType(" << keyType << ")";
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

void Key::print(ostream &out) {
#ifdef ANSI_COLOR_OUTPUT
    if (keyType == KEY_RUSTY) {
        out << BOLDYELLOW;
    }
    else if (keyType == KEY_BRONZE) {
        out << BOLDRED;
    }
    else if (keyType == KEY_SILVER) {
        out << BOLDBLUE;
    }
    else { // if (lockLevel == CHEST_GOLD) {
        out << BOLDMAGENTA;
    }
#endif
    out << shape;
#ifdef ANSI_COLOR_OUTPUT
    out << RESET;
#endif
}

bool Key::isKey() {
    return true;
}

int Key::getKeyType() {
    return keyType;
}

bool Key::use(Unit *unit) {
    return false;
}

Item *Key::clone() {
    return new Key(*this);
}

string Key::getID() {
    return string(ITEM_ID_KEY);
}

void Key::save(ostream &out) {
    ConsumableItem::save(out);
    
    out << "#-------------------- class Key" << endl;
    
    out << "# keyType" << endl;
    out << keyType << endl;
}

void Key::load(istream &in) {
    ConsumableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Key" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# keyType" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << keyType << endl;
    in >> keyType;
    in.get(); // skip enter code.
}

Key *getRandomKey() {
    int rangeRusty = (5 - KEY_RUSTY) * (5 - KEY_RUSTY);
    int rangeBronze = (5 - KEY_BRONZE) * (5 - KEY_BRONZE);
    int rangeSilver = (5 - KEY_SILVER) * (5 - KEY_SILVER);
    int rangeGold = (5 - KEY_GOLD) * (5 - KEY_GOLD);
    
    int total = rangeRusty + rangeBronze + rangeSilver + rangeGold;

    int randVal = rand() % total;
    
    int keyType = -1;
    
    if (randVal >= 0 && randVal < rangeRusty) {
        keyType = KEY_RUSTY;
    }
    else if (randVal >= rangeRusty && randVal < (rangeRusty + rangeBronze)) {
        keyType = KEY_BRONZE;
    }
    else if (randVal >= (rangeRusty + rangeBronze) && randVal < (rangeRusty + rangeBronze + rangeSilver)) {
        keyType = KEY_SILVER;
    }
    else {
        keyType = KEY_GOLD;
    }

    if (keyType == KEY_RUSTY) {
        return new Key(DEFAULT_KEY_SHAPE, KEY_RUSTY_NAME, KEY_RUSTY_PRICE, DEFAULT_KEY_LEVEL, KEY_RUSTY);
        //return new Key((char)('9'-KEY_RUSTY), KEY_RUSTY_NAME, KEY_RUSTY_PRICE, DEFAULT_KEY_LEVEL, KEY_RUSTY);
    }
    else if (keyType == KEY_BRONZE) {
        return new Key(DEFAULT_KEY_SHAPE, KEY_BRONZE_NAME, KEY_BRONZE_PRICE, DEFAULT_KEY_LEVEL, KEY_BRONZE);
        //return new Key((char)('9'-KEY_BRONZE), KEY_BRONZE_NAME, KEY_BRONZE_PRICE, DEFAULT_KEY_LEVEL, KEY_BRONZE);
    }
    else if (keyType == KEY_SILVER) {
        return new Key(DEFAULT_KEY_SHAPE, KEY_SILVER_NAME, KEY_SILVER_PRICE, DEFAULT_KEY_LEVEL, KEY_SILVER);
        //return new Key((char)('9'-KEY_SILVER), KEY_SILVER_NAME, KEY_SILVER_PRICE, DEFAULT_KEY_LEVEL, KEY_SILVER);
    }
    else { // if (keyType == KEY_GOLD) {
        return new Key(DEFAULT_KEY_SHAPE, KEY_GOLD_NAME, KEY_GOLD_PRICE, DEFAULT_KEY_LEVEL, KEY_GOLD);
        //return new Key((char)('9'-KEY_GOLD), KEY_GOLD_NAME, KEY_GOLD_PRICE, DEFAULT_KEY_LEVEL, KEY_GOLD);
    }
}

//------------------------------------------------------------------------------
// class Arrow
//------------------------------------------------------------------------------

/*
 #define ARROW_SHAPE_NORTH '^'
 #define ARROW_SHAPE_EAST '>'
 #define ARROW_SHAPE_SOUTH 'v'
 #define ARROW_SHAPE_WEST '<'
 
 #define DEFAULT_ARROW_SHAPE ARROW_SHAPE_NORTH
 #define DEFAULT_ARROW_NAME "Arrow"
 #define DEFAULT_ARROW_PRICE 5
 #define DEFAULT_ARROW_LEVEL 1
 #define DEFAULT_ARROW_ATK 10
 #define DEFAULT_ARROW_DIR ARROW_SHAPE_NORTH
 #define DEFAULT_ARROW_MAX_RANGE 10
 */

Arrow::Arrow()
: ConsumableItem(DEFAULT_ARROW_SHAPE, DEFAULT_ARROW_NAME,
                 DEFAULT_ARROW_PRICE, false, DEFAULT_ARROW_LEVEL) {
    atk = DEFAULT_ARROW_ATK;
    dir = DEFAULT_ARROW_DIR;
    maxRange = DEFAULT_ARROW_MAX_RANGE;
    currentFlyingDist = 0;
    
    hero = NULL;
}

Arrow::Arrow(Arrow &other) : ConsumableItem(other) {
    *this = other;
}

Arrow::Arrow(int atk, int dir, Unit *hero)
: ConsumableItem(DEFAULT_ARROW_SHAPE, DEFAULT_ARROW_NAME,
                 DEFAULT_ARROW_PRICE, false, DEFAULT_ARROW_LEVEL) {
    this->atk = atk;
    this->dir = dir;
    maxRange = DEFAULT_ARROW_MAX_RANGE;
    currentFlyingDist = 0;
    
    this->hero = hero;
}

Arrow::Arrow(char shape, string name, int price, int level, int atk, int dir, int maxRange, Unit *hero)
: ConsumableItem(shape, name, price, false, level) {
    this->atk = atk;
    this->dir = dir;
    this->maxRange = maxRange;
    currentFlyingDist = 0;
    
    this->hero = hero;
}

Arrow::~Arrow() {
}

Item &Arrow::operator=(Item &other) {
    ConsumableItem::operator=(other);
   
    atk = ((Arrow &)other).atk;
    dir = ((Arrow &)other).dir;
    maxRange = ((Arrow &)other).maxRange;
    currentFlyingDist = ((Arrow &)other).currentFlyingDist;
    hero = ((Arrow &)other).hero;

    return *this;
}

void Arrow::print(ostream &out) {
    if (dir == MOVE_DIR_NORTH) {
        out << ARROW_SHAPE_NORTH;
    }
    else if (dir == MOVE_DIR_EAST) {
        out << ARROW_SHAPE_EAST;
    }
    else if (dir == MOVE_DIR_SOUTH) {
        out << ARROW_SHAPE_SOUTH;
    }
    else {
        out << ARROW_SHAPE_WEST;
    }
}

void Arrow::printFullSpec() {
    ConsumableItem::printFullSpec();
    
    cout << " Atk(" << atk << ") MaxRange(" << maxRange << ")";
}

bool Arrow::use(Unit *unit) {
    if (unit == NULL) {
        return false;
    }

    if (atk - unit->getDef()/2 < 0) {
        unit->decHp(0);
    }
    else {
        unit->decHp(atk - unit->getDef()/2);
    }
    
    hero->setUnitEngaged(unit);
    unit->setUnitEngaged(hero);
    
    if (unit->getHp() == 0) {
        if (unit->isHero()) {
            hero->incGold(unit->getGold()/10);
            hero->incExp(unit->getLevel()*50);
            unit->decExp(unit->getLevel()*100);
            int randNum = rand() % 4;
            cout << randNum;
            if (randNum == 1) {
                hero->addPotion(1);
            }
        }
        else if (unit->isMon()) {
            hero->incGold(unit->getGold()/10);
            hero->incExp(unit->getExp());
            int randNum = rand() % 4;
            cout << randNum;
            if (randNum == 1) {
                hero->addPotion(1);
            }
        }
        
    }
    
    //cout << "Monster hit hero! " << enemy->getAtk() << " point(s)!! Hero's HP is " << hero->getHp() << "!!" << endl;
    
    /*
     //cout << "Monster died!! Congratulation!!" << endl;
     hero->incGold(enemy->getGold());
     hero->incExp(enemy->getExp());
     
     int randNum = rand() % 4;
     cout << randNum;
     if (randNum == 1) {
     hero->addPotion(1);
     
     */
    
    disposed = true;
    return true;
}

bool Arrow::move(int row, int col) {
    processed = true;
    
    if (dir == MOVE_DIR_NORTH) {
        // we are sure about no unit at the current position.
        if (sim->board->validate(row-1, col) &&
            (sim->board->getProp(row-1, col) == NULL ||
             sim->board->getProp(row-1, col)->canGoThroughByThrowableItem())) {
                sim->board->setThrowingItem(row-1, col, this);
            }
        else {
            disposed = true;
            delete this;
        }
        // deleting the throwing item will be processed in
        // Tile::processThrowingItems()
        return true;
    }
    else if (dir == MOVE_DIR_EAST) {
        // we are sure about no unit at the current position.
        if (sim->board->validate(row, col+1) &&
            (sim->board->getProp(row, col+1) == NULL ||
             sim->board->getProp(row, col+1)->canGoThroughByThrowableItem())) {
                sim->board->setThrowingItem(row, col+1, this);
            }
        else {
            disposed = true;
            delete this;
        }
        // deleting the throwing item will be processed in
        // Tile::processThrowingItems()
        return true;
    }
    else if (dir == MOVE_DIR_SOUTH) {
        // we are sure about no unit at the current position.
        if (sim->board->validate(row+1, col) &&
            (sim->board->getProp(row+1, col) == NULL ||
             sim->board->getProp(row+1, col)->canGoThroughByThrowableItem())) {
                sim->board->setThrowingItem(row+1, col, this);
            }
        else {
            disposed = true;
            delete this;
        }
        // deleting the throwing item will be processed in
        // Tile::processThrowingItems()
        return true;
    }
    else if (dir == MOVE_DIR_WEST) {
        // we are sure about no unit at the current position.
        if (sim->board->validate(row, col-1) &&
            (sim->board->getProp(row, col-1) == NULL ||
             sim->board->getProp(row, col-1)->canGoThroughByThrowableItem())) {
                sim->board->setThrowingItem(row, col-1, this);
            }
        else {
            disposed = true;
            delete this;
        }
        // deleting the throwing item will be processed in
        // Tile::processThrowingItems()
        return true;
    }
    return false;
}

Item *Arrow::clone() {
    return new Arrow(*this);
}

string Arrow::getID() {
    return string(ITEM_ID_ARROW);
}

void Arrow::save(ostream &out) {
    ConsumableItem::save(out);
    
    out << "#-------------------- class Arrow" << endl;
    
    out << "# atk" << endl;
    out << atk << endl;
    
    out << "# dir" << endl;
    out << dir << endl;
    
    out << "# maxRange" << endl;
    out << maxRange << endl;
    
    out << "# currentFlyingDist" << endl;
    out << currentFlyingDist << endl;
}

void Arrow::load(istream &in) {
    ConsumableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Arrow" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# atk" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << atk << endl;
    in >> atk;
    in.get(); // skip enter code.
    
    //out << "# dir" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << dir << endl;
    in >> dir;
    in.get(); // skip enter code.
    
    //out << "# maxRange" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxRange << endl;
    in >> maxRange;
    in.get(); // skip enter code.
    
    //out << "# currentFlyingDist" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << currentFlyingDist << endl;
    in >> currentFlyingDist;
    in.get(); // skip enter code.
    
    hero = NULL;
}

//------------------------------------------------------------------------------
// class Armor
//------------------------------------------------------------------------------

Armor::Armor() : EquipableItem(DEFAULT_ARMOR_SHAPE, DEFAULT_ARMOR_NAME, DEFAULT_ARMOR_PRICE, false, DEFAULT_ARMOR_LEVEL) {
    def = DEFAULT_ARMOR_DEFENCE;
    durability = DEFAULT_ARMOR_DURABILITY;
    bodyPartID = -1;
    armorType = DEFAULT_ARMOR_TYPE;
}

Armor::Armor(Armor &other) : EquipableItem(other) {
    *this = other;
}

Armor::Armor(char shape, string name, int price, int level, int def, int durability, int bodyPartID, int armorType) : EquipableItem(shape, name, price, false, level) {
    this->def = def;
    this->durability = durability;
    this->bodyPartID = bodyPartID;
    this->armorType = armorType;
}

Armor::~Armor() {}

Item &Armor::operator=(Item &other) {
    EquipableItem::operator=(other);
    
    def = ((Armor &)other).def;
    durability = ((Armor &)other).durability;
    bodyPartID = ((Armor &)other).bodyPartID;
    armorType = ((Armor &)other).armorType;

    return *this;
}

void Armor::printFullSpec() {
    EquipableItem::printFullSpec();
    
    cout << " Def(" << def << ") Durability(" << durability << ")";
}

void Armor::print(ostream &out) {
#ifdef ANSI_COLOR_OUTPUT
    if (armorType == WEAPON_WOOD) {
        out << BOLDYELLOW;
    }
#endif
    out << shape;
#ifdef ANSI_COLOR_OUTPUT
    out << RESET;
#endif
}

bool Armor::isArmor() {
    return true;
}

int Armor::getDef() {
    return def;
}

int Armor::getBodyPartID() {
    return bodyPartID;
}

bool Armor::use(Unit *unit) {
    if (unit->equip(this)) {
        moved = true;
        return true;
    }
    return false;
}

Item *Armor::clone() {
    return new Armor(*this);
}

string Armor::getID() {
    return string(ITEM_ID_ARMOR);
}

void Armor::save(ostream &out) {
    EquipableItem::save(out);
    
    out << "#-------------------- class Armor" << endl;
    
    out << "# def" << endl;
    out << def << endl;
    
    out << "# durability" << endl;
    out << durability << endl;
    
    out << "# bodyPartID" << endl;
    out << bodyPartID << endl;
    
    out << "# armorType" << endl;
    out << armorType << endl;
}

void Armor::load(istream &in) {
    EquipableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Armor" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# def" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << def << endl;
    in >> def;
    in.get(); // skip enter code.
    
    //out << "# durability" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << durability << endl;
    in >> durability;
    in.get(); // skip enter code.
    
    //out << "# bodyPartID" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << bodyPartID << endl;
    in >> bodyPartID;
    in.get(); // skip enter code.
    
    //out << "# armorType" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << armorType << endl;
    in >> armorType;
    in.get(); // skip enter code.
}

/*
 #define BODY_PART_ID_HEAD 1
 #define BODY_PART_ID_CHEST 2
 #define BODY_PART_ID_BACK 3
 #define BODY_PART_ID_HANDS 4
 #define BODY_PART_ID_LEGS 5
 #define BODY_PART_ID_FEET 6
 #define BODY_PART_ID_LEFT_HAND 7
 #define BODY_PART_ID_RIGHT_HAND 8
 
 #define ARMOR_SHAPE_HEAD 'A'
 #define ARMOR_SHAPE_CHEST 'W'
 #define ARMOR_SHAPE_BACK 'Q'
 #define ARMOR_SHAPE_HANDS 'M'
 #define ARMOR_SHAPE_LEGS 'L'
 #define ARMOR_SHAPE_FEET 'F'
 
 #define NUM_RANDOM_ARMORS 6
 */
Armor *getRandomArmor() {
    return getRandomArmor(ARMOR_SHAPE_NONE);
}

Armor *getRandomArmor(char shape) {
    char shapes[NUM_RANDOM_ARMORS] =        {ARMOR_SHAPE_HEAD,    ARMOR_SHAPE_HANDS,    ARMOR_SHAPE_CHEST,    ARMOR_SHAPE_BACK,    ARMOR_SHAPE_LEGS,    ARMOR_SHAPE_FEET};
    char name[NUM_RANDOM_ARMORS][80] =     {"Wooden Helmet",     "Wooden Gloves",      "Wooden Chestpiece",  "Woopen Cape",       "Wooden Pants",      "Wooden Boots"};
    int price[NUM_RANDOM_ARMORS] =         {500,                 500,                  1000,                 500,                 1000,                500};
    int level[NUM_RANDOM_ARMORS] =         {1,                   1,                    1,                    1,                   1,                   1};
    int def[NUM_RANDOM_ARMORS] =           {5,                   5,                    10,                   5,                   10,                  5};
    int durability[NUM_RANDOM_ARMORS] =    {200,                 1000,                 2000,                    200,                 1500,                1000};
    int bodyPartID[NUM_RANDOM_ARMORS] =    {BODY_PART_ID_HEAD,   BODY_PART_ID_HANDS,   BODY_PART_ID_CHEST,   BODY_PART_ID_BACK,   BODY_PART_ID_LEGS,   BODY_PART_ID_FEET};
    int armorType[NUM_RANDOM_ARMORS] =     {ARMOR_WOOD,          ARMOR_WOOD,           ARMOR_WOOD,           ARMOR_WOOD,          ARMOR_WOOD,          ARMOR_WOOD};
    
    int randArmorIndex = rand() % NUM_RANDOM_ARMORS;
    
    if (shape != ARMOR_SHAPE_NONE) {
        while (true) {
            if (shapes[randArmorIndex] == shape) {
                break;
            }
            
            randArmorIndex = rand() % NUM_RANDOM_ARMORS;
        }
    }
    
    Armor *randomArmor = new Armor(shapes[randArmorIndex],
                                   name[randArmorIndex],
                                   price[randArmorIndex],
                                   level[randArmorIndex],
                                   def[randArmorIndex],
                                   durability[randArmorIndex],
                                   bodyPartID[randArmorIndex],
                                   armorType[randArmorIndex]);
    return randomArmor;
}


bool isArmor(char shape) {
    return
        shape == ARMOR_SHAPE_HEAD ||
        shape == ARMOR_SHAPE_CHEST ||
        shape == ARMOR_SHAPE_BACK ||
        shape == ARMOR_SHAPE_HANDS ||
        shape == ARMOR_SHAPE_LEGS ||
        shape == ARMOR_SHAPE_FEET;
}

//------------------------------------------------------------------------------
// class Weapon
//------------------------------------------------------------------------------

Weapon::Weapon() : EquipableItem(DEFAULT_WEAPON_SHAPE, DEFAULT_WEAPON_NAME, DEFAULT_WEAPON_PRICE, false, DEFAULT_WEAPON_LEVEL) {
    atk = DEFAULT_WEAPON_ATK;
    durability = DEFAULT_WEAPON_DURABILITY;
    numHands = DEFAULT_WEAPON_NUM_HANDS;
    weaponType = DEFAULT_WEAPON_TYPE;
    job = DEFAULT_HERO_JOB;
}

Weapon::Weapon(Weapon &other) : EquipableItem(other) {
    *this = other;
}

Weapon::Weapon(char shape, string name, int price, int level, int atk, int durability, int numHands, bool rangeAttack, int weaponType, int job) : EquipableItem(shape, name, price, false, level) {
    this->atk = atk;
    this->durability = durability;
    this->numHands = numHands;
    this->rangeAttack = rangeAttack;
    this->weaponType = weaponType;
    this->job = job;
}

Weapon::~Weapon() {}

Item &Weapon::operator=(Item &other) {
    EquipableItem::operator=(other);
  
    atk = ((Weapon &)other).atk;
    durability = ((Weapon &)other).durability;
    numHands = ((Weapon &)other).numHands;
    rangeAttack = ((Weapon &)other).rangeAttack;
    weaponType = ((Weapon &)other).weaponType;
    job = ((Weapon &)other).job;

    return *this;
}

void Weapon::printPartSpec() {
    EquipableItem::printPartSpec();
    
    cout << " Atk(" << setw(4) << atk << ") NumHands(" << numHands << ")";
}

void Weapon::printFullSpec() {
    EquipableItem::printFullSpec();
    
    cout << " Atk(" << setw(4) << atk << ") NumHands(" << numHands << ")";
}

void Weapon::print(ostream &out) {
#ifdef ANSI_COLOR_OUTPUT
    if (weaponType == WEAPON_WOOD) {
        out << BOLDYELLOW;
    }
    else if (weaponType == WEAPON_STONE) {
        out << BOLDRED;
    }
#endif
    out << shape;
#ifdef ANSI_COLOR_OUTPUT
    out << RESET;
#endif
}

int Weapon::getAtk() {
    return atk;
}

bool Weapon::getRangeAttack() {
    return rangeAttack;
}

int Weapon::getNumHands() {
    return numHands;
}

int Weapon::getWeaponType() {
    return weaponType;
}

int Weapon::getJob() {
    return job;
}

bool Weapon::use(Unit *unit) {
    if (unit->equip(this)) {
        moved = true;
        return true;
    }
    return false;
}

bool Weapon::isWeapon() {
    return true;
}

Item *Weapon::clone() {
    return new Weapon(*this);
}

string Weapon::getID() {
    return string(ITEM_ID_WEAPON);
}
    
void Weapon::save(ostream &out) {
    EquipableItem::save(out);
    
    out << "#-------------------- class Weapon" << endl;
    
    out << "# atk" << endl;
    out << atk << endl;
    
    out << "# durability" << endl;
    out << durability << endl;
    
    out << "# numHands" << endl;
    out << numHands << endl;
    
    out << "# rangeAttack" << endl;
    out << rangeAttack << endl;
    
    out << "# weaponType" << endl;
    out << weaponType << endl;
    
    out << "# job" << endl;
    out << job << endl;
}

void Weapon::load(istream &in) {
    EquipableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Weapon" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# atk" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << atk << endl;
    in >> atk;
    in.get(); // skip enter code.
    
    //out << "# durability" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << durability << endl;
    in >> durability;
    in.get(); // skip enter code.
    
    //out << "# numHands" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numHands << endl;
    in >> numHands;
    in.get(); // skip enter code.
    
    //out << "# rangeAttack" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << rangeAttack << endl;
    in >> rangeAttack;
    in.get(); // skip enter code.
    
    //out << "# weaponType" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << weaponType << endl;
    in >> weaponType;
    in.get(); // skip enter code.
    
    //out << "# job" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << job << endl;
    in >> job;
    in.get(); // skip enter code.
}

/*
 #define WEAPON_ONE_HAND_SHAPE '!'
 #define WEAPON_TWO_HAND_SHAPE '?'
 
 #define DEFAULT_WEAPON_NUM_HANDS 1
 
 #define NUM_RANDOM_WEAPONS 4
 */
Weapon *getRandomWeapon() {
    return getRandomWeapon(WEAPON_SHAPE_NONE);
}

Weapon *getRandomWeapon(char shape) {
    char shapes[NUM_RANDOM_WEAPONS] =        {WEAPON_ONE_HAND_SHAPE,  WEAPON_TWO_HAND_SHAPE,  WEAPON_TWO_HAND_SHAPE,  WEAPON_BOW_SHAPE,        WEAPON_BOW_SHAPE,   WEAPON_ONE_HAND_SHAPE,   WEAPON_TWO_HAND_SHAPE,   WEAPON_TWO_HAND_SHAPE,   WEAPON_BOW_SHAPE,    WEAPON_BOW_SHAPE};
    char name[NUM_RANDOM_WEAPONS][80] =     {"Wooden Sword",         "Wooden Axe",           "Wooden Hammer",        "Wooden Crossbow",       "Wooden Bow",       "Stone Sword",           "Stone Axe",             "Stone Hammer",          "Stone Crossbow",    "Stone Bow"};
    int price[NUM_RANDOM_WEAPONS] =         {1000,                   2000,                   2000,                   2000,                    2000,               4000,                    4000,                    4000,                    4000,                4000};
    int level[NUM_RANDOM_WEAPONS] =         {1,                      1,                      1,                      1,                       1,                  10,                      10,                      10,                      10,                  10};
    int atk[NUM_RANDOM_WEAPONS] =           {10,                     20,                     20,                     20,                      20,                 25,                      50,                      50,                      50,                  50};
    int durability[NUM_RANDOM_WEAPONS] =    {500,                    2000,                   2500,                   1000,                    1000,               2000,                    4000,                    4000,                    3000,                3000};
    int numHands[NUM_RANDOM_WEAPONS] =      {1,                      2,                      2,                      2,                       2,                  1,                       2,                       2,                       2,                   2};
    bool rangeAttack[NUM_RANDOM_WEAPONS] =  {false,                  false,                  false,                  true,                    true,               false,                   false,                   false,                   true,                true};
    int weaponType[NUM_RANDOM_WEAPONS] =    {WEAPON_WOOD,            WEAPON_WOOD,            WEAPON_WOOD,            WEAPON_WOOD,             WEAPON_WOOD,        WEAPON_STONE,            WEAPON_STONE,            WEAPON_STONE,            WEAPON_STONE,        WEAPON_STONE};
    int job[NUM_RANDOM_WEAPONS] =           {HERO_JOB_KNIGHT,        HERO_JOB_PALADIN,     HERO_JOB_WARRIOR,       HERO_JOB_HUNTER,         HERO_JOB_ARCHER,    HERO_JOB_KNIGHT,           HERO_JOB_PALADIN,        HERO_JOB_WARRIOR,        HERO_JOB_HUNTER,     HERO_JOB_ARCHER};
    
    int randWeaponsIndex = rand() % NUM_RANDOM_WEAPONS;
    
    if (shape != WEAPON_SHAPE_NONE) {
        while (true) {
            if (shapes[randWeaponsIndex] == shape) {
                break;
            }
            
            randWeaponsIndex = rand() % NUM_RANDOM_WEAPONS;
        }
    }
    
    Weapon *randomWeapon = new Weapon(shapes[randWeaponsIndex],
                                      name[randWeaponsIndex],
                                      price[randWeaponsIndex],
                                      level[randWeaponsIndex],
                                      atk[randWeaponsIndex],
                                      durability[randWeaponsIndex],
                                      numHands[randWeaponsIndex],
                                      rangeAttack[randWeaponsIndex],
                                      weaponType[randWeaponsIndex],
                                      job[randWeaponsIndex]
                                      );
    
    return randomWeapon;
}

bool isWeapon(char shape) {
    return
        shape == WEAPON_ONE_HAND_SHAPE ||
        shape == WEAPON_TWO_HAND_SHAPE ||
        shape == WEAPON_BOW_SHAPE;
}

//------------------------------------------------------------------------------
// class Bomb
//------------------------------------------------------------------------------

Bomb::Bomb() : ConsumableItem(DEFAULT_BOMB_SHAPE, DEFAULT_BOMB_NAME,
                              DEFAULT_BOMB_PRICE, DEFAULT_BOMB_DISPOSABLE, 1) {
    range = DEFAULT_BOMB_RANGE;
    atk = DEFAULT_BOMB_ATK;
}

Bomb::Bomb(Bomb &other) : ConsumableItem(other) {
    *this = other;
}

Bomb::Bomb(char shape, string name, int price, bool disposable,
           int range, int atk)
: ConsumableItem(shape, name, price, DEFAULT_BOMB_DISPOSABLE, 1) {
    this->range = range;
    this->atk = atk;
}

Item &Bomb::operator=(Item &other) {
    ConsumableItem::operator=(other);
    
    range = ((Bomb &)other).range;
    atk = ((Bomb &)other).atk;

    return *this;
}

Bomb::~Bomb() {
}

void Bomb::printPartSpec() {
    ConsumableItem::printPartSpec();
    
    cout << " Atk(" << setw(4) << atk << ")";
}

void Bomb::printFullSpec() {
    ConsumableItem::printFullSpec();
    
    cout << " Atk(" << setw(4) << atk << ")";
}

void Bomb::print(ostream &out) {
#ifdef ANSI_COLOR_OUTPUT
    out << BLACK;
#endif
    out << shape;
#ifdef ANSI_COLOR_OUTPUT
    out << RESET;
#endif
}

bool Bomb::use(Unit *unit) {
    sim->board->startWave(NULL, this, NULL,
                      unit->getRow(), unit->getCol(),
                      range,
                      BOMB_WAVE_FRAME_INTERVAL,
                      BOMB_WAVE_SHAPE, 0);
    if (disposable) {
        moved = true;
    }
    return true;
}

void Bomb::effect(Unit *unit, Item *item, Prop *prop) {
    if (unit != NULL) {
        if (unit->isMon()) {
            unit->decHp(atk);
            if (unit->isDead()) {
            }
        }
    }
}

Item *Bomb::clone() {
    return new Bomb(*this);
}

string Bomb::getID() {
    return string(ITEM_ID_BOMB);
}

void Bomb::save(ostream &out) {
    ConsumableItem::save(out);
    
    out << "#-------------------- class Bomb" << endl;
    
    out << "# range" << endl;
    out << range << endl;
    
    out << "# atk" << endl;
    out << atk << endl;
}

void Bomb::load(istream &in) {
    ConsumableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Bomb" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# range" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << range << endl;
    in >> range;
    in.get(); // skip enter code.
    
    //out << "# atk" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << atk << endl;
    in >> atk;
    in.get(); // skip enter code.
}

//------------------------------------------------------------------------------
// class TimeBomb
//------------------------------------------------------------------------------

TimeBomb::TimeBomb() : ConsumableItem(DEFAULT_TIMEBOMB_SHAPE, DEFAULT_TIMEBOMB_NAME,
                              DEFAULT_TIMEBOMB_PRICE, DEFAULT_TIMEBOMB_DISPOSABLE, 1) {
    range = DEFAULT_TIMEBOMB_RANGE;
    atk = DEFAULT_TIMEBOMB_ATK;
}

TimeBomb::TimeBomb(TimeBomb &other) : ConsumableItem(other) {
    *this = other;
}

TimeBomb::TimeBomb(char shape, string name, int price, bool disposable,
           int range, int atk)
: ConsumableItem(shape, name, price, DEFAULT_TIMEBOMB_DISPOSABLE, 1) {
    this->range = range;
    this->atk = atk;
}

Item &TimeBomb::operator=(Item &other) {
    ConsumableItem::operator=(other);
    
    range = ((TimeBomb &)other).range;
    atk = ((TimeBomb &)other).atk;
    
    return *this;
}

TimeBomb::~TimeBomb() {
}

void TimeBomb::printPartSpec() {
    ConsumableItem::printPartSpec();
    
    cout << " Atk(" << setw(4) << atk << ")";
}

void TimeBomb::printFullSpec() {
    ConsumableItem::printFullSpec();
    
    cout << " Atk(" << setw(4) << atk << ")";
}

void TimeBomb::print(ostream &out) {
#ifdef ANSI_COLOR_OUTPUT
    out << BLACK;
#endif
    out << shape;
#ifdef ANSI_COLOR_OUTPUT
    out << RESET;
#endif
}

bool TimeBomb::use(Unit *unit) {

    if (sim->board->getItem(unit->getRow(), unit->getCol()) != NULL) {
        return false;
    }
    
    sim->board->setItem(unit->getRow(), unit->getCol(), this);
    pickUp = false; // hero가 이미 set된 time bomb을 다시 주워들지 못하게 한다.
    
    sim->eq->enqueue(new TimeBombEvent(sim->time+TIME_BOMB_EVENT_INTERVAL, this));
    
    if (disposable) {
        moved = true;
    }
    return true;
}

void TimeBomb::trigger() {
    sim->board->setItem(row, col, NULL); // 터질때 이미 board상에서는 지워져야 한다.
    
    sim->board->startWave(NULL, this, NULL,
                          row, col,
                          range,
                          TIMEBOMB_WAVE_FRAME_INTERVAL,
                          TIMEBOMB_WAVE_SHAPE, 0);
}

void TimeBomb::effect(Unit *unit, Item *item, Prop *prop) {
    if (unit != NULL) {
        if (unit->isMon()) {
            unit->decHp(atk);
            if (unit->isDead()) {
            }
        }
    }
}

Item *TimeBomb::clone() {
    return new TimeBomb(*this);
}

string TimeBomb::getID() {
    return string(ITEM_ID_TIMEBOMB);
}

void TimeBomb::save(ostream &out) {
    ConsumableItem::save(out);
    
    out << "#-------------------- class TimeBomb" << endl;
    
    out << "# range" << endl;
    out << range << endl;
    
    out << "# atk" << endl;
    out << atk << endl;
}

void TimeBomb::load(istream &in) {
    ConsumableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class TimeBomb" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# range" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << range << endl;
    in >> range;
    in.get(); // skip enter code.
    
    //out << "# atk" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << atk << endl;
    in >> atk;
    in.get(); // skip enter code.
}

//------------------------------------------------------------------------------
// class Magicscroll
//------------------------------------------------------------------------------

Magicscroll::Magicscroll() : ConsumableItem(DEFAULT_MAGICSCROLL_SHAPE, DEFAULT_MAGICSCROLL_NAME,
                                            DEFAULT_MAGICSCROLL_PRICE, false, 1) {
    magic = createRandMagic();
}

Magicscroll::Magicscroll(Magicscroll &other) : ConsumableItem(other) {
    //*this = other;
    magic = other.magic->clone();
}

Magicscroll::Magicscroll(char shape, string name, int price, bool disposable)
    : ConsumableItem(shape, name, price, false, 1) {
    magic = createRandMagic();
}

Item &Magicscroll::operator=(Item &other) {
    ConsumableItem::operator=(other);
    
    magic = ((Magicscroll &)other).magic->clone();
    
    return *this;
}

Magicscroll::~Magicscroll() {
    if (magic != NULL) {
        delete magic;
        magic = NULL;
    }
}

void Magicscroll::printPartSpec() {
    ConsumableItem::printPartSpec();
    
    
    if (magic->getJob() == HERO_JOB_KNIGHT) {
        cout << " Job(" << setw(8) << "Knight" << ")";
    }
    else if (magic->getJob() == HERO_JOB_PALADIN) {
        cout << " Job(" << setw(8) << "Paladin" << ")";
    }
    else if (magic->getJob() == HERO_JOB_WARRIOR) {
        cout << " Job(" << setw(8) << "Warrior" << ")";
    }
    else if (magic->getJob() == HERO_JOB_HUNTER) {
        cout << " Job(" << setw(8) << "Hunter" << ")";
    }
    else {
        cout << " Job(" << setw(18) << "Archer" << ")";
    }
}

void Magicscroll::printFullSpec() {
    ConsumableItem::printFullSpec();
    
    magic->printFullSpec();
}

void Magicscroll::print(ostream &out) {
#ifdef ANSI_COLOR_OUTPUT
    out << RED;
#endif
    out << shape;
#ifdef ANSI_COLOR_OUTPUT
    out << RESET;
#endif
}

bool Magicscroll::use(Unit *unit) {
    if (unit->getJob() != magic->getJob()) {
        return false;
    }
    Magic *clone = magic->clone();
    if (!unit->addMagicToMagicbook(clone)) {
        delete clone; // 이렇게 하지 않으면 memory leak.
        return false;
    }
    disposed = true;
    
    return true;
}

Item *Magicscroll::clone() {
    return new Magicscroll(*this);
}

string Magicscroll::getID() {
    return string(ITEM_ID_MAGICSCROLL);
}

void Magicscroll::save(ostream &out) {
    Item::save(out);
    
    out << "#-------------------- class Magicscroll" << endl;
    
    out << "# Magic ID" << endl;
    out << magic->getID() << endl;
    magic->save(out);
}

void Magicscroll::load(istream &in) {
    Item::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Magicscroll" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# Magic ID" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << magic->getID() << endl;
    string magicID = "";
    in >> magicID;
    in.get(); // skip enter code.
    
    magic = createMagicByID(magicID);
    magic->load(in);
}

// Default Constructor
Torch::Torch() : ReusableItem(DEFAULT_TORCH_SHAPE, DEFAULT_TORCH_NAME, DEFAULT_TORCH_PRICE, false, DEFAULT_LEVEL) {
    
    range = DEFAULT_TORCH_RANGE;
}

Torch::Torch(Torch &other) : ReusableItem(other) {
    *this = other;
}

Torch::Torch(char shape, string name, int price, int level, int range) : ReusableItem(shape, name, price, false, level) {
    this->range = range;
}

Torch::~Torch() {}

Item &Torch::operator=(Item &other) {
    ReusableItem::operator=(other);
    
    range = ((Torch &)other).range;
    
    return *this;
}

void Torch::printFullSpec() {
    ReusableItem::printFullSpec();

}

void Torch::print(ostream &out) {
#ifdef ANSI_COLOR_OUTPUT
    out << RED;
#endif
    out << shape;
#ifdef ANSI_COLOR_OUTPUT
    out << RESET;
#endif
}

bool Torch::isTorch() {
    return true;
}

int Torch::getRange() {
    return range;
}

bool Torch::use(Unit *unit) {
    return false;
}

Item *Torch::clone() {
    return new Torch(*this);
}

string Torch::getID() {
    return string(ITEM_ID_TORCH);
}

void Torch::save(ostream &out) {
    ReusableItem::save(out);
    
    out << "#-------------------- class Torch" << endl;
    
    out << "# range" << endl;
    out << range << endl;
}

void Torch::load(istream &in) {
    ReusableItem::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Torch" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# range" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << range << endl;
    in >> range;
    in.get(); // skip enter code.
}
