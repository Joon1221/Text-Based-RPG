#include <iostream>
#include <fstream>

using namespace std;

#include "main.h"
#include "util.h"
#include "game.h"
#include "game_manager.h"

// Campaign
GameManager::GameManager() { //??????????????????????????????????????????????????????????????????????????????????????
    currentLevel = NULL;
}

GameManager::~GameManager() { //??????????????????????????????????????????????????????????????????????????????????????
}

void GameManager::play() {
    int userNum = -1;
    
    do {
        // 유저에게 campaign
        // 유저에게 single
        cout << "1. Campaign" << endl;
        cout << "2. Single Random Mode" << endl;
        cout << "3. Single Level" << endl;
        cout << endl;
        cout << "Enter a mode (-1 to exit): " << endl;
        
        cin >> userNum;
        
        if (userNum == 1) {
            if (loadCampaign()) {
                while (true) {
                    currentLevel->play();
                    // the player cleared the current level.
                    if (currentLevel->getPlayResult()) {
                        
                        if (currentLevelIndex+1 == numLevels) {
                            showEnding();
                            break;
                        }
                        
                        char command;
                        while (true) {
                            cout << "Next Level? (Y/n) : ";
                            cin >> command;
                            cin.get();
                            
                            if (command == 'y') {
                                loadNextLevel();
                                break;
                            }
                            else if (command == 'n') {
                                break;
                            }
                        }
                        
                        if (command == 'n') {
                            break;
                        }
                    }
                    // the player has not been cleared the current level.
                    else {
                        char command;
                        while (true) {
                            cout << "Play again? (Y/n) : ";
                            cin >> command;
                            cin.get();
                            
                            if (command == 'y') {
                                loadCurrentLevelAgain();
                                break;
                            }
                            else if (command == 'n') {
                                break;
                            }
                        }
                        
                        if (command == 'n') {
                            break;
                        }
                    }
                }
            }
        }
        else if (userNum == 2) {
            Game *game = new Game();
            game->initRandomOrTestMode();
            game->play();
            delete game;
        }
        else if (userNum == 3) {
            Game *game = new Game();
            game->initSingleLevelMode();
            game->commandLoadLevel(';');
            game->play();

            delete game;
        }
        else if (userNum != -1) {
            cout << "error: invalid number." << endl;
            cout << endl;
        }
    } while (userNum != -1);
}

bool GameManager::loadCampaign() {
    campaignFilename = "";
    
    cout << "Enter the campaign filename ('c' to cancel): ";
    cin >> campaignFilename;
    cin.get();
    
    if (campaignFilename == "c") {
        return false;
    }
    
    ifstream in;
    in.open(campaignFilename.c_str());
    
    if (in.fail()) { // error
        cout << "error: failed to open the campaign file \"" << campaignFilename << "\"." << endl;
        in.close();
        return false;
    }
    
    // load campaign start
    char buf[MAX_LEN_BUF];
    
    //======================================================================
    // load title screen
    //======================================================================
    
    //#-------------------------------------------------------------------------------
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# rowSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << rowSize << endl;
    in >> titleRowSize;
    in.get(); // skip enter code.
    
    //out << "# colSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << colSize << endl;
    in >> titleColSize;
    in.get(); // skip enter code.
    
    title = new char *[titleRowSize];
    
    for (int i = 0; i < titleRowSize; i++) {
        title[i] = new char [titleColSize+1];
        in.getline(buf, MAX_LEN_BUF); // skip comment
        strncpy(title[i], buf, titleColSize+1);
    }
    
    //======================================================================
    // load level filenames
    //======================================================================
    
    //#-------------------------------------------------------------------------------
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# numLevels" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //cout << buf << endl;
    
    //out << numLevels << endl;
    in >> numLevels;
    in.get(); // skip enter code.
    //cout << "numLevels:" << numLevels << endl;
    
    saveFilenames = new char *[numLevels];
    
    for (int i = 0; i < numLevels; i++) {
        //out << "# Level #?" << endl;
        in.getline(buf, MAX_LEN_BUF); // skip comment
        
        saveFilenames[i] = new char [MAX_LEN_FILENAME+1];
        in.getline(buf, MAX_LEN_BUF); // read filename
        strncpy(saveFilenames[i], buf, MAX_LEN_FILENAME);
    }
    
    //======================================================================
    // load ending credit
    //======================================================================
    
    //#-------------------------------------------------------------------------------
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "# rowSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << rowSize << endl;
    in >> endingRowSize;
    in.get(); // skip enter code.
    
    //out << "# colSize" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    //out << colSize << endl;
    in >> endingColSize;
    in.get(); // skip enter code.
    
    ending = new char *[endingRowSize];
    
    for (int i = 0; i < endingRowSize; i++) {
        ending[i] = new char [endingColSize+1];
        in.getline(buf, MAX_LEN_BUF); // skip comment
        strncpy(ending[i], buf, endingColSize+1);
    }
    
    in.close();
    
    //======================================================================
    // load first level
    //======================================================================
    showTitle(); // show the campaign title.
    //showEnding(); // show the campaign title.

    currentLevelIndex = 0;
    currentLevel = new Game(saveFilenames[currentLevelIndex]);
    
    return true;
}

void GameManager::loadNextLevel() {
    if (currentLevel != NULL) {
        delete currentLevel;
    }
    currentLevelIndex++;
    currentLevel = new Game(saveFilenames[currentLevelIndex]);
}

void GameManager::loadCurrentLevelAgain() {
    if (currentLevel != NULL) {
        delete currentLevel;
    }
    //currentLevelIndex++; // 다음 레벨이 로드되지 않도록..
    currentLevel = new Game(saveFilenames[currentLevelIndex]);
}

void GameManager::showTitle() {
    if (title) {
        for (int i = 0; i < titleRowSize; i++) {
            cout << title[i] << endl;
        }
        
        while (!_kbhit()) {}
        getchar();
    }
}

void GameManager::showEnding() {
    if (ending) {
        for (int i = 0; i < endingRowSize; i++) {
            cout << ending[i] << endl;
        }
        
        while (!_kbhit()) {}
        getchar();
    }
}
