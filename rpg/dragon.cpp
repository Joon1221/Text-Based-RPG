#include <iostream>

using namespace std;

#include "main.h"
#include "board.h"
#include "unit.h"
#include "prop.h"
#include "dragon.h"

#include "sim.h"
extern Sim *sim;

Dragon::Dragon()
    : Unit(DEFAULT_DRAGON_SHAPE_HEAD, -1, -1,
           DEFAULT_DRAGON_HP, DEFAULT_DRAGON_MAX_HP,
           DEFAULT_DRAGON_MELEE_ATK, DEFAULT_DRAGON_RANGE_ATK,
           DEFAULT_DRAGON_GOLD, DEFAULT_DRAGON_EXP,
           DEFAULT_DRAGON_LEVEL, DEFAULT_MAX_EXP_TO_LEVEL_UP,
           DEFAULT_DRAGON_FREEZE) {
    initDragon(1);
}

Dragon::Dragon(char shape, int len)
    : Unit(shape, -1, -1,
       DEFAULT_DRAGON_HP, DEFAULT_DRAGON_MAX_HP,
       DEFAULT_DRAGON_MELEE_ATK, DEFAULT_DRAGON_RANGE_ATK,
       DEFAULT_DRAGON_GOLD, DEFAULT_DRAGON_EXP,
       DEFAULT_DRAGON_LEVEL, DEFAULT_MAX_EXP_TO_LEVEL_UP,
       DEFAULT_DRAGON_FREEZE) {
    initDragon(len);
}

Dragon::Dragon(char shape, int hp, int maxHp, int meeleAtk, int rangeAtk,
               int gold, int exp, int level, int currentMaxExpToLevelUp,
               bool freeze, int len)
        : Unit(shape, -1, -1, hp, maxHp, meeleAtk, rangeAtk, gold, exp, level, currentMaxExpToLevelUp, freeze) {
    initDragon(len);
}

void Dragon::initDragon(int len) {
    this->len = len;
    prev = NULL;
    next = NULL;
    unitCurDir = MOVE_DIR_NORTH;
}

Dragon::~Dragon() {
    destroyDragon();
}

void Dragon::destroyDragon() {
}

void Dragon::print() {
#ifdef ANSI_COLOR_OUTPUT
    cout << BOLDBLUE << shape << RESET;
#else
    Unit::print();
#endif
}

void Dragon::printStat() {
    cout << "Dragon's Dir: ";
    if (unitCurDir == MOVE_DIR_NORTH) {
        cout << "NORTH";
    }
    else if (unitCurDir == MOVE_DIR_EAST) {
        cout << "EAST";
    }
    else if (unitCurDir == MOVE_DIR_SOUTH) {
        cout << "SOUTH";
    }
    else if (unitCurDir == MOVE_DIR_WEST) {
        cout << "WEST";
    }
    else {
        cout << "ERRRRRRRRRRRRR";
    }
    cout << endl;

    cout << "Dragon's Right Dir: ";
    if (sim->board->getRightDir(unitCurDir) == MOVE_DIR_NORTH) {
        cout << "NORTH";
    }
    else if (sim->board->getRightDir(unitCurDir) == MOVE_DIR_EAST) {
        cout << "EAST";
    }
    else if (sim->board->getRightDir(unitCurDir) == MOVE_DIR_SOUTH) {
        cout << "SOUTH";
    }
    else if (sim->board->getRightDir(unitCurDir) == MOVE_DIR_WEST) {
        cout << "WEST";
    }
    else {
        cout << "ERRRRRRRRRRRRR";
    }
    cout << endl;
}

bool Dragon::isDragon() {
    return true;
}

// Dragon만 가진 기능. 주어진 위치로 무조건 움직이면 된다.
void Dragon::move(int nextRow, int nextCol) {
    int prevRow = row;
    int prevCol = col;
    
    sim->board->setUnit(row, col, NULL); // remove the shape from the current pos
    sim->board->setUnit(nextRow, nextCol, this); // set the unit to the next pos
    
    if (next != NULL) {
        if (!(nextRow == next->getRow() && nextCol == next->getCol())) {
            next->move(prevRow, prevCol);
//            dir = moveDir; 여기에서는 따로 calculate을 해야 한다. 현재 row, col에서..
//                           nextRow, nextCol로 움직였을때, 그 방향을 dir에 넣는다.
//                           하지만 아직 필요치 않기 때문에 용의 body에서는 dir를 넣지 않기로 한다.
        }
    }
}

void Dragon::move(int moveDir) {
    bool moved = false;
  
    int prevRow = row;
    int prevCol = col;

    int nextRow = row;
    int nextCol = col;
    
//    
//    int nextRow = row;
//    int nextCol = col;
//    
//    if (moveDir == MOVE_DIR_NORTH) {
//        nextRow--;
//    }
//    else if (moveDir == MOVE_DIR_EAST) {
//        nextCol++;
//    }
//    else if (moveDir == MOVE_DIR_SOUTH) {
//        nextRow++;
//    }
//    else if (moveDir == MOVE_DIR_WEST) {
//        nextCol--;
//    }
   
    /*
    if (sim->board->validate(nextRow, nextCol) &&
        sim->board->isClimbable(nextRow, nextCol) &&
        sim->board->getNumEmptyCells(nextRow, nextCol) >= MIN_NUM_EMPTY_CELLS_TO_MOVE) {
        
        //cout << sim->board->getNumEmptyCells(nextRow, nextCol) << endl;
        //cout << sim->board->canExit(nextRow, nextCol) << endl;
        //exit(1);
        
        sim->board->setUnit(row, col, NULL); // remove the shape from the current pos
        sim->board->setUnit(nextRow, nextCol, this); // set the unit to the next pos
        moved = true;
        this->dir = dir;
    }
     */
    
    

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
 
    int leftRow;
    int leftCol;
    int rightRow;
    int rightCol;
    int forwardRow;
    int forwardCol;
    int leftForwardRow;
    int leftForwardCol;
    int rightForwardRow;
    int rightForwardCol;
    
    int leftLen = 0;
    int rightLen = 0;
    int forwardLen = 0;
    
    bool aiDone = false;
    
    sim->board->getLeftPos(row, col, unitCurDir, &leftRow, &leftCol);
    sim->board->getRightPos(row, col, unitCurDir, &rightRow, &rightCol);
    sim->board->getForwardRightPos(row, col, unitCurDir, &rightForwardRow, &rightForwardCol);
    sim->board->getForwardLeftPos(row, col, unitCurDir, &leftForwardRow, &leftForwardCol);
    sim->board->getForwardPos(row, col, unitCurDir, &forwardRow, &forwardCol);
#ifdef DEBUG_DRAGON_MOVE
    cout << "Dragon::move(): unitCurDir=" << unitCurDir << endl;
    cout << "Dragon::move(): row=" << row << endl;
    cout << "Dragon::move(): col=" << col << endl;

    cout << "Dragon::move(): forwardRow=" << forwardRow << endl;
    cout << "Dragon::move(): forwardCol=" << forwardCol << endl;

    cout << "Dragon::move(): leftForwardRow=" << leftForwardRow << endl;
    cout << "Dragon::move(): leftForwardCol=" << leftForwardCol << endl;

    cout << "Dragon::move(): rightForwardRow=" << rightForwardRow << endl;
    cout << "Dragon::move(): rightForwardCol=" << rightForwardCol << endl;
#endif

    if (sim->board->isClimbable(leftRow, leftCol) && sim->board->isClimbable(rightRow, rightCol)) {
#ifdef DEBUG_DRAGON_MOVE
        cout << "Dragon::move():0" << endl;
#endif
        // 1) L과 R과 F가 open이고, 동시에(AND) LD/RD가 동시에 막혀있으면, call해야 한다.
        if (!sim->board->isClimbable(leftForwardRow, leftForwardCol) && !sim->board->isClimbable(rightForwardRow, rightForwardCol) && sim->board->isClimbable(forwardRow, forwardCol)) {
#ifdef DEBUG_DRAGON_MOVE
            cout << "Dragon::move():1a" << endl;
#endif
            leftLen = sim->board->getLenWalls(leftRow, leftCol, sim->board->getLeftDir(unitCurDir));
#ifdef DEBUG_DRAGON_MOVE
            cout << "Dragon::move():leftLen=" << leftLen << endl;
            cout << "Dragon::move():1b" << endl;
#endif
            rightLen = sim->board->getLenWalls(rightRow, rightCol, sim->board->getRightDir(unitCurDir)); 
#ifdef DEBUG_DRAGON_MOVE
            cout << "Dragon::move():rightLen=" << rightLen << endl;
            cout << "Dragon::move():1c" << endl;
#endif
            forwardLen = sim->board->getLenWalls(forwardRow, forwardCol, unitCurDir); 
#ifdef DEBUG_DRAGON_MOVE
            cout << "Dragon::move():forwardLen=" << forwardLen << endl;
            cout << "Dragon::move():1d" << endl;
#endif
        }
        // 2) L과 R이 open이고, 동시에(AND) LD/F/RD 셋중에 한개라도 막혀있으면, call해야 한다.
        else if (!sim->board->isClimbable(leftForwardRow, leftForwardCol) || !sim->board->isClimbable(rightForwardRow, rightForwardCol) || !sim->board->isClimbable(forwardRow, forwardCol)){
            leftLen = sim->board->getLenWalls(leftRow, leftCol, sim->board->getLeftDir(unitCurDir));
            rightLen = sim->board->getLenWalls(rightRow, rightCol, sim->board->getRightDir(unitCurDir));
        }
        aiDone = true;
    }
    //    3a) 만약 L만 open일 경우, F는 반드시 open이면서, LD가 block일 경우..
    else if (sim->board->isClimbable(leftRow, leftCol) && sim->board->isClimbable(forwardRow, forwardCol) && !sim->board->isClimbable(leftForwardRow, leftForwardCol)) {
        leftLen = sim->board->getLenWalls(leftRow, leftCol, sim->board->getLeftDir(unitCurDir));
        forwardLen = sim->board->getLenWalls(forwardRow, forwardCol, unitCurDir);
        aiDone = true;
    }
    //    3b) 만약 R만 open일 경우, F는 반드시 open이면서, RD가 block일 경우..
    else if (sim->board->isClimbable(rightRow, rightCol) && sim->board->isClimbable(forwardRow, forwardCol) && !sim->board->isClimbable(rightForwardRow, rightForwardCol)) {
        rightLen = sim->board->getLenWalls(rightRow, rightCol, sim->board->getRightDir(unitCurDir));
        forwardLen = sim->board->getLenWalls(forwardRow, forwardCol, unitCurDir);
        aiDone = true;
    }
    else {
        // 위의 어떤 경우도 아니라면, 그냥 random하게 움직이도록 내버려둔다.
        unitCurDir = moveDir;
    }
    
    // random하게 움직이지 않을 경우..
    if (aiDone) {
        if (leftLen > rightLen && leftLen > forwardLen) {
    #ifdef DEBUG_DRAGON_MOVE
            cout << "Dragon::move(): unitCurDir = sim->board->getLeftDir(unitCurDir);" << endl;
    #endif
            unitCurDir = sim->board->getLeftDir(unitCurDir);
        }
        else if (rightLen > leftLen && rightLen > forwardLen) {
    #ifdef DEBUG_DRAGON_MOVE
            cout << "Dragon::move(): unitCurDir = sim->board->getRightDir(unitCurDir);" << endl;
            cout << "Dragon::move(): prev unitCurDir = " << unitCurDir << endl;
    #endif
            unitCurDir = sim->board->getRightDir(unitCurDir);
    #ifdef DEBUG_DRAGON_MOVE
            cout << "Dragon::move(): new unitCurDir = " << unitCurDir << endl;
    #endif
        }
        else {
    #ifdef DEBUG_DRAGON_MOVE
            cout << "Dragon::move(): unitCurDir = unitCurDir;" << endl;
    #endif
        }
    }
    
    if (unitCurDir == MOVE_DIR_NORTH) {
        nextRow = row - 1;
    }
    else if (unitCurDir == MOVE_DIR_EAST) {
        nextCol = col + 1;
    }
    else if (unitCurDir == MOVE_DIR_SOUTH) {
        nextRow = row + 1;
    }
    else if (unitCurDir == MOVE_DIR_WEST) {
        nextCol = col - 1;
    }
    
    if (sim->board->isClimbable(nextRow, nextCol)) {
#ifdef DEBUG_DRAGON_MOVE
        cout << "Dragon::move(): if (sim->board->isClimbable(nextRow, nextCol)) {" << endl;
#endif
        moved = true;
    }
    
    if (moved) {
#ifdef DEBUG_DRAGON_MOVE
        cout << "Dragon::move(): if (moved) {" << endl;
#endif
        sim->board->setUnit(prevRow, prevCol, NULL);
        sim->board->setUnit(nextRow, nextCol, this);
    }
    
    // 만약 움직였다면, 다음 몸통에게 나의 이전 위치로 움직이라고 하면, 이제 dragon의 모든 몸통이 다 따라온다.
    if (moved && next != NULL) {
        // 내 이전 위치와 내 다음 몸통의 위치가 같다는 것은 Dragon이 맨 처음 시작할 때, 몸통이
        // 겹쳐 있었던 상태에서 내 위치가 새로 빠져나온 것이므로, 이전 몸통을 이제 tile위에 등장하게 한다.
        //if (prevRow == next->getRow() && prevCol == next->getCol()) {
        next->move(prevRow, prevCol);
        //}
    }
}

// battle
void Dragon::interact(Unit *unit) {
    if (unit == NULL) {
        return;
    }
    
    decHp(unit->getMeleeAtk()); // hero attacks Dragon(me).
    if (!isDead()) {
        unit->decHp(meleeAtk); // Dragon(I) attacks hero.
    }
    else {
        // looted by unit
        unit->incGold(gold);
        unit->incExp(exp);
        
        gold = 0;
        exp = 0;
    }
}

string Dragon::getID() {
    return string(UNIT_ID_DRAGON);
}

void Dragon::save(ostream &out) {
    Unit::save(out);
    out << "#-------------------- class Dragon" << endl;
    
    out << "# len" << endl;
    out << len << endl;
}

void Dragon::load(istream &in) {
    Unit::load(in);
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Dragon" << endl;
    in.getline(buf, 80); // skip comment
    
    //out << "# len" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << len << endl;
    in >> len;
    in.get(); // skip enter code.
}

// 만약 주어진 위치에 만들수 없다면, 만들지 않고 NULL를 return.
Dragon *createDragon(int row, int col, int len) {
    int dragonStartRow = row;
    int dragonStartCol = col;
    
    Dragon *dragonHead = new Dragon(DEFAULT_DRAGON_SHAPE_HEAD, len);
    sim->board->setUnit(dragonStartRow, dragonStartCol, dragonHead);
  
    Dragon *curDragonBody = dragonHead;
    for (int i = 1; i < len; i++) {
        // 맨 처음 등장할 때는, 그냥 같은 자리에 위치하게 한다.
        Dragon *nextDragonBody = new Dragon(DEFAULT_DRAGON_SHAPE_BODY, len);
        nextDragonBody->setRow(dragonStartRow);
        nextDragonBody->setCol(dragonStartCol);
        
        curDragonBody->next = nextDragonBody;
        nextDragonBody->prev = curDragonBody;
        
        curDragonBody = nextDragonBody;
    }
    
    // 위에서 만들어진 dragon을 member variable에 넣어주면 끝.
    // 이제 moveDragon()에서 움직이게 할 수 있다.
    return dragonHead;
}

// 만약 주어진 위치에 만들수 없다면, 만들지 않고 NULL를 return.
void createDragonWithHead(Dragon *dragonHead, int len) {
    int dragonStartRow = dragonHead->getRow();
    int dragonStartCol = dragonHead->getCol();
    
    Dragon *curDragonBody = dragonHead;
    for (int i = 1; i < len; i++) {
        // 맨 처음 등장할 때는, 그냥 같은 자리에 위치하게 한다.
        Dragon *nextDragonBody = new Dragon(DEFAULT_DRAGON_SHAPE_BODY, len);
        nextDragonBody->setRow(dragonStartRow);
        nextDragonBody->setCol(dragonStartCol);
        
        curDragonBody->next = nextDragonBody;
        nextDragonBody->prev = curDragonBody;
        
        curDragonBody = nextDragonBody;
    }
}