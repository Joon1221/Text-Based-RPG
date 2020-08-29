#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <iostream>

using namespace std;

#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

#include "main.h"
#include "item.h"
#include "unit.h"
#include "hero.h"
#include "tile.h"
#include "board.h"
#include "backpack.h"
#include "util.h"
#include "game.h"
//#include "sim.h"

class Game;

// Campaign
class GameManager {
protected:
    string userID;
    
    string campaignFilename;
    
    //Screen *title;
    char **title;
    int titleRowSize;
    int titleColSize;
    
    //Screen *ending;
    char **ending;
    int endingRowSize;
    int endingColSize;
    
    int numLevels;
    char **levelFilenames;
    int currentLevelIndex;
    
    Game *currentLevel; // 예전 초기 RPG의 main()
    
    // save/load feature
    char **saveFilenames;
    int maxSaveSlots;
    
    char *configFilename;
    
public:
    GameManager();
    virtual ~GameManager();
    
    void play(); // 진짜 game play가 아니라 그냥 main menu
    
    bool loadCampaign();
    
    void loadNextLevel();
    void loadCurrentLevelAgain();

    void showTitle();
    void showEnding();
};

#endif
