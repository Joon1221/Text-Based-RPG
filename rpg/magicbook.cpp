#include <iostream>

using namespace std;

#include "main.h"
#include "magicbook.h"
#include "magic.h"
#include "unit.h"
#include "item.h"

// Default Constructor
Magicbook::Magicbook() {
    initMagicbook(3);
}

// General Constructor
Magicbook::Magicbook(int maxNumItems) {
    initMagicbook(maxNumItems);

}

void Magicbook::initMagicbook(int maxNumItems) {
    this->maxNumItems = maxNumItems;
    numItems = 0;
    
    magicbook = new Magic *[maxNumItems];
    
    for (int i = 0; i < maxNumItems; i++) {
        magicbook[i] = NULL;
    }
    
    curIndexForIter = 0;
}

Magicbook::~Magicbook() {
    deleteMagicbook();
}

void Magicbook::deleteMagicbook() {
    if (magicbook != NULL) {
        for (int i = 0; i < maxNumItems; i++) {
            if (magicbook[i] != NULL) {
                delete magicbook[i];
                magicbook[i] = NULL;
            }
        }
        numItems = 0;
        
        delete [] magicbook;
        magicbook = NULL;
        
        curIndexForIter = 0;
    }
}

void Magicbook::print() {
    cout << "[";
    for (int i = 0; i < maxNumItems; i++) {
        if (magicbook[i] != NULL) {
            magicbook[i]->print();
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

void Magicbook::printIndex(int startIndex) {
    cout << " ";
    for (int i = 0; i < maxNumItems; i++) {
        cout << (i+startIndex) % 10;
        
        if (i < maxNumItems-1) {
            cout << " ";
        }
    }
    cout << " ";
}

int Magicbook::getMaxNumItems() {
    return maxNumItems;
}

int Magicbook::getNumItems() {
    return numItems;
}

int Magicbook::getSkillNumberAtIndex(int index) {
    return magicbook[index]->getSkillNumber();
}

bool Magicbook::add(Magic *magic) {
    if (isFull()) {
        cout << "error: the magic book is full!" << endl;
        return false;
    }
    
    bool isRepeated = false;

    for (int i = 0; i < maxNumItems; i++) {
        if (magicbook[i] != NULL &&
            magicbook[i]->getJob() == magic->getJob() &&
            magicbook[i]->getSkillNumber() == magic->getSkillNumber()) {
            isRepeated = true;
            break;
        }
    }
    
    if (isRepeated) {
        return false;
    }

    for (int i = 0; i < maxNumItems; i++) {
        if (magicbook[i] == NULL) {
            magicbook[i] = magic;
            break;
        }
    }
    
    return true;
}

bool Magicbook::setMagicAtIndex(int index, Magic *magic) {
    if (magicbook[index] != NULL) {
        cout << "error: the index is occupied!!" << endl;
        return false;
    }
    magicbook[index] = magic;
    return true;
}

Magic *Magicbook::get(int indexToRemove) {
    
    // return NULL when the index is not valid.
    if (indexToRemove < 0 && indexToRemove >= maxNumItems) {
        return NULL;
    }
    
    // when the slot at the index does not have any item.
    if (magicbook[indexToRemove] == NULL) {
        return NULL;
    }
    // when the slot at the index has an item.
    else {
        return magicbook[indexToRemove];
    }
}

Magic *Magicbook::remove(int indexToRemove) {
    // return NULL when the index is not valid.
    if (indexToRemove < 0 && indexToRemove >= maxNumItems) {
        return NULL;
    }
    
    // when the slot at the index does not have any item.
    if (magicbook[indexToRemove] == NULL) {
        return NULL;
    }
    // when the slot at the index has an item.
    else {
        Magic *magicToReturn = magicbook[indexToRemove];
        magicbook[indexToRemove] = NULL;
        numItems--;
        return magicToReturn;
    }
}

bool Magicbook::cast(int indexToUse, Unit *unit) {
    // return NULL when the index is not valid.
    if (indexToUse < 0 && indexToUse >= maxNumItems) {
        return false;
    }
    
    // when the slot at the index does not have any item.
    if (magicbook[indexToUse] == NULL) {
        return false;
    }
    // when the slot at the index has an item.
    else {
        bool resultUse = magicbook[indexToUse]->cast(unit);
        
        return resultUse;
    }
}

bool Magicbook::isFull() {
    return numItems >= maxNumItems;
}

int Magicbook::capacity() {
    return maxNumItems;
}

// Iterator interface
bool Magicbook::hasMore() {
    return curIndexForIter < maxNumItems;
}

Magic *Magicbook::next() {
    //Item *itemToReturn = items[curIndexForIter];
    //curIndexForIter++;
    //return itemToReturn;
    
    // 위의 3라인을 한번에.. 우선 items[curIndexForIter]이 아이템이 리턴될 것이면서..
    // curIndexForIter 얘가 1증가된다.
    return magicbook[curIndexForIter++];
}

void Magicbook::resetIter() {
    curIndexForIter = 0;
}

void Magicbook::save(ostream &out) {
    out << "#-------------------- class Magicbook" << endl;
    
    out << "# maxNumItems" << endl;
    out << maxNumItems << endl;
    out << "# numItems" << endl;
    out << numItems << endl;
    
    out << "#======================================== magicbook[] begin" << endl;
    for (int i = 0; i < maxNumItems; i++) {
        if (magicbook[i] == NULL) {
            out << "#======================================== magicbook[" << i << "]" << endl;
            out << TOMB_STONE_EMPTY << endl;
        }
        else {
            out << "#======================================== magicbook[" << i << "]" << endl;
            out << TOMB_STONE_NON_EMPTY << endl;
            out << "# Magic ID" << endl;
            out << magicbook[i]->getID() << endl;
            magicbook[i]->save(out);
        }
    }
    out << "#======================================== magicbook[] end" << endl;
    
    // We don't save or load the member variables for Iterator
    //int currentIterIndex;
}

void Magicbook::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Magicbook" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    deleteMagicbook(); // clear
    
    //out << "# maxNumItems" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumItems << endl;
    in >> maxNumItems;
    in.get(); // skip enter code.
    
    initMagicbook(maxNumItems); // build new array with the loaded maxNumItems
    
    //out << "# numItems" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numItems << endl;
    in >> numItems;
    in.get(); // skip enter code.
    
    //out << "#======================================== magicbook[] begin" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    for (int i = 0; i < maxNumItems; i++) {
        //out << "# magicbook[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        
        string tombStone = "";
        in >> tombStone;
        in.get(); // skip enter code.
        
        if (tombStone == TOMB_STONE_EMPTY) {
            magicbook[i] = NULL;
        }
        else {
            //out << "# Magic ID" << endl;
            in.getline(buf, MAX_LEN_BUF); // skip comment
            //out << magicbook[i]->getID() << endl;
            string magicID = "";
            in >> magicID;
            in.get(); // skip enter code.
            
            magicbook[i] = createMagicByID(magicID);
            magicbook[i]->load(in);
        }
    }
    //out << "#======================================== magicbook[] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
}
