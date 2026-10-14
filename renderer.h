#pragma once
#include "bfs.h"

enum class Color 
{
    White, Gray, Blue, Cyan, Green, Yellow, Red, Magenta
};

class Renderer 
{
public:
    static void hideCursor();
    static void showCursor();
    static void gotoxy(int x, int y);
    static void setColor(Color c);
    static void clearScreen();

    static void drawFullMaze(const Grid& g, int heroX, int heroY,
        int moves, int level, bool isRandom);

    static void updateHeroMove(const Grid& g,
        int oldX, int oldY,
        int newX, int newY,
        int moves);

    static void drawLevelComplete(int level, int moves, bool isRandom);
    static void drawGameOver(int totalMoves);
    static void drawTitle(const char* title);

    static const int CELL_OFFSET_X = 0;
    static const int CELL_OFFSET_Y = 4;  


private:
   
    static void drawCell(int cellX, int cellY, char content);

    static int screenX(int cellX) { return CELL_OFFSET_X + cellX * 2; }
    static int screenY(int cellY) { return CELL_OFFSET_Y + cellY; }

    static const int MOVES_ROW = 2;
    static const int MOVES_COL = 7;   
};