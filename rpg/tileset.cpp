#include <iostream>
#include <assert.h>

using namespace std;

#include "tile.h"
#include "tileset.h"

//------------------------------------------------------------------------------
// class TileNode
//------------------------------------------------------------------------------
TileNode::TileNode() { // 사실 만들 필요 없다. 얘는..
    tile = NULL;
    next = NULL;
}

TileNode::TileNode(Tile *tile) { // 주로 이것을 쓸 것임.
    this->tile = tile;
    next = NULL;
}

//------------------------------------------------------------------------------
// class TileSet
//------------------------------------------------------------------------------
TileSet::TileSet() {
    head = NULL;
    numNodes = 0;
}

TileSet::~TileSet() {
    if (head != NULL) { // size() > 0
        if (head->next == NULL) { // size() == 1
            delete head;
            head = NULL;
            numNodes = 0;
        }
        else { // size() > 1
            TileNode *current = head;
            
            while (current != NULL) {
                TileNode *next = current->next;
                delete current;
                
                current = next;
            }
            head = NULL;
            numNodes = 0;
        }
    }
}

void TileSet::print() {
    TileNode *current = head;
    
    while (current != NULL) {
        current->tile->print();
        if (current->next != NULL) {
            cout << "->";
        }
        else {
            cout << "-||";
        }
        
        current = current->next;
    }
    cout << endl;
}

// pre-condition: the given tile is not NULL && find(tile) == NULL
void TileSet::insert(Tile *tile) { // prepend
    assert(tile != NULL);
    assert(find(tile) == NULL);
    
    TileNode *newNode = new TileNode(tile);
    
    if (head == NULL) { // size() == 0
        head = newNode;
        numNodes++;
    }
    else { // size() >= 1
        newNode->next = head;
        head = newNode;
        numNodes++;
    }
}

// pre-condition: the given tile is not null
Tile *TileSet::find(Tile *tile) {
    assert(tile != NULL);

    TileNode *current = head;
    
    while (current != NULL) {
        // 현재 노드의 elem가 찾는 elem과 같다면, index를 return.
        if (tile == current->tile) {
            return current->tile;
        }
        
        current = current->next;
    }
    
    return NULL;
}

// pre-condition: the given tile is not null
void TileSet::remove(Tile *tile) {
    assert(tile != NULL);

    TileNode *prev = NULL;
    TileNode *current = head;
    
    while (current != NULL) {
        if (tile == current->tile) {
            // when the node is the first node.
            if (prev == NULL) {
                head = head->next;
                delete current;
                numNodes--;
            }
            // when the node is not the first node.
            else {
                prev->next = current->next;
                delete current;
                numNodes--;
            }
        }
        
        prev = current;
        current = current->next;
    }
}

int TileSet::size() {
    return numNodes;
}

// pre-condition: size() > 0
Tile *TileSet::lowestF() {
    assert(size() > 0);
    
    Tile *lowestF = head->tile;
    
    TileNode *current = head->next;
    
    while (current != NULL) {
        if (lowestF->f > current->tile->f) {
            lowestF = current->tile;
        }
        
        current = current->next;
    }
    
    return lowestF;
}

Tile *TileSet::lowestH() {
    assert(size() > 0);
    
    Tile *lowestH = head->tile;
    
    TileNode *current = head->next;
    
    while (current != NULL) {
        if (lowestH->h > current->tile->h) {
            lowestH = current->tile;
        }
        
        current = current->next;
    }
    
    return lowestH;
}

Tile *TileSet::lowestG() {
    assert(size() > 0);
    
    Tile *lowestG = head->tile;
    
    TileNode *current = head->next;
    
    while (current != NULL) {
        if (lowestG->g > current->tile->g) {
            lowestG = current->tile;
        }
        
        current = current->next;
    }
    
    return lowestG;
}

