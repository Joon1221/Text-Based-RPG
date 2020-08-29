#include <iostream>
#include <cmath>

using namespace std;

#include "main.h"
#include "unit.h"
#include "hero.h"
#include "mon.h"
#include "prop.h"
#include "tree.h"
#include "tile.h"
#include "boss.h"
#include "item.h"
#include "shockwave.h"
#include "merchant.h"
#include "chest.h"
#include "levels.h"
#include "car.h"
#include "dragon.h"
#include "board.h"
#include "util.h"
#include "event.h"
#include "eventqueue.h"

#include "sim.h"
extern Sim *sim;

//--------------------------------------------------
// Constructors
//--------------------------------------------------

// Default Constructor
Board::Board() {
    board = NULL;
    visited = NULL;
    visitedOrder = NULL;
    
    rowSize = 0;
    colSize = 0;
    
    mons = NULL;
    maxNumMons = 0;
    numMons = 0;
    
    bosses = NULL;
    maxNumBosses = 0;
    numBosses = 0;
    
    merchants = NULL;
    maxNumMerchants = 0;
    numMerchants = 0;
    
    cars = NULL;
    maxNumCars = 0;
    numCars = 0;
    
    dragons = NULL;
    maxNumDragons = 0;
    numDragons = 0;
    
    hero = NULL;
    
    exited = false;
    
    // for shockwave
    shockwaves = NULL;
    maxNumShockwaves = 0;
    numShockwaves = 0;
    
    // for loadLevel()
    title = NULL;
    titleRowSize = 0;
    titleColSize = 0;
    
    ending = NULL;
    endingRowSize = 0;
    endingColSize = 0;
}

// Copy Constructor

// General Constructor

//--------------------------------------------------
// Destructor
//--------------------------------------------------
Board::~Board() {
    destroyAll();
}

void Board::destroyAll() {
    destroyMons();
    destroyBosses();
    destroyMerchants();
    destroyCars();
    destroyDragons();
    destroyFx();
    
    if (board != NULL) {
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                delete board[i][j];
            }
            delete [] board[i];
            delete [] visited[i];
        }
        delete [] board;
        board = NULL;
        
        hero = NULL;
        
        rowSize = 0;
        colSize = 0;
        
        delete [] visited;
        visited = NULL;
    }

    if (title != NULL) {
        for (int i = 0; i < titleRowSize; i++) {
            delete [] title[i];
        }
        delete [] title;
        title = NULL;
        titleRowSize = 0;
        titleColSize = 0;
    }

    if (ending != NULL) {
        for (int i = 0; i < endingRowSize; i++) {
            delete [] ending[i];
        }
        delete [] ending;
        ending = NULL;
        endingRowSize = 0;
        endingColSize = 0;
    }
}

//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
// Member Functions
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
void Board::init() {
    init(MAX_ROW_SIZE, MAX_COL_SIZE, NULL);
}

void Board::init(int rowSize, int colSize, Hero *hero) {
    initBoard(rowSize, colSize, hero);
    
    title = NULL;
    titleRowSize = 0;
    titleColSize = 0;
    
    ending = NULL;
    endingRowSize = 0;
    endingColSize = 0;

    initProps();
    initMons();
    initBosses();
    initMerchants();
    initCars();
    initDragons();
    //initItems();
    initFx();
    exited = false;
}

void Board::loadLevel(int levelID, Hero *hero) {
    if (levelID == CAVE01_LEVEL_ID) {
        initBoard(CAVE01_ROW_SIZE, CAVE01_COL_SIZE, NULL);
        // 위의 initBoard()를 갔다오면, 이제 rowSize와 colSize에는,
        // 제대로 value들이 loading하려는 사이드로 되어 있을테고..
        // 그러니까 여기서는 CAVE01_ROW_SIZE와 CAVE01_COL_SIZE으로
        // 바뀌어 있고, Tile *의 2D array도 만들어져 있다.
        // 이렇게 만들어진 Tile *의 2D array를 모든 access하면서,
        // 위의 CAVE01[][]에 디자인된대로 item이나 prop이나 unit을
        // load하려면 아래처럼 nested for loops를 써야 한다.
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                char currentShape = CAVE01[i][j];
                board[i][j]->setItem(createItemByShape(currentShape));
                board[i][j]->setProp(createPropByShape(currentShape));
                setUnit(i, j, createUnitByShape(currentShape, i, j));
            }
        }
    }
    else if (levelID == CAVE02_LEVEL_ID) {
        initBoard(CAVE02_ROW_SIZE, CAVE02_COL_SIZE, NULL);
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                char currentShape = CAVE02[i][j];
                board[i][j]->setItem(createItemByShape(currentShape));
                board[i][j]->setProp(createPropByShape(currentShape));
                setUnit(i, j, createUnitByShape(currentShape, i, j));
            }
        }
    }
    else if (levelID == CAVE03_LEVEL_ID) {
        initBoard(CAVE03_ROW_SIZE, CAVE03_COL_SIZE, NULL);
        for (int i = 0; i < rowSize; i++) {
            for (int j = 0; j < colSize; j++) {
                char currentShape = CAVE03[i][j];
                board[i][j]->setItem(createItemByShape(currentShape));
                board[i][j]->setProp(createPropByShape(currentShape));
                setUnit(i, j, createUnitByShape(currentShape, i, j));
            }
        }
    }
    
    // 아래에서, 몬스터들과 보스들을 array에 셋해주어야 한다.
    // 일단 마리수를 count해서, 그만큼 어레이를 만든 다음, 모든 주소를 셋해야 한다
    // 주의할 점은, 몬스터보다 보스인지 먼저 count해야 한다.
    maxNumMons = 0;
    maxNumBosses = 0;
    maxNumMerchants = 0;
    maxNumCars = 0;
    maxNumDragons = 0;
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (board[i][j]->getUnit() != NULL) {
                if (board[i][j]->getUnit()->isBoss()) {
                    maxNumBosses++;
                }
                else if (board[i][j]->getUnit()->isMon()) {
                    maxNumMons++;
                }
                else if (board[i][j]->getUnit()->isMerchant()) {
                    maxNumMerchants++;
                }
                else if (board[i][j]->getUnit()->isCar()) {
                    maxNumCars++;
                }
                else if (board[i][j]->getUnit()->isDragon()) {
                    maxNumDragons++;
                }
            }
        }
    }

    //cout << "maxNumMons: " << maxNumMons << endl;

    // create random monsters
    mons = new Mon *[maxNumMons];
    numMons = 0;
    bosses = new Boss *[maxNumBosses];
    numBosses = 0;
    merchants = new Merchant *[maxNumMerchants];
    numMerchants = 0;
    cars = new Car *[maxNumCars];
    numCars = 0;
    dragons = new Dragon *[maxNumDragons];
    numDragons = 0;
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (board[i][j]->getUnit() != NULL) {
                if (board[i][j]->getUnit()->isBoss()) {
                    bosses[numBosses] = (Boss *)board[i][j]->getUnit();
                    numBosses++;
                }
                else if (board[i][j]->getUnit()->isMon()) {
                    mons[numMons] = (Mon *)board[i][j]->getUnit();
                    numMons++;
                }
                else if (board[i][j]->getUnit()->isMerchant()) {
                    merchants[numMerchants] = (Merchant *)board[i][j]->getUnit();
                    numMerchants++;
                }
                else if (board[i][j]->getUnit()->isCar()) {
                    cars[numCars] = (Car *)board[i][j]->getUnit();
                    numCars++;
                }
                else if (board[i][j]->getUnit()->isDragon()) {
                    dragons[numDragons] = (Dragon *)board[i][j]->getUnit();
                    numDragons++;
                }
            }
        }
    }
    
    hero->setRow(HERO_ENTRANCE_ROW);
    hero->setCol(HERO_ENTRANCE_COL);
    setUnit(hero->getRow(), hero->getCol(), hero);
    this->hero = hero;
    
    exited = false;
    initFx();
}


void Board::initBoard(int rowSize, int colSize, Hero *hero) {
    this->rowSize = rowSize;
    this->colSize = colSize;
    board = new Tile **[rowSize];
    visited = new bool *[rowSize];
    visitedOrder = new int *[rowSize];
    
    for (int i = 0; i < rowSize; i++) {
        board[i] = new Tile *[colSize];
        visited[i] = new bool [colSize];
        visitedOrder[i] = new int [colSize];

        for (int j = 0; j < colSize; j++) {
            board[i][j] = new Tile();
            board[i][j]->row = i; // for A*
            board[i][j]->col = j; // for A*
            visited[i][j] = false;
            visitedOrder[i][j] = -1;
        }
    }
    
    if (hero != NULL) {
        this->hero = hero;
        setUnit(hero->getRow(), hero->getCol(), hero);
    }
    else {
        this->hero = NULL;
    }
}

void Board::resetVisited() {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            visited[i][j] = false;
        }
    }
}

void Board::initProps() {
    initTrees();
    initChest();
}

void Board::initTrees() {
    for (int i = 0; i < MAX_NUM_TREES; i++) {
        Tree *currentTree = new Tree();
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (validate(randRow, randCol) && setProp(randRow, randCol, currentTree)) {
                break;
            }
        }
    }
}

void Board::initChest() {
    for (int i = 0; i < MAX_NUM_CHESTS; i++) {
        Chest *currentChest = getRandomChest();
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (validate(randRow, randCol) &&
                board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getItem() == NULL) {
                int countEmptyTilesAround = 0;
                
                for (int i = randRow-1; i <= randRow+1; i++) {
                    for (int j = randCol-1; j <= randCol+1; j++) {
                        if (validate(i, j) &&
                            board[i][j]->getProp() == NULL &&
                            board[i][j]->getItem() == NULL) {
                            countEmptyTilesAround++;
                        }
                    }
                }
                
                if (countEmptyTilesAround >= (currentChest->getLockLevel() + 2)) {
                    setProp(randRow, randCol, currentChest);
                    break;
                }
            }            
        }
    }
}

void Board::initMons() {
    maxNumMons = MAX_NUM_MONS;
    numMons = 0;
    mons = new Mon *[maxNumMons];
    for (int i = 0; i < maxNumMons; i++) {
        mons[i] = new Mon();
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (isClimbable(randRow, randCol) && setUnit(randRow, randCol, mons[i])) {
                break;
            }
        }
        numMons++;
    }
}

void Board::destroyMons() {
    if (mons != NULL) {
        delete [] mons;
        mons = NULL;
        
        maxNumMons = 0;
        numMons = 0;
    }
}

void Board::initBosses() {
    maxNumBosses = MAX_NUM_BOSS_MONS;
    numBosses = 0;
    bosses = new Boss *[maxNumBosses];
    for (int i = 0; i < maxNumBosses; i++) {
        bosses[i] = new Boss();
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (isClimbable(randRow, randCol) && setUnit(randRow, randCol, bosses[i])) {
                break;
            }
        }
        numBosses++;
    }
}

void Board::destroyBosses() {
    if (bosses != NULL) {
        delete [] bosses;
        bosses = NULL;
        
        maxNumBosses = 0;
        numBosses = 0;
    }
}

void Board::initMerchants() {
    maxNumMerchants = MAX_NUM_MERCHANTS;
    numMerchants = 0;
    merchants = new Merchant * [maxNumMerchants];
    
    for (int i = 0; i < maxNumMerchants; i++) {
        merchants[i] = new Merchant();
        
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getItem() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                setUnit(randRow, randCol, merchants[i]);
                break;
            }
        }
        
        numMerchants++;
    }
}

void Board::destroyMerchants() {
    if (merchants != NULL) {
        delete [] merchants;
        merchants = NULL;
        
        maxNumMerchants = 0;
        numMerchants = 0;
    }
}

void Board::initCars() {
    maxNumCars = MAX_NUM_CARS;
    numCars = 0;
    cars = new Car *[maxNumCars];
    for (int i = 0; i < maxNumCars; i++) {
        cars[i] = new Car();
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (isClimbable(randRow, randCol) && setUnit(randRow, randCol, cars[i])) {
                break;
            }
        }
        numCars++;
    }
}

void Board::destroyCars() {
    if (cars != NULL) {
        delete [] cars;
        cars = NULL;
        
        maxNumCars = 0;
        numCars = 0;
    }
}

void Board::initDragons() {
    maxNumDragons = MAX_NUM_DRAGONS;
    numDragons = 0;
    dragons = new Dragon *[maxNumDragons];
    for (int i = 0; i < maxNumDragons; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            if (isClimbable(randRow, randCol)) {
                dragons[i] = createDragon(randRow, randCol, DRAGON_LEN);
                setUnit(randRow, randCol, dragons[i]);
                break;
            }
        }
        numDragons++;
    }
}

void Board::destroyDragons() {
    if (dragons != NULL) {
        delete [] dragons;
        dragons = NULL;
        
        maxNumDragons = 0;
        numDragons = 0;
    }
}

void Board::initItems() {
    // init potions
    for (int i = 0; i < MAX_NUM_POTIONS; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (isClimbable(randRow, randCol) && board[randRow][randCol]->getItem() == NULL) {
                board[randRow][randCol]->setItem(new Potion());
                break;
            }
        }
    }

    // init keys
    for (int i = 0; i < MAX_NUM_KEYS; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (isClimbable(randRow, randCol) && board[randRow][randCol]->getItem() == NULL) {
                board[randRow][randCol]->setItem(getRandomKey());
                break;
            }
        }
    }
    
    // init random armor
    for (int i = 0; i < MAX_NUM_ARMORS; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (isClimbable(randRow, randCol) && board[randRow][randCol]->getItem() == NULL) {
                board[randRow][randCol]->setItem(getRandomArmor());
                break;
            }
        }
    }

    // init random weapon
    for (int i = 0; i < MAX_NUM_WEAPONS; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (isClimbable(randRow, randCol) && board[randRow][randCol]->getItem() == NULL) {
                board[randRow][randCol]->setItem(getRandomWeapon());
                break;
            }
        }
    }
    
    // install random bombs
    for (int i = 0; i < MAX_NUM_BOMBS; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getUnit() == NULL &&
                board[randRow][randCol]->getItem() == NULL) {
                Bomb *bomb = new Bomb();
                board[randRow][randCol]->setItem(bomb);
                break;
            }
        }
    }
}

void Board::initFx() {
    maxNumShockwaves = MAX_NUM_SHOCKWAVES;
    shockwaves = new Shockwave *[maxNumShockwaves];
    numShockwaves = 0;
    
    for (int i = 0; i < maxNumShockwaves; i++) {
        shockwaves[i] = NULL;
    }
}

void Board::destroyFx() {
    if (shockwaves != NULL) {
        for (int i = 0; i < maxNumShockwaves; i++) {
            if (shockwaves[i] != NULL) {
                delete shockwaves[i];
            }
        }
        
        delete [] shockwaves;
        shockwaves = NULL;
        
        maxNumShockwaves = 0;
        numShockwaves = 0;
    }
}

//--------------------------------------------------
// General Member Functions
//--------------------------------------------------
void Board::print(int firstGap, int row, int col, int viewportRangeRow, int viewportRangeCol) {
    // process all shockwaves --------------------------------------------------
    for (int i = 0; i < maxNumShockwaves; i++) {
        if (shockwaves[i] != NULL) {
            if (!shockwaves[i]->getWaveActivated()) {
                delete shockwaves[i];
                shockwaves[i] = NULL;
                numShockwaves--;
            }
            else {
                shockwaves[i]->print();
            }
        }
    }
    // process all shockwaves end ----------------------------------------------

    if (hero->getHeroFacingDirection() == MOVE_DIR_NORTH) {
        // print first gap
        for (int z = 0; z < firstGap; z++) {
            cout << " ";
        }
        
        // print a horizontal line
        cout << " ";
        for (int j = col-viewportRangeCol; j < col+viewportRangeCol; j++) {
            if (j >= 0-viewportRangeCol && j < colSize+viewportRangeCol) {
                cout << "^";
            }
        }
        cout << " " << endl;
    }
    else {
        cout << endl;
    }
    
    // print first gap
    for (int z = 0; z < firstGap; z++) {
        cout << " ";
    }

    // print a horizontal line
    cout << "+";
    for (int j = col-viewportRangeCol; j < col+viewportRangeCol; j++) {
        if (j >= 0-viewportRangeCol && j < colSize+viewportRangeCol) {
            cout << "-";
        }
    }
    cout << "+" << endl;
    
    // print a board using nested for loops
    for (int i = row-viewportRangeRow; i < row+viewportRangeRow; i++) {
        // print first gap
        for (int z = 0; z < firstGap; z++) {
            if (!(z == firstGap-1 && hero->getHeroFacingDirection() == MOVE_DIR_WEST)) {
                cout << " ";
            }
        }

        if (i >= 0-viewportRangeRow && i < rowSize+viewportRangeRow) {
            if (hero->getHeroFacingDirection() == MOVE_DIR_WEST) {
                cout << "<";
            }
            cout << "|";
        }
        for (int j = col-viewportRangeCol; j < col+viewportRangeCol; j++) {
            if (i >= 0 && i < rowSize && j >= 0 && j < colSize) {
                double distRow = fabs(i - hero->getRow());
                double distCol = fabs(j - hero->getCol());
                double dist = sqrt(distRow*distRow + distCol*distCol);
                if (sim->day == DAY || dist <= hero->getNightRange()) {
                    board[i][j]->print();
                }
                else {
                    cout << TILE_NIGHT;
                }
            }
            else {
                cout << TILE_WALL;
            }
        }
        if (i >= 0-viewportRangeRow && i < rowSize+viewportRangeRow) {
            cout << "|";
            if (hero->getHeroFacingDirection() == MOVE_DIR_EAST) {
                cout << ">";
            }
            cout << endl;
        }
        
    }
    
    // print a horizontal line.
    // print first gap
    for (int z = 0; z < firstGap; z++) {
        cout << " ";
    }

    cout << "+";
    for (int j = col-viewportRangeCol; j < col+viewportRangeCol; j++) {
        if (j >= 0-viewportRangeCol && j < colSize+viewportRangeCol) {
            cout << "-";
        }
    }
    cout << "+" << endl;
    
    if (hero->getHeroFacingDirection() == MOVE_DIR_SOUTH) {
        // print first gap
        for (int z = 0; z < firstGap; z++) {
            cout << " ";
        }
        
        // print a horizontal line
        cout << " ";
        for (int j = col-viewportRangeCol; j < col+viewportRangeCol; j++) {
            if (j >= 0-viewportRangeCol && j < colSize+viewportRangeCol) {
                cout << "v";
            }
        }
        cout << " " << endl;
    }
    else {
        cout << endl;
    }
}

void Board::clearFx(int row, int col) {
    board[row][col]->clearFx();
}

void Board::setFx(int row, int col, char fx) {
    board[row][col]->setFx(fx);
}

void Board::startWave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                      int row, int col, int range, int frameInterval, char fxShape, int skillNumber) {
    if (numShockwaves >= maxNumShockwaves) {
        cout << "error: can't start new shockwave!";
        return;
    }

    for (int i = 0; i < maxNumShockwaves; i++) {
        if (shockwaves[i] == NULL) {
            shockwaves[i] = new Shockwave(waveUnit, waveItem, waveProp,
                                          row, col, range, frameInterval, fxShape);
            shockwaves[i]->start();
            shockwaves[i]->setSkillNumber(skillNumber);
            numShockwaves++;
            break;
        }
    }
}

int Board::getRowSize() {
    return rowSize;
}

int Board::getColSize() {
    return colSize;
}

Hero *Board::getHero() {
    return hero;
}

Tile *Board::getTile(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    return board[row][col];
}

Unit *Board::getUnit(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    return board[row][col]->getUnit();
}

bool Board::setUnit(int row, int col, Unit *unit) {
    if (!validate(row, col)) {
        return false;
    }
    
    board[row][col]->setUnit(unit);
    
    if (unit != NULL) {
        unit->setRow(row);
        unit->setCol(col);
    }

    return true;
}

void Board::removeUnit(int row, int col) {
    if (validate(row, col)) {
        board[row][col]->setUnit(NULL);
    }
}

Prop *Board::getProp(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    
    return board[row][col]->getProp();
}

bool Board::setProp(int row, int col, Prop *prop) {
    if (!validate(row, col)) {
        return false;
    }
    
    board[row][col]->setProp(prop);
    return true;
}

Item *Board::getItem(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    
    return board[row][col]->getItem();
}

bool Board::setItem(int row, int col, Item *item) {
    if (!validate(row, col)) {
        return false;
    }
    board[row][col]->setItem(item);
    
    if (item != NULL) {
        item->setRow(row);
        item->setCol(col);
    }
    return true;
}

void Board::setThrowingItem(int row, int col, Item *item) {
    if (!validate(row, col)) {
        return;
    }
    
    board[row][col]->setThrowingItem(item);
}

void Board::setHero(Hero *hero) {
    this->hero = hero;
}

bool Board::getExited() {
    return exited;
}

void Board::setExited(bool exited) {
    this->exited = exited;
}

bool Board::validate(int row, int col) {
    return row >= 0 && row < rowSize && col >= 0 && col < colSize;
}

bool Board::isClimbable(int row, int col) {
    if (!validate(row, col)) {
        return false;
    }
    return board[row][col]->isClimbable();
}

void Board::setHeroRandomLoc(Unit *hero) {
    while (true) {
        int randRow = rand() % rowSize;
        int randCol = rand() % colSize;
        
        if (validate(randRow, randCol) && setUnit(randRow, randCol, hero)) {
            break;
        }
    }
}

//--------------------------------------------------
// Special Member Functions
//--------------------------------------------------
void Board::moveMons() {
    //cout << "Board::moveMons()" << endl;
    for (int i = 0; i < numMons; i++) {
        if (!mons[i]->isDead()) {
            int randDir = rand() % NUM_HERO_MOVE_DIR;
            mons[i]->move(randDir);
        }
    }
}

void Board::removeDeadMons() {
    for (int i = 0; i < numMons; i++) {
        if (mons[i]->isDead() && mons[i]->getRow() != -1) {
            int randomInterval = rand() % (MON_RESPAWN_EVENT_INTERVAL_MAX - MON_RESPAWN_EVENT_INTERVAL_MIN + 1) + MON_RESPAWN_EVENT_INTERVAL_MIN;
            sim->eq->enqueue(new MonRespawnEvent(sim->time+randomInterval, mons[i]));
            setUnit(mons[i]->getRow(), mons[i]->getCol(), NULL);
            mons[i]->setRow(-1);
            mons[i]->setCol(-1);

//            Mon *curMon = mons[i];
//            for (int j = i; j < numMons-1; j++) {
//                mons[j] = mons[j+1];
//            }
//            
//            removeUnit(curMon->getRow(), curMon->getCol());
//            delete curMon;
//            numMons--;
        }
    }
}

void Board::moveBosses() {
    //cout << "Board::moveBosses()" << endl;
    for (int i = 0; i < numBosses; i++) {
        if (!bosses[i]->isDead()) {
            int randDir = rand() % NUM_HERO_MOVE_DIR;
            bosses[i]->move(randDir);
        }
    }
}

void Board::bossRush() {
    int maxDist = sqrt(MAX_ROW_SIZE * MAX_ROW_SIZE + MAX_COL_SIZE * MAX_COL_SIZE);
    for (int i = 0; i < numBosses; i++) {
        bosses[i]->setRange(maxDist);
    }
}

void Board::moveCars() {
    for (int i = 0; i < numCars; i++) {
        if (!cars[i]->getIdle()) {
            cars[i]->move(MOVE_DIR_NONE);
        }
    }
}

void Board::moveDragon() {
    for (int i = 0; i < numDragons; i++) {
        if (!dragons[i]->isDead()) {
            int randDir = rand() % NUM_HERO_MOVE_DIR;
            dragons[i]->move(randDir);
        }
    }
}

void Board::processThrowingItems() {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            board[i][j]->processThrowingItems(i, j);
        }
    }
}

void Board::removeDeadBosses() {
    for (int i = 0; i < numBosses; i++) {
        if (bosses[i]->isDead()) {
            Boss *curMon = bosses[i];
            for (int j = i; j < numBosses-1; j++) {
                bosses[j] = bosses[j+1];
            }
            
            removeUnit(curMon->getRow(), curMon->getCol());
            delete curMon;
            numBosses--;
        }
    }
}

void Board::checkIfNoMoreMons() {
//    if (numMons == 0) {
//        delete [] mons;
//        initMons();
//    }
//    
//    if (numBosses == 0) {
//        delete [] bosses;
//        initBosses();
//    }
}

#define MIN_SPACE_TO_BE_OPENED 12 //(DRAGON_LEN*10)
// ***** Dragon등이 어떤 쪽으로 움직이는 것을 결정할 때, exit있는지 없는지 알아보기 위해..
bool Board::canExit(int row, int col) {
    resetVisited();
    if (isClimbable(row, col)) {
        visited[row][col] = true;
        return recCanExit(row, col, MIN_SPACE_TO_BE_OPENED, 1);
    }
    else {
        return false;
    }
}

// 얘가 진짜 recursive function이다. 즉, 모든 일은 얘가 하고, 위의 noExit()은 그냥 준비해주고
// 시작시켜조는 역할이다.
// pre-condition: isClimbable(row, col) == true
bool Board::recCanExit(int row, int col, int minSpaceToBeOpened, int count) {
    int northOpened = false;
    int eastOpened = false;
    int southOpened = false;
    int westOpened = false;
    if (isClimbable(row-1, col) && !visited[row-1][col]) { // check north
        visited[row-1][col] = true;
        northOpened = true;
        count++;
    }
    if (isClimbable(row, col+1) && !visited[row][col+1]) { // check east
        visited[row][col+1] = true;
        eastOpened = true;
        count++;
    }
    if (isClimbable(row+1, col) && !visited[row+1][col]) { // check south
        visited[row+1][col] = true;
        southOpened = true;
        count++;
    }
    if (isClimbable(row, col-1) && !visited[row][col-1]) { // check west
        visited[row][col-1] = true;
        westOpened = true;
        count++;
    }
    
    // base case = code to terminate
    if (count >= minSpaceToBeOpened) {
        return true;
    }
    
    if (northOpened) { // check north
        if (recCanExit(row-1, col, minSpaceToBeOpened, count)) {
            return true;
        }
    }
    
    if (eastOpened) { // check east
        if (recCanExit(row, col+1, minSpaceToBeOpened, count)) {
            return true;
        }
    }

    if (southOpened) { // check south
        if (recCanExit(row+1, col, minSpaceToBeOpened, count)) {
            return true;
        }
    }
    
    if (westOpened) { // check west
        if (recCanExit(row, col-1, minSpaceToBeOpened, count)) {
            return true;
        }
    }
    
    return false;
}

// 아래는 위의 canExit()과 조금 다른 앨거리듬으로, 그냥 빈 공간들의 갯수를 count한다.
int Board::getNumEmptyCells(int row, int col) {
    resetVisited();
    return recGetNumEmptyCells(row, col);
}

int Board::recGetNumEmptyCells(int row, int col) {
    if (!isClimbable(row, col) || visited[row][col]) {
        return 0;
    }
    
    visited[row][col] = true;
    return 1
        + recGetNumEmptyCells(row+1, col)
        + recGetNumEmptyCells(row, col+1)
        + recGetNumEmptyCells(row-1, col)
        + recGetNumEmptyCells(row, col-1);
}

//==============================================================================
// 드래곤 쪽에서 getLenWalls()이 call되기 위한 조건.
//==============================================================================
// 드래곤이 진행하다가 F앞/L좌/R우 들을 체크해서 특정 상황일 때만, 앨거리듬을 가동한다.
//
// LD  F  RD
// L   V  R
//     r
//
// 위의 상황에서..
// 1) L과 R과 F가 open이고, 동시에(AND) LD/RD가 동시에 막혀있으면, call해야 한다.
//    L과 F와 R 각 지점에 대해 아래의 앨거리듬이 call되어야 한다.
// 2) L과 R이 open이고, 동시에(AND) LD/F/RD 셋중에 한개라도 막혀있으면, call해야 한다.
//    L과 R 각 지점에 대해 아래의 앨거리듬이 call되어야 한다.
// 3) L과 R둘중에 딱 한개만 open일 경우..
//    3a) 만약 L만 open일 경우, F는 반드시 open이면서, LD가 block일 경우..
//        L과 F 각 지점에 대해 아래의 앨거리듬이 call되어야 한다.
//    3b) 만약 R만 open일 경우, F는 반드시 open이면서, RD가 block일 경우..
//        R과 F 각 지점에 대해 아래의 앨거리듬이 call되어야 한다.
// 위의 (1)이나 (2)나 (3a)나 (3b)의 경우만, 아래의 앨거리듬이 각각 open된 장소에서부터 call되어야 한다.
//==============================================================================

#define MAX_STEPS_FOLLOW_RIGHT_WALLS 100

int Board::getLenWalls(int startRow, int startCol, int dir) {
#ifdef DEBUG_DRAGON_MOVE
    cout << "dir : " << dir << " (startRow, startCol) : (" << startRow << ", " << startCol << ")" << endl;
#endif
    if (!validate(startRow, startCol)) {
        return false;
    }
    resetVisited();
    visited[startRow][startCol] = true;
    
    int maxNumRepeatitionsAtStartPos = 0;
    if (validate(startRow-1, startCol) &&
        (getUnit(startRow-1, startCol) == NULL || !getUnit(startRow-1, startCol)->isDragon()) &&
        (getProp(startRow-1, startCol) == NULL || getProp(startRow-1, startCol)->isClimbable())) { // check north
        maxNumRepeatitionsAtStartPos++;
    }
    if (validate(startRow, startCol+1) &&
        (getUnit(startRow, startCol+1) == NULL || !getUnit(startRow, startCol+1)->isDragon()) &&
        (getProp(startRow, startCol+1) == NULL || getProp(startRow, startCol+1)->isClimbable())) { // check east
        maxNumRepeatitionsAtStartPos++;
    }
    if (validate(startRow+1, startCol) &&
        (getUnit(startRow+1, startCol) == NULL || !getUnit(startRow+1, startCol)->isDragon()) &&
        (getProp(startRow+1, startCol) == NULL || getProp(startRow+1, startCol)->isClimbable())) { // check south
        maxNumRepeatitionsAtStartPos++;
    }
    if (validate(startRow, startCol-1) &&
        (getUnit(startRow, startCol-1) == NULL || !getUnit(startRow, startCol-1)->isDragon()) &&
        (getProp(startRow, startCol-1) == NULL || getProp(startRow, startCol-1)->isClimbable())) { // check west
        maxNumRepeatitionsAtStartPos++;
    }
    
    return recGetLenWalls(startRow, startCol, dir, startRow, startCol, 1, MAX_STEPS_FOLLOW_RIGHT_WALLS, 0, maxNumRepeatitionsAtStartPos);
}

// pre-condition: validate(startRow, startCol) == true
int Board::recGetLenWalls(int curRow, int curCol, int curDir, int startRow, int startCol, int curSteps, int maxSteps, int numRepeatitionsAtStartPos, int maxNumRepeatitionsAtStartPos) {
// 현재 지점으로부터(curRow, curCol) 진행방향의(curDir) 오른쪽을 체크한다.
    // 막혔으면..
    //     현재 진행방향(curDir)으로 진행하기 위해 진행 방향쪽(curDir) cell을 비어있는지 체크한다.
    //     막혔으면..
    //         왼쪽으로 turn한다.(curRow, curCol은 바꾸지 않고, curDir만 왼쪽으로 바꾼 후)
    //         recursive call.
    //         이때 curSteps는 증가시키지 않음.(움직이지 않았으므로)
    //     안 막혔으면..
    //         그 지점이 visited이고, (startRow, startCol)과 같을 때..
    //             curSteps를 return한다.(즉 끝이다)
    //         그 지점이 visited이고, (startRow, startCol)이 아닐 때..
    //             진행할 지점에 visited mark를 할 필요없고..
    //             진행한다.(recursive call을 하면서 바뀐 curRow, curCol을 pass한다.)
    //             이때 curSteps는 1을 뺀다.(그렇게 하기로 했다. 온 자리 다시 지나갈 경우..)
    //         아니면..
    //             진행할 지점에 visited mark를 한다.
    //             진행한다.(recursive call을 하면서 바뀐 curRow, curCol을 pass한다.)
    //             이때 curSteps는 1 증가시킴.
    // 안 막혔으면..
    //     오른쪽으로 turn한다.(curRow, curCol은 바꾸지 않고, curDir만 오른쪽으로 바꾼 후).
    //     recursive call.
    //     이때 curSteps는 증가시키지 않음.(움직이지 않았으므로)
#ifdef DEBUG_DRAGON_MOVE
    cout << "curDir : " << curDir << " (row, col) : (" << curRow << ", " << curCol << ") curSteps=" << curSteps << endl;
#endif
    int nextRow = -1;
    int nextCol = -1;
    
    int nextRowRight = -1;
    int nextColRight = -1;
    
    getForwardPos(curRow, curCol, curDir, &nextRow, &nextCol);
    getRightPos(curRow, curCol, curDir, &nextRowRight, &nextColRight);

    Unit *frontUnit = NULL;
    if (validate(nextRow, nextCol)) {
        if (getUnit(nextRow, nextCol) != NULL &&
            getUnit(nextRow, nextCol)->isDragon()) {
            frontUnit = getUnit(nextRow, nextCol);
        }
    }
    
    Unit *rightUnit = NULL;
    if (validate(nextRowRight, nextColRight)) {
        if (getUnit(nextRowRight, nextColRight) != NULL &&
            getUnit(nextRowRight, nextColRight)->isDragon()) {
            rightUnit = getUnit(nextRowRight, nextColRight);
        }
    }

    Prop *frontProp = NULL;
    if (validate(nextRow, nextCol)) {
        frontProp = getProp(nextRow, nextCol);
    }

    Prop *rightProp = NULL;
    if (validate(nextRowRight, nextColRight)) {
        rightProp = getProp(nextRowRight, nextColRight);
    }

//    cout << "nextRow : " << nextRow << endl;
//    cout << "nextCol : " << nextCol << endl;
//
//    cout << "nextRowRight : " << nextRowRight << endl;
//    cout << "nextColRight : " << nextColRight << endl;

    // 현재 지점으로부터(curRow, curCol) 진행방향의(curDir) 오른쪽을 체크한다.
    // 막혔으면..
    if (!validate(nextRowRight, nextColRight) ||
        rightUnit != NULL ||
        (rightProp != NULL && !rightProp->isClimbable())) {
        //     현재 진행방향(curDir)으로 진행하기 위해 진행 방향쪽(curDir) cell을 비어있는지 체크한다.
        //     막혔으면..
        if (!validate(nextRow, nextCol) || frontUnit != NULL || (frontProp != NULL && !frontProp->isClimbable())) {
            //         왼쪽으로 turn한다.(curRow, curCol은 바꾸지 않고, curDir만 왼쪽으로 바꾼 후)
            //         recursive call.
            //         이때 curSteps는 증가시키지 않음.(움직이지 않았으므로)
#ifdef DEBUG_DRAGON_MOVE
            cout << "hi1" << endl;
#endif
            if (curRow == startRow && curCol == startCol) {
                numRepeatitionsAtStartPos++;
                if (numRepeatitionsAtStartPos >= 4) {
                    return curSteps;
                }
            }
            return recGetLenWalls(curRow, curCol, getLeftDir(curDir), startRow, startCol, curSteps, maxSteps, numRepeatitionsAtStartPos, maxNumRepeatitionsAtStartPos);
        }
        //     안 막혔으면..
        //             이때 curSteps는 1을 뺀다.(그렇게 하기로 했다. 온 자리 다시 지나갈 경우..)
        else {
            //         그 지점이 visited이고, (startRow, startCol)과 같을 때..
            //             curSteps를 return한다.(즉 끝이다)
            if (visited[nextRow][nextCol] && (nextRow == startRow && nextCol == startCol)) {
            //if (nextRow == startRow && nextCol == startCol) {
#ifdef DEBUG_DRAGON_MOVE
                cout << "hi2: return curSteps=" << curSteps << endl;
#endif
                return curSteps;
            }
            //         (앞이 열려있고, visited일때..)
            //         그 지점이 visited이고, (startRow, startCol)이 아닐 때..
            //             진행할 지점에 visited mark를 할 필요없고..
            //             진행한다.(recursive call을 하면서 바뀐 curRow, curCol을 pass한다.)
            else if (visited[nextRow][nextCol] && !(nextRow == startRow && nextCol == startCol)) {
                curSteps -= 1;
#ifdef DEBUG_DRAGON_MOVE
                cout << "hi3" << endl;
#endif
                return recGetLenWalls(nextRow, nextCol, curDir, startRow, startCol, curSteps, maxSteps, numRepeatitionsAtStartPos, maxNumRepeatitionsAtStartPos);
            }
            //         아니면..(앞이 열려있고, visited가 아닐때..)
            //             진행할 지점에 visited mark를 한다.
            //             진행한다.(recursive call을 하면서 바뀐 curRow, curCol을 pass한다.)
            //             이때 curSteps는 1 증가시킴.
            else {
                if (visited[nextRow][nextCol]) {
                    curSteps += 1;
                }
                else {
                    curSteps += 1;
                }
                visited[nextRow][nextCol] = true;
#ifdef DEBUG_DRAGON_MOVE
                cout << "hi4" << endl;
#endif
                return recGetLenWalls(nextRow, nextCol, curDir, startRow, startCol, curSteps, maxSteps, numRepeatitionsAtStartPos, maxNumRepeatitionsAtStartPos);
            }
        }
    }
    else {
#ifdef DEBUG_DRAGON_MOVE
        cout << "hi5" << endl;
#endif
        // 오른쪽으로 turn한다.(curRow, curCol은 바꾸지 않고, curDir만 오른쪽으로 바꾼 후)
        int nextRow = -1;
        int nextCol = -1;
        int nextForwardDir = getRightDir(curDir);
        getForwardPos(curRow, curCol, nextForwardDir, &nextRow, &nextCol);
        
        if (visited[nextRow][nextCol] && (nextRow == startRow && nextCol == startCol)) {
            //if (nextRow == startRow && nextCol == startCol) {
#ifdef DEBUG_DRAGON_MOVE
            cout << "hi6: return curSteps=" << curSteps << endl;
#endif
            return curSteps;
        }

        if (visited[nextRow][nextCol]) {
#ifdef DEBUG_DRAGON_MOVE
            cout << "hi7" << endl;
#endif
            curSteps -= 1;
        }
        else {
#ifdef DEBUG_DRAGON_MOVE
            cout << "hi8" << endl;
#endif
            curSteps += 1;
            visited[nextRow][nextCol] = true;
        }
        return recGetLenWalls(nextRow, nextCol, nextForwardDir, startRow, startCol, curSteps, maxSteps, numRepeatitionsAtStartPos, maxNumRepeatitionsAtStartPos);
    }
}

int Board::getRightDir(int dir) {
    if (dir == MOVE_DIR_WEST) {
        return MOVE_DIR_NORTH;
    }
    else if (dir == MOVE_DIR_NORTH || dir == MOVE_DIR_EAST || dir == MOVE_DIR_SOUTH) {
        return dir+1;
    }
    return -1;
}

int Board::getLeftDir(int dir) {
    if (dir == MOVE_DIR_NORTH) {
        return MOVE_DIR_WEST;
    }
    else if (dir == MOVE_DIR_WEST || dir == MOVE_DIR_EAST || dir == MOVE_DIR_SOUTH) {
        return dir-1;
    }
    return -1;
}

// 아래처럼 return할 value가 두개 이상일 경우는(2 or more), *를 붙여서 pointer variable에..
// result를 return할 variable들의 address(= pointer = reference)를 가져와서, remotely
// 넣어준다.
void Board::getForwardPos(int row, int col, int dir, int *nextRow, int *nextCol) {
    int rowDir = (dir == MOVE_DIR_NORTH)? -1: ((dir == MOVE_DIR_SOUTH)? 1: 0);
    int colDir = (dir == MOVE_DIR_WEST)? -1: ((dir == MOVE_DIR_EAST)? 1: 0);
    
    *nextRow = row+rowDir;
    *nextCol = col+colDir;
}

void Board::getRightPos(int row, int col, int dir, int *nextRow, int *nextCol) {
    getForwardPos(row, col, getRightDir(dir), nextRow, nextCol);
}

void Board::getLeftPos(int row, int col, int dir, int *nextRow, int *nextCol) {
    getForwardPos(row, col, getLeftDir(dir), nextRow, nextCol);
}

void Board::getForwardRightPos(int row, int col, int dir, int *nextRow, int *nextCol) {
    int forwardPosRow = -1;
    int forwardPosCol = -1;
    getForwardPos(row, col, dir, &forwardPosRow, &forwardPosCol);
    getRightPos(forwardPosRow, forwardPosCol, dir, nextRow, nextCol);
}

void Board::getForwardLeftPos(int row, int col, int dir, int *nextRow, int *nextCol) {
    int forwardPosRow = -1;
    int forwardPosCol = -1;
    getForwardPos(row, col, dir, &forwardPosRow, &forwardPosCol);
    getLeftPos(forwardPosRow, forwardPosCol, dir, nextRow, nextCol);
}

void Board::save(ostream &out) {
    out << "#---------------------------------------- class Board" << endl;
    
    //--------------------------------------------------------------------------
    // Save board[][]
    //--------------------------------------------------------------------------
    out << "#---------------------------------------- board[][]" << endl;
    
    out << "# rowSize" << endl;
    out << rowSize << endl;
    
    out << "# colSize" << endl;
    out << colSize << endl;

    out << "#---------------------------------------- board[][] started" << endl;
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            out << "#---------------------------------------- board[" << i << "][" << j << "]" << endl;
            board[i][j]->save(out);
        }
    }
    out << "#---------------------------------------- board[][] end" << endl;
    
    //--------------------------------------------------------------------------
    // Save mons[]
    //--------------------------------------------------------------------------
    out << "#---------------------------------------- mons" << endl;
    
    out << "# maxNumMons" << endl;
    out << maxNumMons << endl;
    
    out << "# numMons" << endl;
    out << numMons << endl;
    
    out << "#---------------------------------------- mons[] started" << endl;
    for (int i = 0; i < maxNumMons; i++) {
        if (mons[i] == NULL) {
            out << "#---------------------------------------- mons[" << i << "]" << endl;
            out << TOMB_STONE_EMPTY << endl;
        }
        else {
            out << "#---------------------------------------- mons[" << i << "]" << endl;
            out << TOMB_STONE_NON_EMPTY << endl;
            mons[i]->save(out);
        }
    }
    out << "#---------------------------------------- mons[] end" << endl;
    
    //--------------------------------------------------------------------------
    // Save bosses[]
    //--------------------------------------------------------------------------
    out << "#---------------------------------------- bosses" << endl;
    
    out << "# maxNumBosses" << endl;
    out << maxNumBosses << endl;
    
    out << "# numBosses" << endl;
    out << numBosses << endl;
    
    out << "#---------------------------------------- bosses[] started" << endl;
    for (int i = 0; i < maxNumBosses; i++) {
        if (bosses[i] == NULL) {
            out << "#---------------------------------------- bosses[" << i << "]" << endl;
            out << TOMB_STONE_EMPTY << endl;
        }
        else {
            out << "#---------------------------------------- bosses[" << i << "]" << endl;
            out << TOMB_STONE_NON_EMPTY << endl;
            bosses[i]->save(out);
        }
    }
    out << "#---------------------------------------- bosses[] end" << endl;
    
    //--------------------------------------------------------------------------
    // Save merchants[]
    //--------------------------------------------------------------------------
    out << "#---------------------------------------- merchants" << endl;
    
    out << "# maxNumMerchants" << endl;
    out << maxNumMerchants << endl;
    
    out << "# numMerchants" << endl;
    out << numMerchants << endl;
    
    out << "#---------------------------------------- merchants[] started" << endl;
    for (int i = 0; i < maxNumMerchants; i++) {
        if (merchants[i] == NULL) {
            out << "#---------------------------------------- merchants[" << i << "]" << endl;
            out << TOMB_STONE_EMPTY << endl;
        }
        else {
            out << "#---------------------------------------- merchants[" << i << "]" << endl;
            out << TOMB_STONE_NON_EMPTY << endl;
            merchants[i]->save(out);
        }
    }
    out << "#---------------------------------------- merchants[] end" << endl;
    
    //--------------------------------------------------------------------------
    // Save cars[]
    //--------------------------------------------------------------------------
    out << "#---------------------------------------- cars" << endl;
    
    out << "# maxNumCars" << endl;
    out << maxNumCars << endl;
    
    out << "# numCars" << endl;
    out << numCars << endl;
    
    out << "#---------------------------------------- cars[] started" << endl;
    for (int i = 0; i < maxNumMerchants; i++) {
        if (cars[i] == NULL) {
            out << "#---------------------------------------- cars[" << i << "]" << endl;
            out << TOMB_STONE_EMPTY << endl;
        }
        else {
            out << "#---------------------------------------- cars[" << i << "]" << endl;
            out << TOMB_STONE_NON_EMPTY << endl;
            cars[i]->save(out);
        }
    }
    out << "#---------------------------------------- cars[] end" << endl;
  
    //--------------------------------------------------------------------------
    // Save dragons[]
    //--------------------------------------------------------------------------
    out << "#---------------------------------------- dragons" << endl;
    
    out << "# maxNumDragons" << endl;
    out << maxNumDragons << endl;
    
    out << "# numDragons" << endl;
    out << numDragons << endl;
    
    out << "#---------------------------------------- dragons[] started" << endl;
    for (int i = 0; i < maxNumDragons; i++) {
        if (dragons[i] == NULL) {
            out << "#---------------------------------------- dragons[" << i << "]" << endl;
            out << TOMB_STONE_EMPTY << endl;
        }
        else {
            out << "#---------------------------------------- dragons[" << i << "]" << endl;
            out << TOMB_STONE_NON_EMPTY << endl;
            dragons[i]->save(out);
        }
    }
    out << "#---------------------------------------- dragons[] end" << endl;
    
    //--------------------------------------------------------------------------
    // hero
    //--------------------------------------------------------------------------
    out << "#---------------------------------------- hero" << endl;

    hero->save(out);
    
    // don't save exited
}


void Board::load(istream &in) {
    cout << "Board::load(): started" << endl;;
    
    char buf[MAX_LEN_BUF];
    
    //out << "#---------------------------------------- class Board" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Board::load(): buf=" << buf << endl;;
    
    destroyAll();
    
    //--------------------------------------------------------------------------
    // Load board[][]
    //--------------------------------------------------------------------------
    cout << "Board::load(): Loading board[][]" << endl;;

    //out << "#---------------------------------------- board[][]" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Board::load(): buf=" << buf << endl;

    //out << "# rowSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << rowSize << endl;
    in >> rowSize;
    in.get(); // skip enter code.
    
    //out << "# colSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << colSize << endl;
    in >> colSize;
    in.get(); // skip enter code.
    
    initBoard(rowSize, colSize, NULL);

    //out << "#---------------------------------------- board[][] started" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            //out << "#---------------------------------------- board[" << i << "][" << j << "]" << endl;
            in.getline(buf, MAX_LEN_BUF); // skip comment

            board[i][j]->load(in);
        }
    }
    //out << "#---------------------------------------- board[][] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment

    //--------------------------------------------------------------------------
    // Load mons[]
    //--------------------------------------------------------------------------
    cout << "Board::load(): Loading mons[]" << endl;;
    
    //out << "#---------------------------------------- mons" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Board::load(): buf=" << buf << endl;

    //out << "# maxNumMons" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumMons << endl;
    in >> maxNumMons;
    in.get(); // skip enter code.
    
    //out << "# numMons" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numMons << endl;
    in >> numMons;
    in.get(); // skip enter code.
    
    mons = new Mon *[maxNumMons];
    
    //out << "#---------------------------------------- mons[] started" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment

    for (int i = 0; i < maxNumMons; i++) {
        //out << "#---------------------------------------- mons[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment

        string tombStone = "";
        in >> tombStone;
        in.get(); // skip enter code.
        
        if (tombStone == TOMB_STONE_EMPTY) {
            mons[i] = NULL;
        }
        else {
            mons[i] = new Mon();
            mons[i]->load(in);
            
            if (!mons[i]->isDead()) {
                board[mons[i]->getRow()][mons[i]->getCol()]->setUnit(mons[i]);
            }
        }
    }
    //out << "#---------------------------------------- mons[] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //--------------------------------------------------------------------------
    // Load bosses[]
    //--------------------------------------------------------------------------
    cout << "Board::load(): Loading bosses[]" << endl;;
    
    //out << "#---------------------------------------- bosses" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Board::load(): buf=" << buf << endl;
    
    //out << "# maxNumBosses" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumBosses << endl;
    in >> maxNumBosses;
    in.get(); // skip enter code.
    
    //out << "# numBosses" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numBosses << endl;
    in >> numBosses;
    in.get(); // skip enter code.
    
    bosses = new Boss *[maxNumBosses];
    
    //out << "#---------------------------------------- bosses[] started" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    for (int i = 0; i < maxNumBosses; i++) {
        //out << "#---------------------------------------- bosses[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        
        string tombStone = "";
        in >> tombStone;
        in.get(); // skip enter code.
        
        if (tombStone == TOMB_STONE_EMPTY) {
            bosses[i] = NULL;
        }
        else {
            bosses[i] = new Boss();
            bosses[i]->load(in);
            
            if (!bosses[i]->isDead()) {
                board[bosses[i]->getRow()][bosses[i]->getCol()]->setUnit(bosses[i]);
            }
        }
    }
    //out << "#---------------------------------------- bosses[] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //--------------------------------------------------------------------------
    // Load merchants[]
    //--------------------------------------------------------------------------
    cout << "Board::load(): Loading merchants[]" << endl;;
    
    //out << "#---------------------------------------- merchants" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Board::load(): buf=" << buf << endl;
    
    //out << "# maxNumMerchants" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumMerchants << endl;
    in >> maxNumMerchants;
    in.get(); // skip enter code.
    
    //out << "# numMerchants" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numMerchants << endl;
    in >> numMerchants;
    in.get(); // skip enter code.
    
    merchants = new Merchant *[maxNumMerchants];
    
    //out << "#---------------------------------------- merchants[] started" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    for (int i = 0; i < maxNumMerchants; i++) {
        //out << "#---------------------------------------- merchants[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        
        string tombStone = "";
        in >> tombStone;
        in.get(); // skip enter code.
        
        if (tombStone == TOMB_STONE_EMPTY) {
            merchants[i] = NULL;
        }
        else {
            merchants[i] = new Merchant();
            merchants[i]->load(in);
            
            if (!merchants[i]->isDead()) {
                board[merchants[i]->getRow()][merchants[i]->getCol()]->setUnit(merchants[i]);
            }
        }
    }
    //out << "#---------------------------------------- merchants[] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment

    //--------------------------------------------------------------------------
    // Load cars[]
    //--------------------------------------------------------------------------
    cout << "Board::load(): Loading cars[]" << endl;;
    
    //out << "#---------------------------------------- cars" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Board::load(): buf=" << buf << endl;
    
    //out << "# maxNumCars" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumCars << endl;
    in >> maxNumCars;
    in.get(); // skip enter code.
    
    //out << "# numCars" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numCars << endl;
    in >> numCars;
    in.get(); // skip enter code.
    
    cars = new Car *[maxNumCars];
    
    //out << "#---------------------------------------- cars[] started" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    for (int i = 0; i < maxNumCars; i++) {
        //out << "#---------------------------------------- cars[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        
        string tombStone = "";
        in >> tombStone;
        in.get(); // skip enter code.
        
        if (tombStone == TOMB_STONE_EMPTY) {
            cars[i] = NULL;
        }
        else {
            cars[i] = new Car();
            cars[i]->load(in);
            
            if (!cars[i]->isDead()) {
                board[cars[i]->getRow()][cars[i]->getCol()]->setUnit(cars[i]);
            }
        }
    }
    //out << "#---------------------------------------- cars[] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //--------------------------------------------------------------------------
    // Load dragons[]
    //--------------------------------------------------------------------------
    cout << "Board::load(): Loading dragons[]" << endl;;
    
    //out << "#---------------------------------------- dragons" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Board::load(): buf=" << buf << endl;
    
    //out << "# maxNumDragons" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << maxNumDragons << endl;
    in >> maxNumDragons;
    in.get(); // skip enter code.
    
    //out << "# numDragons" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << numDragons << endl;
    in >> numDragons;
    in.get(); // skip enter code.
    
    dragons = new Dragon *[maxNumDragons];
    
    //out << "#---------------------------------------- dragons[] started" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    cout << "Board::load(): buf=" << buf << endl;
    
    for (int i = 0; i < maxNumDragons; i++) {
        //out << "#---------------------------------------- dragons[" << i << "]" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        cout << "Board::load(): buf=" << buf << endl;

        string tombStone = "";
        in >> tombStone;
        in.get(); // skip enter code.
        
        if (tombStone == TOMB_STONE_EMPTY) {
            dragons[i] = NULL;
        }
        else {
            dragons[i] = new Dragon();
            dragons[i]->load(in);
            createDragonWithHead(dragons[i], DRAGON_LEN);
            if (!dragons[i]->isDead()) {
                board[dragons[i]->getRow()][dragons[i]->getCol()]->setUnit(dragons[i]);
            }
        }
    }
    //out << "#---------------------------------------- dragons[] end" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment

    //--------------------------------------------------------------------------
    // Load hero
    //--------------------------------------------------------------------------
    //cout << "Board::load(): Loading hero" << endl;;
    in.getline(buf, MAX_LEN_BUF); // skip comment

    hero = new Hero();
    hero->load(in);
    setUnit(hero->getRow(), hero->getCol(), hero);
    
    //--------------------------------------------------------------------------
    // etc
    //--------------------------------------------------------------------------
    exited = false;
    
    cout << "Board::load(): end" << endl;;
}

void Board::loadLevel(istream &in) {
    char buf[MAX_LEN_BUF];
    
    destroyAll(); // clear
    
    //--------------------------------------------------------------------------
    // read the title page of this level
    //--------------------------------------------------------------------------

    //out << "# titleRowSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << titleRowSize << endl;
    in >> titleRowSize;
    in.get(); // skip enter code.
    
    //out << "# titleColSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << titleColSize << endl;
    in >> titleColSize;
    in.get(); // skip enter code.
    
    title = new char *[titleRowSize];
    
    for (int i = 0; i < titleRowSize; i++) {
        title[i] = new char [titleColSize+1];
        in.getline(buf, MAX_LEN_BUF); // skip comment
        strncpy(title[i], buf, titleColSize+1);
    }

    //--------------------------------------------------------------------------
    // read the board
    //--------------------------------------------------------------------------

    //out << "# rowSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << rowSize << endl;
    in >> rowSize;
    in.get(); // skip enter code.
    
    //out << "# colSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << colSize << endl;
    in >> colSize;
    in.get(); // skip enter code.

    initBoard(rowSize, colSize, NULL);
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            char currentShape = in.get();
            board[i][j]->setItem(createItemByShape(currentShape));
            board[i][j]->setProp(createPropByShape(currentShape));
            setUnit(i, j, createUnitByShape(currentShape, i, j));
        }
        in.get(); // skip enter code
    }
        
    // 아래에서, 몬스터들과 보스들을 array에 셋해주어야 한다.
    // 일단 마리수를 count해서, 그만큼 어레이를 만든 다음, 모든 주소를 셋해야 한다
    // 주의할 점은, 몬스터보다 보스인지 먼저 count해야 한다.
    maxNumMons = 0;
    maxNumBosses = 0;
    maxNumMerchants = 0;
    maxNumCars = 0;
    maxNumDragons = 0;
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (board[i][j]->getUnit() != NULL) {
                if (board[i][j]->getUnit()->isBoss()) {
                    maxNumBosses++;
                }
                else if (board[i][j]->getUnit()->isMon()) {
                    maxNumMons++;
                }
                else if (board[i][j]->getUnit()->isMerchant()) {
                    maxNumMerchants++;
                }
                else if (board[i][j]->getUnit()->isCar()) {
                    maxNumCars++;
                }
                else if (board[i][j]->getUnit()->isDragon()) {
                    maxNumDragons++;
                }
            }
        }
    }
    
    //cout << "maxNumMons: " << maxNumMons << endl;
    
    // create random monsters
    mons = new Mon *[maxNumMons];
    numMons = 0;
    bosses = new Boss *[maxNumBosses];
    numBosses = 0;
    merchants = new Merchant *[maxNumMerchants];
    numMerchants = 0;
    cars = new Car *[maxNumCars];
    numCars = 0;
    dragons = new Dragon *[maxNumDragons];
    numDragons = 0;
    
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (board[i][j]->getUnit() != NULL) {
                // 파일로부터의 loadLevel()은 hero로 읽어들인다.
                if (board[i][j]->getUnit()->isHero()) {
                    hero = (Hero *)board[i][j]->getUnit();
                }
                else if (board[i][j]->getUnit()->isBoss()) {
                    bosses[numBosses] = (Boss *)board[i][j]->getUnit();
                    numBosses++;
                }
                else if (board[i][j]->getUnit()->isMon()) {
                    mons[numMons] = (Mon *)board[i][j]->getUnit();
                    numMons++;
                }
                else if (board[i][j]->getUnit()->isMerchant()) {
                    merchants[numMerchants] = (Merchant *)board[i][j]->getUnit();
                    numMerchants++;
                }
                else if (board[i][j]->getUnit()->isCar()) {
                    cars[numCars] = (Car *)board[i][j]->getUnit();
                    numCars++;
                }
                else if (board[i][j]->getUnit()->isDragon()) {
                    dragons[numDragons] = (Dragon *)board[i][j]->getUnit();
                    numDragons++;
                }
            }
        }
    }
    
    exited = false;
    initFx();
    
    //--------------------------------------------------------------------------
    // read the ending page of this level
    //--------------------------------------------------------------------------
    
    //out << "# endingRowSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << endingRowSize << endl;
    in >> endingRowSize;
    in.get(); // skip enter code.
    
    //out << "# endingColSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << endingColSize << endl;
    in >> endingColSize;
    in.get(); // skip enter code.
    
    ending = new char *[endingRowSize];
    
    for (int i = 0; i < endingRowSize; i++) {
        ending[i] = new char [endingColSize+1];
        in.getline(buf, MAX_LEN_BUF); // skip comment
        strncpy(ending[i], buf, endingColSize+1);
    }
}

void Board::showTitle() {
    if (title) {
        for (int i = 0; i < titleRowSize; i++) {
            cout << title[i] << endl;
        }
        
        while (!_kbhit()) {}
        getchar();
    }
}

void Board::showEnding() {
    if (ending) {
        for (int i = 0; i < endingRowSize; i++) {
            cout << ending[i] << endl;
        }
        
        while (!_kbhit()) {}
        getchar();
    }
}
