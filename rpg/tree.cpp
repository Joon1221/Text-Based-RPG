#include <iostream>

using namespace std;

#include "main.h"
#include "prop.h"
#include "tree.h"

// Default Constructor
Tree::Tree() : Prop(DEFAULT_PROP_TREE_SHAPE, DEFAULT_PROP_TREE_CLIMBABLE) {
}
// General Constructor
Tree::Tree(char shape, bool climbable)  : Prop(shape, climbable) {
}

Tree::~Tree() {}

void Tree::print() {
#ifdef ANSI_COLOR_OUTPUT
    cout << GREEN;
#endif
    cout << shape;
#ifdef ANSI_COLOR_OUTPUT
    cout << RESET;
#endif
}

bool Tree::isTree() {
    return true;
}

string Tree::getID() {
    return string(PROP_ID_TREE);
}

void Tree::save(ostream &out) {
    Prop::save(out);
    
    out << "#-------------------- class Tree" << endl;
}

void Tree::load(istream &in) {
    Prop::load(in);
    
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Tree" << endl;
    in.getline(buf, 80); // skip comment
}
