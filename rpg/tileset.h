#ifndef SET_H
#define SET_H

class Tile;

class TileNode {
public:
    Tile *tile;
    TileNode *next;
    
    TileNode();
    TileNode(Tile *tile);
};

class TileSet {
private:
    TileNode *head;
    int numNodes;
    
public:
    TileSet();
    virtual ~TileSet();
    
    void print();
    
    // pre-condition: the given tile is not null
    void insert(Tile *tile); // prepend

    // pre-condition: the given tile is not null
    Tile *find(Tile *tile);
    
    // pre-condition: the given tile is not null
    void remove(Tile *tile);
    
    int size();
    
    // pre-condition: size() > 0
    Tile *lowestF();
    Tile *lowestH();
    Tile *lowestG();
};

#endif
