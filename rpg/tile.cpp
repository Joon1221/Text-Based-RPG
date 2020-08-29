#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "prop.h"
#include "tile.h"

//--------------------------------------------------
// Constructors
//--------------------------------------------------

// Default Constructor
Tile::Tile() {
    fx = FX_NONE;
    
    unit = NULL;
    
    numThrowingItems = 0;
    
    item = NULL;
    prop = NULL;
    
    resetAStar();
}

// Copy Constructor
Tile::Tile(Tile &other) {
    fx = other.fx;

    unit = other.unit;

    numThrowingItems = 0;

    item = other.item;
    prop = other.prop;
    
    resetAStar();
}

// General Constructor

//--------------------------------------------------
// Destructor
//--------------------------------------------------
Tile::~Tile() {
    if (unit != NULL) {
        delete unit;
    }
    for (int i = 0; i < numThrowingItems; i++) {
        if (throwingItem[i] != NULL) {
            delete throwingItem[i];
            numThrowingItems = 0;
        }
    }
    if (item != NULL) {
        delete item;
    }
    if (prop != NULL) {
        delete prop;
    }
    
    resetAStar();
}

//--------------------------------------------------
// General Member Functions
//--------------------------------------------------

void Tile::print() {
    if (fx != FX_NONE) {
        cout << fx;
    }
    else if (unit != NULL) {
        unit->print();
    }
    else if (numThrowingItems > 0) {
        throwingItem[0]->print();
    }
    else if (item != NULL) {
        item->print();
    }
    else if (prop != NULL) {
        prop->print();
    }
    else {
        cout << TILE_EMPTY;
    }
}

char Tile::getFx() {
    return fx;
}

void Tile::setFx(char fx) {
    this->fx = fx;
}

void Tile::clearFx() {
    fx = FX_NONE;
}

Unit *Tile::getUnit() {
    return unit;
}

void Tile::setUnit(Unit *unit) {
    this->unit = unit;
}

int Tile::getNumThrowingItems() {
    return numThrowingItems;
}

Item *Tile::getThrowingItem(int index) {
    if (index < 0 || index >= numThrowingItems) {
        cout << "fatal error: Tile::setThrowingItem():";
        cout << " invalid index = " << index << endl;
        exit(1);
    }
    
    return throwingItem[index];
}

void Tile::setThrowingItem(Item *item) {
    if (numThrowingItems >= MAX_NUM_THROWING_ITEMS) {
        cout << "fatal error: Tile::setThrowingItem():";
        cout << " numThrowingItems >= MAX_NUM_THROWING_ITEMS" << endl;
        exit(1);
    }
    
    throwingItem[numThrowingItems++] = item;
}

void Tile::processThrowingItems(int row, int col) {
    int itemsLeft = numThrowingItems;
    int i = 0;
    while (i < itemsLeft) {
        if (throwingItem[i]->hasBeenProcessed()) {
            throwingItem[i]->resetProcessed();
        } else {
            if (unit != NULL) {
                if (throwingItem[i]->use(unit)) {
                    if (throwingItem[i]->hasBeenDisposed()) {
                        delete throwingItem[i];
                        throwingItem[i] = NULL;
                    }
                }
            }
            else {
                throwingItem[i]->move(row, col);
                throwingItem[i] = NULL;
            }
            for (int j = i; j < itemsLeft-1; j++) {
                throwingItem[j] = throwingItem[j+1];
            }
            itemsLeft--;
        }
        
        i++;
    }
    numThrowingItems = itemsLeft;
}

Item *Tile::getItem() {
    return item;
}
 
void Tile::setItem(Item *item) {
    this->item = item;
}

Prop *Tile::getProp() {
    return prop;
}

void Tile::setProp(Prop *prop) {
    this->prop = prop;
}

bool Tile::isEmpty() {
    //return unit == NULL && item == NULL && prop == NULL;
    return unit == NULL;
}

bool Tile::isClimbable() {
    if (unit != NULL) {
        return false;
    }
    else if (prop != NULL) {
        return prop->isClimbable();
    }
    
    return true;
}

void Tile::save(ostream &out) {
    out << "#---------------------------------------- class Tile" << endl;
    
    out << "#-------------------- item" << endl;
    if (item == NULL) {
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Item ID" << endl;
        out << item->getID() << endl;
        item->save(out);
    }
    
    out << "#-------------------- prop" << endl;
    if (prop == NULL) {
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << TOMB_STONE_NON_EMPTY << endl;
        out << "# Prop ID" << endl;
        out << prop->getID() << endl;
        prop->save(out);
    }
}

void Tile::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#---------------------------------------- class Tile" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "#-------------------- item" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    string tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        item = NULL;
    }
    else {
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << item->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        item = createItemByID(itemID);
        item->load(in);
    }

    //out << "#-------------------- prop" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        prop = NULL;
    }
    else {
        //out << "# Prop ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << prop->getID() << endl;
        string propID = "";
        in >> propID;
        in.get(); // skip enter code.
        
        prop = createPropByID(propID);
        prop->load(in);
    }
}

void Tile::resetAStar() {
    f = INF;
    g = INF;
    h = 0.0;
    cameFromRow = -1;
    cameFromCol = -1;
}
