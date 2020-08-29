#include <iostream>
#include <cmath>
#include <assert.h>

using namespace std;

#include "main.h"
#include "unit.h"
#include "hero.h"
#include "prop.h"
#include "mon.h"
#include "board.h"
#include "tile.h"
#include "tileset.h"
#include "boss.h"

#include "sim.h"
extern Sim *sim;

// Default Constructor
Boss::Boss()
    : Mon(DEFAULT_BOSS_SHAPE, DEFAULT_BOSS_HP, DEFAULT_BOSS_HP_MAX,
          DEFAULT_BOSS_MELEE_ATK, DEFAULT_BOSS_RANGE_ATK,
          DEFAULT_BOSS_GOLD, DEFAULT_BOSS_EXP,
          DEFAULT_LEVEL, DEFAULT_MAX_EXP_TO_LEVEL_UP,
          DEFAULT_BOSS_FREEZE, DEFAULT_BOSS_RANGE) {
    resetAStar();
}

// General Constructor
Boss::Boss(char shape, int hp, int maxHp, int meeleAtk, int rangeAtk,
           int gold, int exp, int level, int currentMaxExpToLevelUp,
           bool freeze, int range)
    : Mon(shape, hp, maxHp, meeleAtk, rangeAtk, gold, exp, level,
           currentMaxExpToLevelUp, freeze, range) {
    resetAStar();
}

Boss::~Boss() {
    resetAStar();
}

void Boss::print() {
#ifdef ANSI_COLOR_OUTPUT
    cout << MAGENTA;
#endif
    cout << shape;
#ifdef ANSI_COLOR_OUTPUT
    cout << RESET;
#endif
}

// A* related
#define ROW_DIR 0
#define COL_DIR 1
int DIRS[2][NUM_HERO_MOVE_DIR] = {
    {-1, 0, 1, 0}, // row dir
    { 0, 1, 0,-1}  // col dir
};

void Boss::move(int moveDir) {
//    cout << "Boss::move()" << endl;
    //--------------------------------------------------------------------------
    // IQ 120
    // 출처: https://en.wikipedia.org/wiki/A*_search_algorithm
    //--------------------------------------------------------------------------
#ifdef BOSS_IQ_120
    if (pathExist) {
//        cout << "if (pathExist) {: pathLen=" << pathLen << endl;
//        cout << "if (pathExist) {: curIndexPath=" << curIndexPath << endl;

        if (curIndexPath < pathLen-1 || (fakeGoal && curIndexPath < pathLen)) {
//            cout << "if (curIndexPath < pathLen-1) {" << endl;
            // boss가 a*를 돌릴때 hero의 위치를 oldHero라고 하고, 만약 hero가 그 사이에 움직였다면..
            // newHero로 놓는다면, oldHero와 newHero사이의 dist가 oldHero와 현재 boss 사이의
            // dist보다 작은 동안에는 a*로 찾은 path를 reset하지 않는다.
            // 하지만, 아직 남은 거리와 hero가 움직인 거리가 차이가 난다면, 새로 계산하게 하였다.
            // 이렇게 하는 이유는, 그래야만, 부하가 걸리지 않는다. 만약 hero가 중간에 움직일 때마다
            // A*를 새로 돌리면, 수많은 boss들이 boss rush때 다시 a*를 돌리게 되면서 fps가
            // 1fps이하로 떨어진다.
            int rowDistOldHeroAndNewHero = abs(pathRow[pathLen-1] - sim->hero->getRow());
            int colDistOldHeroAndNewHero = abs(pathCol[pathLen-1] - sim->hero->getCol());
            int distOldHeroAndNewHero = sqrt(rowDistOldHeroAndNewHero * rowDistOldHeroAndNewHero +
                                             colDistOldHeroAndNewHero * colDistOldHeroAndNewHero);
            int rowDistOldHeroAndBoss = abs(pathRow[pathLen-1] - row);
            int colDistOldHeroAndBoss = abs(pathCol[pathLen-1] - col);
            int distOldHeroAndBoss = sqrt(rowDistOldHeroAndBoss * rowDistOldHeroAndBoss +
                                          colDistOldHeroAndBoss * colDistOldHeroAndBoss);
            
            if (distOldHeroAndBoss > distOldHeroAndNewHero &&
//            if (
                sim->board->getUnit(pathRow[curIndexPath], pathCol[curIndexPath]) == NULL &&
                (sim->board->getProp(pathRow[curIndexPath], pathCol[curIndexPath]) == NULL ||
                 sim->board->getProp(pathRow[curIndexPath], pathCol[curIndexPath])->isClimbable())) {
//                cout << "moved!!!" << endl;
                sim->board->setUnit(row, col, NULL);
                sim->board->setUnit(pathRow[curIndexPath], pathCol[curIndexPath], this);
                curIndexPath++;
                    
                if (pathExist && !fakeGoal &&
                    (sim->board->getUnit(pathRow[pathLen-1], pathCol[pathLen-1]) == NULL ||
                     !sim->board->getUnit(pathRow[pathLen-1], pathCol[pathLen-1])->isHero())) {
                    resetAStar();
                }
                return;
            }
            resetAStar();
            avoidUnit = true; // 만약 hero로 가는길 도중에 unit에 막혔을 경우, 다시 path를 찾는데, 이때, unit을 피해서 path를 찾게 한다.
//            cout << "blocked by unit -> resetAStart()" << pathLen << endl;
        }
        else if (!fakeGoal) {
//            cout << "resetAStar()" << endl;
            if (sim->board->getUnit(pathRow[pathLen-1], pathCol[pathLen-1]) != NULL &&
                sim->board->getUnit(pathRow[pathLen-1], pathCol[pathLen-1])->isHero()) {
//                cout << "hero beside boss" << endl;
                Hero *hero = (Hero *)sim->board->getUnit(pathRow[pathLen-1], pathCol[pathLen-1]);
                if (meleeAtk - hero->getDef()/2 > 0) {
//                    cout << "boss attacks hero" << endl;
                    hero->decHp(meleeAtk - hero->getDef()/2);
                }
            }
            resetAStar();
            return;
        }
    }
#endif
    
    //--------------------------------------------------------------------------
    // IQ 80
    //--------------------------------------------------------------------------
#ifdef BOSS_IQ_80
    if (moveOrFollowHuman(moveDir)) {
        return;
    }
#endif

    //--------------------------------------------------------------------------
    // IQ 120
    // 출처: https://en.wikipedia.org/wiki/A*_search_algorithm
    //--------------------------------------------------------------------------
#ifdef BOSS_IQ_120
//    cout << "A* started!!" << endl;

//function A*(start,goal)
    double dist = sqrt((sim->board->getHero()->getRow() - row) * (sim->board->getHero()->getRow() - row) +
                       (sim->board->getHero()->getCol() - col) * (sim->board->getHero()->getCol() - col));
    if (dist > range) {
        Mon::move(moveDir);
        return;
    }
    
    Tile *start = sim->board->getTile(row, col); // Boss' position
    Tile *goal = sim->board->getTile(sim->board->getHero()->getRow(), sim->board->getHero()->getCol()); // Hero's position
    
    // 만약 hero와 boss의 range를 측정해서, boss의 기본 따라가기 range보다 작으면 hero를 찾아내고, 아니면, 그냥 random move로 해야 한다.
    // 아직 implement되지는 않음(201601120959)
    
//    ClosedSet := {}    	  // The set of nodes already evaluated.
    TileSet *closedSet = new TileSet();
    
//    OpenSet := {start}    // The set of tentative nodes to be evaluated, initially containing the start node
    TileSet *openSet = new TileSet();
    openSet->insert(sim->board->getTile(row, col));
    
//    Came_From := the empty map    // The map of navigated nodes.
//    g_score := map with default value of Infinity
//    g_score[start] := 0    // Cost from start along best known path.
    sim->board->getTile(row, col)->g = 0.0;
    
//    // Estimated total cost from start to goal through y.
//    f_score := map with default value of Infinity
//    f_score[start] := heuristic_cost_estimate(start, goal)
    sim->board->getTile(row, col)->h = heuristicCostEstimate(start, goal);
    sim->board->getTile(row, col)->f = sim->board->getTile(row, col)->g + sim->board->getTile(row, col)->h;

//    while OpenSet is not empty
    while (openSet->size() > 0) {
//        current := the node in OpenSet having the lowest f_score[] value
        Tile *current = openSet->lowestF();
//        if current = goal
//            return reconstruct_path(Came_From, goal)
        if (current == goal) {
            delete openSet;
            delete closedSet;
            return reconstructPath(start, goal);
        }
            
//        OpenSet.Remove(current)
        openSet->remove(current);
//        ClosedSet.Add(current)
        closedSet->insert(current);
//        for each neighbor of current

        for (int i = 0; i < NUM_HERO_MOVE_DIR; i++) {
            int neighbourRow = current->row + DIRS[ROW_DIR][i];
            int neighbourCol = current->col + DIRS[COL_DIR][i];
            
            if (!sim->board->validate(neighbourRow, neighbourCol)) {
                continue;
            }
            
            if ((avoidUnit && sim->board->getUnit(neighbourRow, neighbourCol) != NULL) ||
                (sim->board->getProp(neighbourRow, neighbourCol) != NULL &&
                !sim->board->getProp(neighbourRow, neighbourCol)->isClimbable())) {
                continue;
            }
            
            Tile *neighbour = sim->board->getTile(neighbourRow, neighbourCol);
            
//            if neighbor in ClosedSet
//                continue		// Ignore the neighbor which is already evaluated.
            if (closedSet->find(neighbour) != NULL) {
                continue;
            }
                
//            tentative_g_score := g_score[current] + dist_between(current,neighbor) // length of this path.
            double tentativeG = current->g + 1;
//            if neighbor not in OpenSet	// Discover a new node
//                OpenSet.Add(neighbor)
            if (openSet->find(neighbour) == NULL) {
                neighbour->g = tentativeG;
                openSet->insert(neighbour);
            }
//            else if tentative_g_score >= g_score[neighbor]
//                continue		// This is not a better path.
            else if (tentativeG >= neighbour->g)  {
                continue;
            }
                
//            // This path is the best until now. Record it!
//            Came_From[neighbor] := current
//            g_score[neighbor] := tentative_g_score
//            f_score[neighbor] := g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)
            neighbour->cameFromRow = current->row;
            neighbour->cameFromCol = current->col;
            neighbour->g = tentativeG;
            neighbour->h = heuristicCostEstimate(neighbour, goal);
            neighbour->f = neighbour->g + neighbour->h;
        }
//            return failure
    }
    
    // if path to hero is not available, find the tile that is nearest to
    // Hero(smallest h_score, also the smallest g_score out of the smallest h_scores) and it to the goal
    // 정리: 위에서 search할때 쓴 closedSet의 tile들중 가장 작은 h값을 가진 tile들중(hero에 가장 근접하면서도),
    //      g가 가장 작은(즉 boss와 가장 가까운) tile을 임시 goal로 하여 path를 만든다.
    //      즉, boss는 이제 hero와 boss사이에 가장 가까운 곳 근처로 가서 냄새맡으면서 맴돌게 된다.
    Tile *lowestGH = closedSet->lowestH();
    closedSet->remove(lowestGH);

    if (closedSet->size() > 1) {
        Tile *lowestH = closedSet->lowestH();
        closedSet->remove(lowestH);

        while (lowestH->h == lowestGH->h) {
            if (lowestGH->g > lowestH->g) {
                lowestGH = lowestH;
            }
            if (closedSet->size() == 0) {
                break;
            }
            lowestH = closedSet->lowestH();
            closedSet->remove(lowestH);
        }
    }
    
    delete openSet;
    delete closedSet;
    // 만약 boss가 hero와 가장 근접한 위치에 서 있을 경우는, 새로 path를 찾지 말고, 그냥 random으로
    // 근처를 방황하게 하기 위해, 이 부분을 skip하면 된다.
    if (lowestGH != start) {
        fakeGoal = true;
        return reconstructPath(start, lowestGH);
    }
#endif

    Mon::move(moveDir);
}

#ifdef BOSS_IQ_120
double Boss::heuristicCostEstimate(Tile *neighbour, Tile *goal) {
    return sqrt((neighbour->row - goal->row)*(neighbour->row - goal->row) +
                (neighbour->col - goal->col)*(neighbour->col - goal->col));
}

//function reconstruct_path(Came_From,current)
void Boss::reconstructPath(Tile *start, Tile *goal) {
    pathLen = 1;
    Tile *current = goal;
    while (current != start) {
        pathLen++;
        current = sim->board->getTile(current->cameFromRow, current->cameFromCol);
    }
    
//    total_path := [current]
    int curIndex = pathLen-1;
    pathRow[curIndex] = goal->row;
    pathCol[curIndex] = goal->col;

    current = sim->board->getTile(goal->cameFromRow, goal->cameFromCol);
//    while current in Came_From.Keys:
    while (current != start) {
//        current := Came_From[current]
//        total_path.append(current)
        curIndex--;
        pathRow[curIndex] = current->row;
        pathCol[curIndex] = current->col;
        current = sim->board->getTile(current->cameFromRow, current->cameFromCol);
    }
    
    curIndex--;

    assert(curIndex == 0);

    pathRow[curIndex] = start->row;
    pathCol[curIndex] = start->col;
    
    pathExist = true;
    curIndexPath = 1;
//
//    return total_path
    // 멤버 변수들에 바로 넣으므로 필요없음.
}

//bool pathExist;
//int pathRow[MAX_LEN_PATH_BY_ASTAR];
//int pathCol[MAX_LEN_PATH_BY_ASTAR];
//int pathLen;
//int curIndexPath;
#endif

bool Boss::isMon() {
    return true;
}

bool Boss::isBoss() {
    return true;
}

string Boss::getID() {
    return string(UNIT_ID_BOSS);
}

void Boss::save(ostream &out) {
    Mon::save(out);
    out << "#-------------------- class Boss" << endl;
}

void Boss::load(istream &in) {
    Mon::load(in);
    char buf[MAX_LEN_BUF];
    
    //out << "#-------------------- class Boss" << endl;
    in.getline(buf, 80); // skip comment
}

void Boss::resetAStar() {
    pathExist = false;
    pathLen = 0;
    curIndexPath = -1;
    fakeGoal = false; // 만약 hero로 가는길이 다 막힐 경우, 근접한 곳으로 goal이 지정되는데, 그곳까지 움직이게 한다.
    avoidUnit = false; // 만약 hero로 가는길 도중에 unit에 막혔을 경우, 다시 path를 찾는데, 이때, unit을 피해서 path를 찾게 한다.
}
