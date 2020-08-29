#ifndef TILE_H
#define TILE_H

class Unit;
class Item;
class Prop;

#define FX_NONE '\0'
#define MAX_NUM_THROWING_ITEMS 10

class Tile {
private:
    char fx; // fx layer
    Unit *unit;
    
    int numThrowingItems;
    Item *throwingItem[MAX_NUM_THROWING_ITEMS];
    
    Item *item;
    Prop *prop;
    
public:
    Tile();
    Tile(Tile &other);
    virtual ~Tile();
    void print();
    Unit *getUnit();
    
    char getFx();
    void setFx(char fx);
    void clearFx(); // resteFx()
    
    void setUnit(Unit *unit);

    int getNumThrowingItems();
    Item *getThrowingItem(int index);
    void setThrowingItem(Item *item);
    void processThrowingItems(int row, int col);

    Item *getItem();
    void setItem(Item *item);

    Prop *getProp();
    void setProp(Prop *prop);

    bool isEmpty();
    bool isClimbable();
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    //--------------------------------------------------------------------------
    // A* related
    //--------------------------------------------------------------------------
    int row;
    int col;
    
    double f;
    double g;
    double h;
    
    int cameFromRow;
    int cameFromCol;
    
    void resetAStar();
};

#endif
