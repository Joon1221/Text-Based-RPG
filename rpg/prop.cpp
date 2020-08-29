#include <iostream>

using namespace std;

#include "main.h"
#include "prop.h"
#include "tree.h"
#include "chest.h"

//==============================================================================
// class Prop
//==============================================================================

// Default Constructor
Prop::Prop() {
    shape = DEFAULT_PROP_SHAPE;
    climbable = DEFAULT_PROP_CLIMBABLE;
}
// General Constructor
Prop::Prop(char shape, bool climbable) {
    this->shape = shape;
    this->climbable = climbable;
}

Prop::~Prop() {}

void Prop::print() {
    cout << shape;
}

bool Prop::isClimbable() {
    return climbable;
}

bool Prop::canGoThroughByThrowableItem() {
    // N/A
    return false;
}

bool Prop::isTree() {
    return false;
}

bool Prop::isChest() {
    return false;
}

bool Prop::isWall() {
    return false;
}

bool Prop::isExit() {
    return false;
}

int Prop::getLockLevel() {
    // N/A
    return 0;
}

bool Prop::trigger(int row, int col, Unit *unit) {
    return false;
}

void Prop::effect(Unit *unit, Item *item, Prop *prop) {
    // N/A
}

void Prop::save(ostream &out) {
    out << "#-------------------- class Prop" << endl;
    
    out << "# shape" << endl;
    out << shape << endl;
    
    out << "# climbable" << endl;
    out << climbable << endl;
}

void Prop::load(istream &in) {
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Prop" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# shape" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << shape << endl;
    in >> shape;
    in.get(); // skip enter code.
    
    //out << "# climbable" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << climbable << endl;
    in >> climbable;
    in.get(); // skip enter code.
    
    // * We don't save or load board.
}

Prop *createPropByShape(char shape) {
    if (shape == DEFAULT_PROP_TREE_SHAPE) {
        return new Tree();
    }
    else if (shape == DEFAULT_CHEST_SHAPE) {
        return new Chest();
    }
    else if (shape == DEFAULT_PROP_WALL_SHAPE_01 ||
             shape == DEFAULT_PROP_WALL_SHAPE_02 ||
             shape == DEFAULT_PROP_WALL_SHAPE_03) {
        return new Wall(shape, DEFAULT_PROP_WALL_CLIMBABLE);
    }
    else if (shape == DEFAULT_PROP_EXIT_SHAPE) {
        return new Exit();
    }
    
    return NULL;
}

Prop *createPropByID(string propID) {
    if (propID == PROP_ID_TREE) {
        return new Tree();
    }
    else if (propID == PROP_ID_WALL) {
        return new Wall();
    }
    else if (propID == PROP_ID_EXIT) {
        return new Exit();
    }
    else if (propID == PROP_ID_CHEST) {
        return new Chest();
    }
    
    return NULL;
}

//==============================================================================
// class Wall
//==============================================================================

// Default Constructor
Wall::Wall() : Prop(DEFAULT_PROP_WALL_SHAPE_01, DEFAULT_PROP_WALL_CLIMBABLE) {
}
// General Constructor
Wall::Wall(char shape, bool climbable)  : Prop(shape, climbable) {
}

Wall::~Wall() {}

void Wall::print() {
#ifdef ANSI_COLOR_OUTPUT
    cout << GREEN;
#endif
    cout << shape;
#ifdef ANSI_COLOR_OUTPUT
    cout << RESET;
#endif
}

bool Wall::isWall() {
    return true;
}

string Wall::getID() {
    return string(PROP_ID_WALL);
}

void Wall::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class Wall" << endl;
}

void Wall::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Wall" << endl;
    in.getline(buf, 80); // skip comment
}

//==============================================================================
// class Exit
//==============================================================================

// Default Constructor
Exit::Exit() : Prop(DEFAULT_PROP_EXIT_SHAPE, DEFAULT_PROP_EXIT_CLIMBABLE) {
}
// General Constructor
Exit::Exit(char shape, bool climbable)  : Prop(shape, climbable) {
}

Exit::~Exit() {}

void Exit::print() {
#ifdef ANSI_COLOR_OUTPUT
    cout << GREEN;
#endif
    cout << shape;
#ifdef ANSI_COLOR_OUTPUT
    cout << RESET;
#endif
}

bool Exit::isClimbable() {
    return true;
}

bool Exit::isExit() {
    return true;
}

string Exit::getID() {
    return string(PROP_ID_EXIT);
}

void Exit::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class Exit" << endl;
}

void Exit::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Exit" << endl;
    in.getline(buf, 80); // skip comment
}
