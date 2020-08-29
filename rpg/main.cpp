#include <iostream>

using namespace std;

#include "game_manager.h"

// 캠페인의 main()
int main() {
    srand((unsigned)time(NULL));
    
    GameManager *gameManager = new GameManager();
    gameManager->play();
    delete gameManager;
    
    return 0;
}
