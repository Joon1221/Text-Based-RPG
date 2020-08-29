#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "inventory.h"

// Default Constructor
Inventory::Inventory() {
    initSlots(DEFAULT_INVENTORY_MAX_NUM_ITMES);
}

// General Constructor
Inventory::Inventory(int maxNumItems) {
    initSlots(maxNumItems);
}

void Inventory::initSlots(int maxNumItems) {
    this->maxNumItems = maxNumItems;
    numItems = 0;
    
    slots = new Item *[maxNumItems];
    
    for (int i = 0; i < maxNumItems; i++) {
        slots[i] = NULL;
    }
    
    curIndexForIter = 0;
}

Inventory::~Inventory() {
    deleteSlots();
}

void Inventory::deleteSlots() {
    if (slots != NULL) {
        for (int i = 0; i < maxNumItems; i++) {
            if (slots[i] != NULL) {
                delete slots[i];
                slots[i] = NULL;
            }
        }
        numItems = 0;
        
        delete [] slots;
        slots = NULL;
        
        curIndexForIter = 0;
    }
}

void Inventory::print() {
    cout << "[";
    for (int i = 0; i < maxNumItems; i++) {
        if (slots[i] != NULL) {
            slots[i]->print();
        }
        else { // when there is no item at the current index.
            cout << " ";
        }
        
        if (i < maxNumItems-1) {
            cout << "|";
        }
    }
    cout << "]";
}

void Inventory::printIndex(int startIndex) {
    cout << " ";
    for (int i = 0; i < maxNumItems; i++) {
        cout << (i+startIndex) % 10;
        
        if (i < maxNumItems-1) {
            cout << " ";
        }
    }
    cout << " ";
}

int Inventory::getMaxNumItems() {
    return maxNumItems;
}

int Inventory::getNumItems() {
    return numItems;
}

bool Inventory::add(Item *item) {
    bool result = false;
    
    for (int i = 0; i < maxNumItems && !result; i++) {
        if (slots[i] == NULL) {
            slots[i] = item;
            result = true;
            numItems++;
        }
    }
    
    return result;
}

void Inventory::addPotion(int amount, Unit *unit) {
    if(unit->isHero()) {
        for (int i = 0; i < amount; i++) {
            
            if (i >= 5) {
                break;
            }
        
            if (slots[i] == NULL) {
                slots[i] = new Potion;
                numItems++;
            } else {
                amount += 1;
            }
            
        }
    }
}

bool Inventory::buyPotion(int amount, Unit *unit) {
    bool result = false;
    int gold = unit->getGold();
    int cost = 0;
    int totalAmount = amount*DEFAULT_POTION_PRICE;
    
    if(gold >= totalAmount && unit->isHero()) {
        for (int i = 0; i < amount; i++) {
           
            if (i >= 5) {
                unit->setGold(gold - cost);
                return false;
            }
            
            if (slots[i] == NULL) {
                slots[i] = new Potion;
                numItems++;
                result = true;
                cost += DEFAULT_POTION_PRICE;
            } else {
                amount += 1;
            }

        }
        
        if (result == true) {
            unit->setGold(gold - cost);
        }
    }
    return result;
}

bool Inventory::setItemAtIndex(int index, Item *item) {
    if (slots[index] != NULL) {
        cout << "error: the index is occupied!!" << endl;
        return false;
    }

    slots[index] = item;
    if (item != NULL) {
        numItems++;
    }
    return true;
}

Item *Inventory::get(int indexToRemove) {
    
    // return NULL when the index is not valid.
    if (indexToRemove < 0 && indexToRemove >= maxNumItems) {
        return NULL;
    }
    
    // when the slot at the index does not have any item.
    if (slots[indexToRemove] == NULL) {
        return NULL;
    }
    // when the slot at the index has an item.
    else {
        return slots[indexToRemove];
    }
}

Item *Inventory::remove(int indexToRemove) {
    // return NULL when the index is not valid.
    if (indexToRemove < 0 && indexToRemove >= maxNumItems) {
        return NULL;
    }
    
    // when the slot at the index does not have any item.
    if (slots[indexToRemove] == NULL) {
        return NULL;
    }
    // when the slot at the index has an item.
    else {
        Item *itemToReturn = slots[indexToRemove];
        slots[indexToRemove] = NULL;
        numItems--;
        return itemToReturn;
    }
}

bool Inventory::use(int indexToUse, Unit *unit) {
    // return NULL when the index is not valid.
    if (indexToUse < 0 && indexToUse >= maxNumItems) {
        return false;
    }
    
    // when the slot at the index does not have any item.
    if (slots[indexToUse] == NULL) {
        return false;
    }
    // when the slot at the index has an item.
    else {
        bool resultUse = slots[indexToUse]->use(unit);
        
        if (resultUse) {
            if (slots[indexToUse]->hasBeenDisposed()) {
                delete slots[indexToUse];
                slots[indexToUse] = NULL;
                numItems--;
            }
            else if (slots[indexToUse]->hasBeenMoved()) {
                slots[indexToUse] = NULL;
                numItems--;
            }
        }
        
        return resultUse;
    }
}

Key *Inventory::getBestKey() {
    int bestIndex = -1;
    for (int i = 0; i < maxNumItems; i++) {
        if (slots[i] != NULL && slots[i]->isConsumable()) {
            ConsumableItem *consumableItem = (ConsumableItem *)slots[i];
            if (consumableItem->isKey()) {
                Key *key = (Key *)consumableItem;
                if (bestIndex == -1) {
                    bestIndex = i;
                }
                else if (((Key *)slots[bestIndex])->getKeyType() < key->getKeyType()) {
                    bestIndex = i;
                }
            }
        }
    }
    
    if (bestIndex != -1) {
        Key *key = (Key *)slots[bestIndex];
        slots[bestIndex] = NULL;
        numItems--;
        return key;
    }

    return NULL;
}

Key *Inventory::checkBestKey() {
    int bestIndex = -1;
    for (int i = 0; i < maxNumItems; i++) {
        if (slots[i] != NULL && slots[i]->isConsumable()) {
            ConsumableItem *consumableItem = (ConsumableItem *)slots[i];
            if (consumableItem->isKey()) {
                Key *key = (Key *)consumableItem;
                if (bestIndex == -1) {
                    bestIndex = i;
                }
                else if (((Key *)slots[bestIndex])->getKeyType() < key->getKeyType()) {
                    bestIndex = i;
                }
            }
        }
    }
    
    if (bestIndex != -1) {
        return (Key *)slots[bestIndex];
    }
    
    return NULL;
}

bool Inventory::addKey(Key *key, Unit *unit) {
    if(unit->isHero()) {
        for (int i = 0; i < maxNumItems; i++) {
            if (slots[i] == NULL) {
                slots[i] = key;
                numItems++;
                return true;
            }
        }
    }
    return false;
}

bool Inventory::isFull() {
    return numItems >= maxNumItems;
}

int Inventory::capacity() {
    return maxNumItems;
}

// Iterator interface
bool Inventory::hasMore() {
    return curIndexForIter < maxNumItems;
}

Item *Inventory::next() {
    //Item *itemToReturn = items[curIndexForIter];
    //curIndexForIter++;
    //return itemToReturn;
    
    // 위의 3라인을 한번에.. 우선 items[curIndexForIter]이 아이템이 리턴될 것이면서..
    // curIndexForIter 얘가 1증가된다.
    return slots[curIndexForIter++];
}

void Inventory::resetIter() {
    curIndexForIter = 0;
}

void Inventory::save(ostream &out) {
    out << "#-------------------- class Inventory" << endl;
    
    out << "# maxNumItems" << endl;
    out << maxNumItems << endl;

    out << "# numItems" << endl;
    out << numItems << endl;
    
    out << "#======================================== slots[] begin" << endl;
    for (int i = 0; i < maxNumItems; i++) {
        if (slots[i] == NULL) {
            out << "#======================================== slots[" << i << "]" << endl;
            out << TOMB_STONE_EMPTY << endl;
        }
        else {
            out << "#======================================== slots[" << i << "]" << endl;
            out << TOMB_STONE_NON_EMPTY << endl;
            out << "# Item ID" << endl;
            out << slots[i]->getID() << endl;
            slots[i]->save(out);
        }
    }
    out << "#======================================== slots[] end" << endl;
    
    // We don't save or load the member variables for Iterator
    //int currentIterIndex;
}

void Inventory::load(istream &in) {
    cout << "Inventory::load(): started" << endl;;
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Inventory" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Inventory::load(): buf=" << buf << endl;
    
    deleteSlots(); // clear
    
    //out << "# maxNumItems" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumItems << endl;
    in >> maxNumItems;
    in.get(); // skip enter code.

    initSlots(maxNumItems); // build new array with the loaded maxNumItems

    //out << "# numItems" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numItems << endl;
    in >> numItems;
    in.get(); // skip enter code.
    
    //out << "#======================================== slots[] begin" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Inventory::load(): buf=" << buf << endl;

    for (int i = 0; i < maxNumItems; i++) {
        //out << "#======================================== slots[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        cout << "Inventory::load(): buf=" << buf << endl;
        
        string tombStone = "";
        in >> tombStone;
        in.get(); // skip enter code.
        
        if (tombStone == TOMB_STONE_EMPTY) {
            slots[i] = NULL;
        }
        else {
            //out << "# Item ID" << endl;
            in.getline(buf, MAX_LEN_BUF); // skip comment
            //out << slots[i]->getID() << endl;
            string itemID = "";
            in >> itemID;
            in.get(); // skip enter code.
            
            slots[i] = createItemByID(itemID); // call factory ??????????????????
            slots[i]->load(in); // ?????????????????????????????????????????????????
        }
    }
    //out << "#======================================== slots[] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Inventory::load(): buf=" << buf << endl;
}
