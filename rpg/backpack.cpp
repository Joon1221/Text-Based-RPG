#include <iostream>

using namespace std;

#include "main.h"
#include "item.h"
#include "backpack.h"

Backpack::Backpack() {
    initBackpack(DEFAULT_BACKPACK_CAPACITY);
}

Backpack::Backpack(int maxNumItems) {
    initBackpack(maxNumItems);
}

void Backpack::initBackpack(int maxNumItems) {
    this->maxNumItems = maxNumItems;
    
    items = new Item * [maxNumItems];
    
    for (int i = 0; i < maxNumItems; i++) {
        items[i] = NULL;
    }
    
    numItems = 0;
    
    curIndexForIter = 0;
}

Backpack::~Backpack() {
    deleteBackpack();
}

void Backpack::deleteBackpack() {
    if (items != NULL) {
        for (int i = 0; i < numItems; i++) {
            if (items[i] != NULL) {
                delete items[i];
            }
        }

        delete [] items;
        items = NULL;
    }
    curIndexForIter = 0;
}

void Backpack::print() {
    cout << "[";
    for (int i = 0; i < maxNumItems; i++) {
        if (items[i] != NULL) {
            items[i]->print();
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

void Backpack::printIndex(int startIndex) {
    cout << " ";
    for (int i = 0; i < maxNumItems; i++) {
        cout << (i+startIndex) % 10;
        
        if (i < maxNumItems-1) {
            cout << " ";
        }
    }
    cout << " ";
}

bool Backpack::push(Item *item) {
    if (isFull()) {
        return false;
    }
    
    items[numItems] = item;
    numItems++;
    return true;
}

Item *Backpack::getItemAt(int index) {
    // validate the given index
    if (index < 0 || index >= maxNumItems) {
        return NULL;
    }
    
    // check if the slot is empty.
    if (items[index] == NULL) {
        cout << "error: the slot is empty." << endl;
        return NULL;
    }
    
    return items[index];
}

Key *Backpack::getBestKey() {
    int bestIndex = -1;
    for (int i = 0; i < numItems; i++) {
        if (items[i] != NULL && items[i]->isConsumable()) {
            ConsumableItem *consumableItem = (ConsumableItem *)items[i];
            if (consumableItem->isKey()) {
                Key *key = (Key *)consumableItem;
                if (bestIndex == -1) {
                    bestIndex = i;
                }
                else if (((Key *)items[bestIndex])->getKeyType() < key->getKeyType()) {
                    bestIndex = i;
                }
            }
        }
    }

    if (bestIndex != -1) {
        Key *key = (Key *)items[bestIndex];
        items[bestIndex] = NULL;
        for (int i = bestIndex; i < numItems-1; i++) { // 땡긴다.
            items[i] = items[i+1];
        }
        items[numItems-1] = NULL;
        numItems--;
        
        return key;
    }
    
    return NULL;
}

Key *Backpack::checkBestKey() {
    int bestIndex = -1;
    for (int i = 0; i < numItems; i++) {
        if (items[i] != NULL && items[i]->isConsumable()) {
            ConsumableItem *consumableItem = (ConsumableItem *)items[i];
            if (consumableItem->isKey()) {
                Key *key = (Key *)consumableItem;
                if (bestIndex == -1) {
                    bestIndex = i;
                }
                else if (((Key *)items[bestIndex])->getKeyType() < key->getKeyType()) {
                    bestIndex = i;
                }
            }
        }
    }
    
    if (bestIndex != -1) {
        return (Key *)items[bestIndex];
    }
    
    return NULL;
}

Item *Backpack::removeItemAt(int index) {
    // validate the given index
    if (index < 0 || index >= maxNumItems) {
        return NULL;
    }
    
    // check if the slot is empty.
    if (items[index] == NULL) {
        cout << "error: the slot is empty." << endl;
        return NULL;
    }
    
    Item *itemToReturn = items[index];
    
    for (int i = index; i < numItems-1; i++) { // 땡긴다.
        items[i] = items[i+1];
    }
    items[numItems-1] = NULL;
    
    numItems--;
    return itemToReturn;
}

bool Backpack::isFull() {
    return numItems >= maxNumItems;
}

bool Backpack::isEmpty() {
    return numItems == 0;
}

int Backpack::size() {
    return numItems;
}

int Backpack::capacity() {
    return maxNumItems;
}

// Iterator interface
bool Backpack::hasMore() {
    return curIndexForIter < numItems;
}

Item *Backpack::next() {
    //Item *itemToReturn = items[curIndexForIter];
    //curIndexForIter++;
    //return itemToReturn;
    
    // 위의 3라인을 한번에.. 우선 items[curIndexForIter]이 아이템이 리턴될 것이면서..
    // curIndexForIter 얘가 1증가된다.
    return items[curIndexForIter++];
}

void Backpack::resetIter() {
    curIndexForIter = 0;
}

void Backpack::save(ostream &out) {
    out << "#-------------------- class Backpack" << endl;
    
    out << "# maxNumItems" << endl;
    out << maxNumItems << endl;
    out << "# numItems" << endl;
    out << numItems << endl;
    
    out << "#======================================== items[] begin" << endl;
    for (int i = 0; i < numItems; i++) {
        out << "#======================================== items[" << i << "]" << endl;
        out << "# Item ID" << endl;
        out << items[i]->getID() << endl;
        items[i]->save(out);
    }
    out << "#======================================== items[] end" << endl;
    
    // We don't save or load the member variables for Iterator
    //int currentIterIndex;
}

void Backpack::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Backpack" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment

    deleteBackpack(); // clear
    
    //out << "# maxNumItems" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumItems << endl;
    in >> maxNumItems;
    in.get(); // skip enter code.

    initBackpack(maxNumItems); // build new array with the loaded maxNumItems

    //out << "# numItems" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numItems << endl;
    in >> numItems;
    in.get(); // skip enter code.
    
    //out << "#======================================== items[] begin" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    for (int i = 0; i < numItems; i++) {
        //out << "#======================================== items[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        
        //out << "# Item ID" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        //out << items[i]->getID() << endl;
        string itemID = "";
        in >> itemID;
        in.get(); // skip enter code.
        
        items[i] = createItemByID(itemID); // call factory ??????????????????
        items[i]->load(in); // ?????????????????????????????????????????????????
    }
    //out << "#======================================== items[] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
}
