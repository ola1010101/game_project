#pragma once
#include <memory>
#include <string>
#include "bfs.h"
#include "control.h"
#include "levels.h"
#include "leaderboard.h"
#include "observer.h"

class Menu : public Subject
{
public:
    Menu();
    void run();

private:
    Grid grid_;
    Control control_;
    Leaderboard leaderboard_;
    std::unique_ptr<ILevelSource> source_;

    int totalMoves_;
    int currentLevel_;

    void showMainMenu();
    void showLevelMenu();

    void playCampaign();
    void playSingleLevel(int levelNum);
    void playRandomLevel();

    bool playLevelLoop(bool isRandom, int levelNum);
};