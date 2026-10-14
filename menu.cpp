#include "menu.h"
#include "renderer.h"
#include "command.h"
#include "random_gen.h"
#include <iostream>
#include <conio.h>

Menu::Menu()
    : leaderboard_("leaderboard.txt"),
    totalMoves_(0), currentLevel_(1) {
}

void Menu::run() { showMainMenu(); }

void Menu::showMainMenu() 
{
    while (true) {
        Renderer::clearScreen();
        Renderer::drawTitle("=== ГЛАВНОЕ МЕНЮ ===");
        std::cout << "1. Начать игру (5 уровней)\n";
        std::cout << "2. Выбор уровня\n";
        std::cout << "3. Таблица лидеров\n";
        std::cout << "4. Выход\n";
        std::cout << "Выберите: ";

        char c = _getch();
        if (c == '1') playCampaign();
        else if (c == '2') showLevelMenu();
        else if (c == '3') leaderboard_.show();
        else if (c == '4') return;
    }
}

void Menu::showLevelMenu()
{
    while (true) {
        Renderer::clearScreen();
        Renderer::drawTitle("=== ВЫБОР УРОВНЯ ===");
        std::cout << "1-5. Уровни 1-5\n";
        std::cout << "6. Случайный уровень\n";
        std::cout << "0. Назад\n";
        std::cout << "Выберите: ";

        char c = _getch();
        if (c >= '1' && c <= '5') { playSingleLevel(c - '0'); return; }
        if (c == '6') { playRandomLevel(); return; }
        if (c == '0') return;
    }
}

bool Menu::playLevelLoop(bool isRandom, int levelNum)
{
    
    Renderer::drawFullMaze(grid_, control_.getX(), control_.getY(),
        control_.getMoves(), levelNum, isRandom);

    while (true)
    {
        
        if (grid_.at(control_.getX(), control_.getY()) == 'E') {
            Renderer::drawLevelComplete(levelNum, control_.getMoves(), isRandom);
            
            Renderer::clearScreen();
            return true;
        }

        Renderer::gotoxy(0, Renderer::CELL_OFFSET_Y + grid_.height() + 3);
        std::cout << "Ваш ход:  ";

        char key = _getch();

        if (Control::isQuit(key))
        {
            Renderer::clearScreen();
            return false;
        }

        if (Control::isUndo(key))
        {
            int oldX = control_.getX();
            int oldY = control_.getY();
            if (control_.undo()) {
                Renderer::updateHeroMove(grid_,
                    oldX, oldY,
                    control_.getX(), control_.getY(),
                    control_.getMoves());
            }
            continue;
        }

        if (Control::isRestart(key))
        {
            std::pair<int, int> start = source_->load(grid_, levelNum);
            control_.reset(start.first, start.second);
            Renderer::drawFullMaze(grid_, control_.getX(), control_.getY(),
                control_.getMoves(), levelNum, isRandom);
            continue;
        }

        int dx = 0, dy = 0;
        if (!Control::parseMove(key, dx, dy)) continue;

        int oldX = control_.getX();
        int oldY = control_.getY();

        MoveCommand cmd(control_, grid_, dx, dy);
        cmd.execute();

        if (cmd.moved())
        {
            Renderer::updateHeroMove(grid_,
                oldX, oldY,
                control_.getX(), control_.getY(),
                control_.getMoves());
            notifyMove(control_.getX(), control_.getY(), control_.getMoves());
        }
    }
}

void Menu::playCampaign() 
{
    source_.reset(new BuiltinLevels());
    totalMoves_ = 0;

    for (int lvl = 1; lvl <= 5; ++lvl)
    {
        std::pair<int, int> start = source_->load(grid_, lvl);
        control_.reset(start.first, start.second);
        currentLevel_ = lvl;

        if (!playLevelLoop(false, lvl)) return;

        notifyLevelComplete(lvl, control_.getMoves());
        totalMoves_ += control_.getMoves();
    }

    notifyGameComplete(totalMoves_);
    Renderer::drawGameOver(totalMoves_);

    std::cout << "\nВведите имя для таблицы лидеров: ";
    std::string name;
    std::cin >> name;
    std::cin.ignore(10000, '\n');

    leaderboard_.add(name, totalMoves_, 5);
    std::cout << "Результат сохранён! ";
    system("pause");
}

void Menu::playSingleLevel(int levelNum)
{
    source_.reset(new BuiltinLevels());
    std::pair<int, int> start = source_->load(grid_, levelNum);
    control_.reset(start.first, start.second);
    currentLevel_ = levelNum;

    playLevelLoop(false, levelNum);
}

void Menu::playRandomLevel()
{
    source_.reset(new RandomGenerator(20, 15, 3));
    std::pair<int, int> start = source_->load(grid_, 1);
    control_.reset(start.first, start.second);
    currentLevel_ = 1;

    playLevelLoop(true, 1);
}