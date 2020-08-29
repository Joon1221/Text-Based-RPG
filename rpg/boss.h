#ifndef BOSS_H
#define BOSS_H

class Unit;
class Mon;
class Tile;

//------------------------------------------------------------------------------
// class Boss: child class of class Mon
//------------------------------------------------------------------------------
class Boss : public Mon {
protected:
    //--------------------------------------------------------------------------
    // A* related
    //--------------------------------------------------------------------------
    bool pathExist;
    int pathRow[MAX_LEN_PATH_BY_ASTAR];
    int pathCol[MAX_LEN_PATH_BY_ASTAR];
    int pathLen;
    int curIndexPath;
    bool fakeGoal; // 만약 hero로 가는길이 다 막힐 경우, 근접한 곳으로 goal이 지정되는데, 그곳까지 움직이게 한다.
    bool avoidUnit; // 만약 hero로 가는길 도중에 unit에 막혔을 경우, 다시 path를 찾는데, 이때, unit을 피해서 path를 찾게 한다.

    void resetAStar();
    void reconstructPath(Tile *start, Tile *goal);
    double heuristicCostEstimate(Tile *neighbour, Tile *goal);
    
public:
    Boss();
    Boss(char shape, int hp, int maxHp, int meeleAtk, int rangeAtk,
         int gold, int exp, int level, int currentMaxExpToLevelUp,
         bool freeze, int range);
    virtual ~Boss();
    
    void print();
    
    void move(int moveDir);
    
    bool isMon();
    bool isBoss();
    
    virtual string getID();

    virtual void save(ostream &out);
    virtual void load(istream &in);
};

#endif
