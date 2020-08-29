#ifndef BOARD_H
#define BOARD_H

class Unit;
class Hero;
class Item;
class Mon;
class Boss;
class Prop;
class Tile;
class Shockwave;
class Merchant;
class Car;
class Dragon;

//------------------------------------------------------------------------------
// class Board
//------------------------------------------------------------------------------
class Board {
private:
//public:
    Tile ***board;
    bool **visited;
    int **visitedOrder;

    int rowSize;
    int colSize;
    
    Mon **mons;
    int maxNumMons;
    int numMons;

    Boss **bosses;
    int maxNumBosses;
    int numBosses;

    Merchant **merchants;
    int maxNumMerchants;
    int numMerchants;
    
    Car **cars;
    int maxNumCars;
    int numCars;

    Dragon **dragons;
    int maxNumDragons;
    int numDragons;
    
    Hero *hero;

    bool exited;
    
    //--------------------------------------------------------------------------
    // for shockwave
    //--------------------------------------------------------------------------
    Shockwave **shockwaves;
    int maxNumShockwaves;
    int numShockwaves;
    
    //--------------------------------------------------------------------------
    // for loadLevel()
    //--------------------------------------------------------------------------
    char **title;
    int titleRowSize;
    int titleColSize;
    
    char **ending;
    int endingRowSize;
    int endingColSize;

    //--------------------------------------------------------------------------
    // private helper functions
    //--------------------------------------------------------------------------
    void initBoard(int rowSize, int colSize, Hero *hero);
    void resetVisited();
    void initProps();
    void initTrees();
    void initChest();
    void initMons();
    void initBosses();
    void initMerchants();
    void initCars();
    void initDragons();
    void initItems();
    void initFx();

    void destroyAll();
    void destroyMons();
    void destroyBosses();
    void destroyMerchants();
    void destroyCars();
    void destroyDragons();
    void destroyFx();

public:
    Board();
    virtual ~Board();
    
    void init();
    void init(int rowSize, int colSize, Hero *hero);
    void loadLevel(int levelID, Hero *hero);
    
    void print(int firstGap, int row, int col, int viewportRangeRow, int viewportRangeCol);
    
    void clearFx(int row, int col);
    void setFx(int row, int col, char fx);
    void startWave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                   int row, int col, int range, int frameInterval, char fxShape, int skillNumber);
    
    int getRowSize();
    int getColSize();
    
    Hero *getHero();

    Tile *getTile(int row, int col);

    Unit *getUnit(int row, int col);
    bool setUnit(int row, int col, Unit *unit);
    void removeUnit(int row, int col);
    
    Prop *getProp(int row, int col);
    bool setProp(int row, int col, Prop *prop);

    Item *getItem(int row, int col);
    bool setItem(int row, int col, Item *item);

    void setThrowingItem(int row, int col, Item *item);
    
    void setHero(Hero *hero);
    
    bool getExited();
    void setExited(bool exited);

    bool validate(int row, int col);
    bool isClimbable(int row, int col);
    void setHeroRandomLoc(Unit *hero);

    void moveMons();
    void removeDeadMons();
    
    void moveBosses();
    void removeDeadBosses();
    void bossRush();
    
    void moveCars();
    void moveDragon();

    void processThrowingItems();

    void checkIfNoMoreMons();
    
    bool canExit(int row, int col);
    bool recCanExit(int row, int col, int minSpaceToBeOpened, int count);

    int getNumEmptyCells(int row, int col);
    int recGetNumEmptyCells(int row, int col);
    
    int getLenWalls(int startRow, int startCol, int dir);
    int recGetLenWalls(int curRow, int curCol, int curDir, int startRow, int startCol, int curSteps, int maxSteps, int numRepeatitionsAtStartPos, int maxNumRepeatitionsAtStartPos);
    
    int getRightDir(int dir);
    int getLeftDir(int dir);
    void getForwardPos(int row, int col, int dir, int *nextRow, int *nextCol);
    void getRightPos(int row, int col, int dir, int *nextRow, int *nextCol);
    void getLeftPos(int row, int col, int dir, int *nextRow, int *nextCol);
    void getForwardRightPos(int row, int col, int dir, int *nextRow, int *nextCol);
    void getForwardLeftPos(int row, int col, int dir, int *nextRow, int *nextCol);
    
    virtual void save(ostream &out);
    virtual void load(istream &in);
    
    virtual void loadLevel(istream &in);
    
    void showTitle();
    void showEnding();
};

#endif
