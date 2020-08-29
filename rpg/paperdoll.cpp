#include <iostream>

using namespace std;

#include "main.h"
#include "unit.h"
#include "item.h"
#include "paperdoll.h"

Paperdoll::Paperdoll() {
    
    head = NULL;
    chest = NULL;
    back = NULL;
    hands = NULL;
    legs = NULL;
    feet = NULL;
    
    leftHand = NULL;
    rightHand = NULL;
}

Paperdoll::Paperdoll(Paperdoll &other) {
}

Paperdoll::~Paperdoll() {
    
    if (head != NULL) {
        delete head;
    }
    
    if (chest != NULL) {
        delete chest;
    }
    
    if (back != NULL) {
        delete back;
    }
    
    if (hands != NULL) {
        delete hands;
    }
    
    if (legs != NULL) {
        delete legs;
    }
    
    if (feet != NULL) {
        delete feet;
    }
    
    if (leftHand != NULL) {
        delete leftHand;
    }
    
    if (rightHand != NULL) {
        delete rightHand;
    }
    
}

void Paperdoll::print() {
    if (head != NULL) {
        cout << "head(" << *head << ") ";
    }
    else {
        cout << "head( ) ";
    }
    if (chest != NULL) {
        cout << "chest(" << *chest << ") ";
    }
    else {
        cout << "chest( ) ";
    }
    if (back != NULL) {
        cout << "back(" << *back << ") ";
    }
    else {
        cout << "back( ) ";
    }
    if (hands != NULL) {
        cout << "hnds(" << *hands << ") ";
    }
    else {
        cout << "hnds( ) ";
    }
    if (legs != NULL) {
        cout << "legs(" << *legs << ") ";
    }
    else {
        cout << "legs( ) ";
    }
    if (feet != NULL) {
        cout << "feet(" << *feet << ") ";
    }
    else {
        cout << "feet( ) ";
    }
    if (leftHand != NULL) {
        cout << "lh(" << *leftHand << ") ";
    }
    else {
        cout << "lh( ) ";
    }
    if (rightHand != NULL) {
        cout << "rh(" << *rightHand << ")";
    }
    else {
        cout << "rh( )";
    }
}

void Paperdoll::printIndex() {
    cout << "     1        2       3       4       5       6     7     8 ";
}

/*
 #define BODY_PART_ID_HEAD 1
 #define BODY_PART_ID_CHEST 2
 #define BODY_PART_ID_BACK 3
 #define BODY_PART_ID_HANDS 4
 #define BODY_PART_ID_LEGS 5
 #define BODY_PART_ID_FEET 6
 */
bool Paperdoll::equip(Item *item, Unit *unit) {
    if (item->isEquipable() && unit->getLevel() >= item->getLevel()) {
        EquipableItem *equipableItem = (EquipableItem *)item;
        if (equipableItem->isArmor()) {
            Armor *armor = (Armor *)equipableItem;
            
            if (armor->getBodyPartID() == BODY_PART_ID_HEAD) {
                if (head != NULL) {
                    return false;
                }
                else { // empty
                    head = armor;
                }
            }
            else if (armor->getBodyPartID() == BODY_PART_ID_CHEST) {
                if (chest != NULL) {
                    return false;
                }
                else { // empty
                    chest = armor;
                }
            }
            else if (armor->getBodyPartID() == BODY_PART_ID_BACK) {
                if (back != NULL) {
                    return false;
                }
                else { // empty
                    back = armor;
                }
            }
            else if (armor->getBodyPartID() == BODY_PART_ID_HANDS) {
                if (hands != NULL) {
                    return false;
                }
                else { // empty
                    hands = armor;
                }
            }
            else if (armor->getBodyPartID() == BODY_PART_ID_LEGS) {
                if (legs != NULL) {
                    return false;
                }
                else { // empty
                    legs = armor;
                }
            }
            else if (armor->getBodyPartID() == BODY_PART_ID_FEET) {
                if (feet != NULL) {
                    return false;
                }
                else { // empty
                    feet = armor;
                }
            }
            else {
                cout << "fatal error: no such armor \"" << armor->getBodyPartID() << "\" exist!" << endl;
                exit(1);
            }
            
            unit->incDef(armor->getDef());
            return true;
        }
        else if (equipableItem->isWeapon()) {
            Weapon *weapon = (Weapon *)equipableItem;
            if (weapon->getNumHands() == WEAPON_ONE_HAND && weapon->getJob() == unit->getJob()) {
                if (rightHand == NULL) {
                    rightHand = weapon;
                    
                    if (rightHand->getRangeAttack()) {
                        unit->incRangeAtk(weapon->getAtk());
                    }
                    else {
                        unit->incMeleeAtk(weapon->getAtk());
                    }
                    
                    return true;
                }
                else if (leftHand == NULL && rightHand->getNumHands() == 1) {
                    leftHand = weapon;
                    
                    if (leftHand->getRangeAttack()) {
                        unit->incRangeAtk(weapon->getAtk());
                    }
                    else {
                        unit->incMeleeAtk(weapon->getAtk());
                    }
                    
                    return true;
                }
                else {
                    return false;
                }
            }
            else if (weapon->getNumHands() == WEAPON_TWO_HAND && weapon->getJob() == unit->getJob()) {
                if (rightHand == NULL) {
                    rightHand = weapon;
                    
                    if (rightHand->getRangeAttack()) {
                        unit->incRangeAtk(weapon->getAtk());
                    }
                    else {
                        unit->incMeleeAtk(weapon->getAtk());
                    }
                    
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
    return false;
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
 */

Item *Paperdoll::unequip(int bodyPartID, Unit *unit) {
    if (bodyPartID == BODY_PART_ID_HEAD) {
        if (head != NULL) {
            Item *itemToReturn = head;
            unit->decDef(head->getDef());
            head = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == BODY_PART_ID_CHEST) {
        if (chest != NULL) {
            Item *itemToReturn = chest;
            unit->decDef(chest->getDef());
            chest = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == BODY_PART_ID_BACK) {
        if (back != NULL) {
            Item *itemToReturn = back;
            unit->decDef(back->getDef());
            back = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == BODY_PART_ID_HANDS) {
        if (hands != NULL) {
            Item *itemToReturn = hands;
            unit->decDef(hands->getDef());
            hands = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == BODY_PART_ID_LEGS) {
        if (legs != NULL) {
            Item *itemToReturn = legs;
            unit->decDef(legs->getDef());
            legs = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == BODY_PART_ID_FEET) {
        if (feet != NULL) {
            Item *itemToReturn = feet;
            unit->decDef(feet->getDef());
            feet = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == BODY_PART_ID_LEFT_HAND) {
        if (leftHand != NULL) {
            Item *itemToReturn = leftHand;
            
            if (leftHand->getRangeAttack()) {
                unit->decRangeAtk(leftHand->getAtk());
            }
            else {
                unit->decMeleeAtk(leftHand->getAtk());
            }
            
            leftHand = NULL;
            return itemToReturn;
        }
    }
    else if (bodyPartID == BODY_PART_ID_RIGHT_HAND) {
        if (rightHand != NULL) {
            Item *itemToReturn = rightHand;
            
            if (rightHand->getRangeAttack()) {
                unit->decRangeAtk(rightHand->getAtk());
            }
            else {
                unit->decMeleeAtk(rightHand->getAtk());
            }
            
            rightHand = leftHand;
            leftHand = NULL;
            return itemToReturn;
        }
    }
    
    return NULL;
}


Armor *Paperdoll::getArmor(int bodyPartID) {
    
    // return NULL when the index is not valid.
    if (bodyPartID < 0 && bodyPartID >= 5) {
        return NULL;
    }
    
    // when the slot at the index does not have any item.
    if (bodyPartID == BODY_PART_ID_HEAD) {
        if (head != NULL) {
            Item *itemToReturn = head;
            Armor* armor = (Armor*) itemToReturn;
            return armor;
        }
    }
    else if (bodyPartID == BODY_PART_ID_CHEST) {
        if (chest != NULL) {
            Item *itemToReturn = chest;
            Armor* armor = (Armor*) itemToReturn;
            return armor;

        }
    }
    else if (bodyPartID == BODY_PART_ID_BACK) {
        if (back != NULL) {
            Item *itemToReturn = back;
            Armor* armor = (Armor*) itemToReturn;
            return armor;

        }
    }
    else if (bodyPartID == BODY_PART_ID_HANDS) {
        if (hands != NULL) {
            Item *itemToReturn = hands;
            Armor* armor = (Armor*) itemToReturn;
            return armor;

        }
    }
    else if (bodyPartID == BODY_PART_ID_LEGS) {
        if (legs != NULL) {
            Item *itemToReturn = legs;
            Armor* armor = (Armor*) itemToReturn;
            return armor;

        }
    }
    else if (bodyPartID == BODY_PART_ID_FEET) {
        if (feet != NULL) {
            Item *itemToReturn = feet;
            Armor* armor = (Armor*) itemToReturn;
            return armor;

        }
    }
    
    return NULL;
}

Weapon *Paperdoll::getWeapon(int bodyPartID) {
    
    // return NULL when the index is not valid.
    if (bodyPartID < 5 && bodyPartID >= 8) {
        return NULL;
    }
    
    // when the slot at the index does not have any item.
    if (bodyPartID == BODY_PART_ID_LEFT_HAND) {
        if (leftHand != NULL) {
            Weapon *itemToReturn = leftHand;

            return itemToReturn;
        }
    }
    else if (bodyPartID == BODY_PART_ID_RIGHT_HAND) {
        if (rightHand != NULL) {
            Weapon *itemToReturn = rightHand;

            return itemToReturn;
            
        }
    }
    return NULL;
}

void Paperdoll::save(ostream &out) {
    out << "#-------------------- class Paperdoll" << endl;
    
    out << "#======================================== head" << endl;
    if (head == NULL) {
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << TOMB_STONE_NON_EMPTY << endl;
        head->save(out);
    }

    out << "#======================================== chest" << endl;
    if (chest == NULL) {
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << TOMB_STONE_NON_EMPTY << endl;
        chest->save(out);
    }

    out << "#======================================== back" << endl;
    if (back == NULL) {
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << TOMB_STONE_NON_EMPTY << endl;
        back->save(out);
    }

    out << "#======================================== hands" << endl;
    if (hands == NULL) {
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << TOMB_STONE_NON_EMPTY << endl;
        hands->save(out);
    }

    out << "#======================================== legs" << endl;
    if (legs == NULL) {
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << TOMB_STONE_NON_EMPTY << endl;
        legs->save(out);
    }

    out << "#======================================== feet" << endl;
    if (feet == NULL) {
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << TOMB_STONE_NON_EMPTY << endl;
        feet->save(out);
    }

    out << "#======================================== leftHand" << endl;
    if (leftHand == NULL) {
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << TOMB_STONE_NON_EMPTY << endl;
        leftHand->save(out);
    }

    out << "#======================================== rightHand" << endl;
    if (rightHand == NULL) {
        out << TOMB_STONE_EMPTY << endl;
    }
    else {
        out << TOMB_STONE_NON_EMPTY << endl;
        rightHand->save(out);
    }

}

void Paperdoll::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Paperdoll" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "#======================================== head" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    string tombStone = "";
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        head = NULL;
    }
    else {
        head = new Armor();
        head->load(in);
    }

    //out << "#======================================== chest" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        chest = NULL;
    }
    else {
        chest = new Armor();
        chest->load(in);
    }

    //out << "#======================================== back" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        back = NULL;
    }
    else {
        back = new Armor();
        back->load(in);
    }

    //out << "#======================================== hands" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        hands = NULL;
    }
    else {
        hands = new Armor();
        hands->load(in);
    }

    //out << "#======================================== legs" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        legs = NULL;
    }
    else {
        legs = new Armor();
        legs->load(in);
    }

    //out << "#======================================== feet" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        feet = NULL;
    }
    else {
        feet = new Armor();
        feet->load(in);
    }

    //out << "#======================================== leftHand" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        leftHand = NULL;
    }
    else {
        leftHand = new Weapon();
        leftHand->load(in);
    }

    //out << "#======================================== rightHand" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    in >> tombStone;
    in.get(); // skip enter code.
    
    if (tombStone == TOMB_STONE_EMPTY) {
        rightHand = NULL;
    }
    else {
        rightHand = new Weapon();
        rightHand->load(in);
    }
}
