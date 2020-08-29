#include <iostream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "backpack.h"
#include "merchant.h"
#include "util.h"

// Default Constructor
Merchant::Merchant() : Unit(DEFAULT_MERCHANT_SHAPE, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, false) {
    initMerchant(DEFAULT_MERCHANT_NUM_ITEMS_TO_SELL);
}

Merchant::~Merchant() {
    if (itemsToSell != NULL) {
        delete itemsToSell;
        itemsToSell = NULL;
    }
    if (itemsBought != NULL) {
        delete itemsBought;
        itemsBought = NULL;
    }
}

void Merchant::initMerchant(int numItemsToSell) {
    initItemsToSell(numItemsToSell);
    initItemsBought();
}

void Merchant::destroyMerchant() {
    destroyItemsToSell();
    destroyItemsBought();
}

void Merchant::initItemsToSell(int numItemsToSell) {
    itemsToSell = new Backpack();
    
    for (int i = 0; i < numItemsToSell; i++) {
        itemsToSell->push(createRandItem());
    }
}

void Merchant::destroyItemsToSell() {
    if (itemsToSell != NULL) {
        delete itemsToSell;
        itemsToSell = NULL;
    }
}

void Merchant::initItemsBought() {
    itemsBought = new Backpack(DEFAULT_MERCHANT_ITEMS_BOUGHT_CAPACITY);
}

void Merchant::destroyItemsBought() {
    if (itemsBought != NULL) {
        delete itemsBought;
        itemsBought = NULL;
    }
}

bool Merchant::isMerchant() {
    return true;
}

void Merchant::interact(Unit *unit) {
    char userInput = '\0';
    while (true) {
        cout << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "---------------------------------  Merchant -----------------------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "(B)uy, (S)ell, or (Q)uit: ";
        while (_kbhit() == 0) {}
        userInput = getchar();
        
        if (userInput == 'b' || userInput == 'B') {
            buy(unit);
        }
        else if (userInput == 's' || userInput == 'S') {
            sell(unit);
        }
        else if (userInput == 'q' || userInput == 'Q') {
            break;
        }
    }
    
    cout << "Bye!!!" << endl;
}

void Merchant::buy(Unit *unit) {
    // show menu buy
    while (true) {
        //----------------------------------------------------------------------
        // show the list of items
        //----------------------------------------------------------------------
        cout << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "---------------------------------- Merchant ------------------------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Items to Sell <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
        
        int curIndexItemToSell = 0;
        itemsToSell->resetIter();
        
        while (itemsToSell->hasMore()) {
            Item *curItem = itemsToSell->next();
            cout << setw(3) << curIndexItemToSell << ": ";
            curItem->printFullSpec();
            cout << endl;
            
            curIndexItemToSell++;
        }
        
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Items from you <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
        
        int curIndexItemBought = 100;
        itemsBought->resetIter();
        
        while (itemsBought->hasMore()) {
            Item *curItem = itemsBought->next();
            cout << setw(3) << curIndexItemBought << ": ";
            curItem->printFullSpec();
            cout << endl;
            
            curIndexItemBought++;
        }
        
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "--------------------------------- Hero's Stat ----------------------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        
        //----------------------------------------------------------------------
        // show hero's stat
        //----------------------------------------------------------------------
        unit->printStat(1, true, 1);
        
        //----------------------------------------------------------------------
        // validate the index from user
        //----------------------------------------------------------------------
        cout << "--------------------------------------------------------------------------------" << endl;
        int indexToBuy = -1;
        cout << "Enter the index of the item to buy (-1 to exit) : ";
        cin >> indexToBuy;
        
        
        //----------------------------------------------------------------------
        // validate the index from user
        //----------------------------------------------------------------------
        if (indexToBuy == -1) { // exit?
            cin.get();
            break;
        }
        // index of itemsToSell?
        if (indexToBuy >= 0 && indexToBuy < itemsToSell->size()) {
            if (unit->getGold() >= itemsToSell->getItemAt(indexToBuy)->getPrice()) {
                if (unit->hasRoom()) {
                    unit->decGold(itemsToSell->getItemAt(indexToBuy)->getPrice());
                    unit->receiveItem(itemsToSell->getItemAt(indexToBuy)->clone());
                }
                else {
                    cout << "error: You don't have enough room!" << endl;
                }
            }
            else {
                cout << "error: You can't afford the price!" << endl;
            }
        }
        // index of itemsBought?
        else if (indexToBuy >= 100 && indexToBuy < itemsBought->size()+100) {
            indexToBuy -= 100;
            if (unit->getGold() >= itemsBought->getItemAt(indexToBuy)->getPrice()) {
                if (unit->hasRoom()) {
                    unit->decGold(itemsBought->getItemAt(indexToBuy)->getPrice());
                    unit->receiveItem(itemsBought->removeItemAt(indexToBuy));
                }
                else {
                    cout << "error: You don't have enough room!" << endl;
                }
            }
            else {
                cout << "error: You can't afford the price!" << endl;
            }
        }
        else {
            cout << "error: invalid index!" << endl;
        }
    }
}

void Merchant::sell(Unit *unit) {
    // show menu buy
    while (true) {
        //----------------------------------------------------------------------
        // show the list of items of unit(hero)
        //----------------------------------------------------------------------
        cout << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "---------------------------------  Merchant -----------------------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        unit->showItemsListToSell();
        
        //----------------------------------------------------------------------
        // show hero's stat
        //----------------------------------------------------------------------
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "--------------------------------- Hero's Stat ----------------------------------" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        unit->printStat(1, true, 1);
        
        //----------------------------------------------------------------------
        // validate the index from user
        //----------------------------------------------------------------------
        cout << "--------------------------------------------------------------------------------" << endl;
        int indexToSell = -1;
        cout << "Enter the index of the item to sell (-1 to exit) : ";
        cin >> indexToSell;
        
        
        //----------------------------------------------------------------------
        // validate the index from user
        //----------------------------------------------------------------------
        if (indexToSell == -1) { // exit?
            cin.get();
            break;
        }
        
        // index of slots?
        Item *itemFromUnit = unit->removeItemByIndex(indexToSell);
        if (itemFromUnit != NULL) {
            unit->incGold(itemFromUnit->getPrice());
            itemsBought->push(itemFromUnit);
        }
        else {
            cout << "error: invalid index or no item!" << endl;
        }
    }
}

void Merchant::move(int moveDir) {
}

string Merchant::getID() {
    return string(UNIT_ID_MERCHANT);
}

void Merchant::save(ostream &out) {
    Unit::save(out);
    out << "#-------------------- class Merchant" << endl;

    out << "# itemsToSell->size()" << endl;
    out << itemsToSell->size() << endl;
    
    out << "#--------------------------------------- itemsToSell" << endl;
    itemsToSell->save(out);
    out << "#--------------------------------------- itemsBought" << endl;
    itemsBought->save(out);
}

void Merchant::load(istream &in) {
    Unit::load(in);
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Merchant" << endl;
    in.getline(buf, 80); // skip comment

    destroyMerchant();
    
    //out << "# itemsToSell->size()" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    int numItemsToSell = 0;
    //out << itemsToSell->size() << endl;
    in >> numItemsToSell;
    in.get(); // skip enter code.
    
    initMerchant(numItemsToSell);

    //out << "#--------------------------------------- itemsToSell" << endl;
    in.getline(buf, 80); // skip comment

    itemsToSell->load(in);

    //out << "#--------------------------------------- itemsBought" << endl;
    in.getline(buf, 80); // skip comment
    
    //itemsBought->save(out);
    itemsBought->load(in);
}
