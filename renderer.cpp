#include "renderer.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

static WORD colorCode(Color c)
{
    switch (c) {
    case Color::White:   return 7;
    case Color::Gray:    return 8;
    case Color::Blue:    return 9;
    case Color::Cyan:    return 11;
    case Color::Green:   return 10;
    case Color::Yellow:  return 14;
    case Color::Red:     return 12;
    case Color::Magenta: return 13;
    }
    return 7;
}

void Renderer::setColor(Color c)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, colorCode(c));
}

void Renderer::hideCursor()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(h, &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo(h, &info);
}

void Renderer::showCursor() 
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(h, &info);
    info.bVisible = TRUE;
    SetConsoleCursorInfo(h, &info);
}

void Renderer::gotoxy(int x, int y) 
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = (SHORT)x;
    pos.Y = (SHORT)y;
    SetConsoleCursorPosition(h, pos);
}

void Renderer::clearScreen() 
{   
    //  system("cls")
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h, &csbi);

    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD written;
    COORD home = { 0, 0 };

    FillConsoleOutputCharacter(h, ' ', cellCount, home, &written);
    FillConsoleOutputAttribute(h, csbi.wAttributes, cellCount, home, &written);
    SetConsoleCursorPosition(h, home);
}

void Renderer::drawCell(int cellX, int cellY, char content) 
{
    gotoxy(screenX(cellX), screenY(cellY));

    switch (content) {
    case '#':
        setColor(Color::Blue);
        std::cout << "[]";
        break;
    case 'E':
        setColor(Color::Green);
        std::cout << "X ";
        break;
    case 'O':
        setColor(Color::Yellow);
        std::cout << "()";
        break;
    default:                    
        setColor(Color::White);
        std::cout << "  ";
        break;
    }
    setColor(Color::White);
}

void Renderer::drawFullMaze(const Grid& g, int heroX, int heroY,
    int moves, int level, bool isRandom) 
{
    clearScreen();

    gotoxy(0, 0);
    setColor(Color::White);
    std::cout << "=== ЛАБИРИНТ - Уровень " << level;
    if (isRandom) std::cout << " (случайный)";
    std::cout << " ===";

    gotoxy(0, MOVES_ROW);
    std::cout << "Ходов: " << moves << "  ";

    for (int y = 0; y < g.height(); ++y) {
        for (int x = 0; x < g.width(); ++x) {
            if (x == heroX && y == heroY)      drawCell(x, y, 'O');
            else if (g.at(x, y) == '#')        drawCell(x, y, '#');
            else if (g.at(x, y) == 'E')        drawCell(x, y, 'E');
            else                                drawCell(x, y, ' ');
        }
    }

    gotoxy(0, screenY(g.height()) + 1);
    setColor(Color::Gray);
    std::cout << "Выход: X | WASD - движение, U - отмена, "
        "R - рестарт, Q - выход";
    setColor(Color::White);
}

void Renderer::updateHeroMove(const Grid& g,
    int oldX, int oldY,
    int newX, int newY,
    int moves) {
    char oldContent = g.at(oldX, oldY);
    if (oldContent == 'E') drawCell(oldX, oldY, 'E');
    else                    drawCell(oldX, oldY, ' ');

    
    drawCell(newX, newY, ' O');

    gotoxy(MOVES_COL, MOVES_ROW);
    setColor(Color::White);
    std::cout << moves << "   ";
}

void Renderer::drawLevelComplete(int level, int moves, bool isRandom)
{
    clearScreen();
    setColor(Color::Green);
    std::cout << "==========================================\n";
    std::cout << "           УРОВЕНЬ ПРОЙДЕН!\n";
    std::cout << "==========================================\n";

    setColor(Color::White);
    if (isRandom)
        std::cout << "Случайный уровень пройден!\n";
    else
        std::cout << "Уровень " << level << " пройден!\n";
    std::cout << "Затрачено ходов: " << moves << "\n";

    setColor(Color::Gray);
    std::cout << "\nНажмите любую клавишу...";
    setColor(Color::White);
    system("pause");
}

void Renderer::drawGameOver(int totalMoves)
{
    clearScreen();
    setColor(Color::Yellow);
    std::cout << "*** ПОЗДРАВЛЯЕМ! ВЫ ПРОШЛИ ВСЕ УРОВНИ! ***\n";
    setColor(Color::White);
    std::cout << "Общее число ходов: " << totalMoves << "\n";
}

void Renderer::drawTitle(const char* title)
{
    setColor(Color::Cyan);
    std::cout << title << "\n";
    setColor(Color::White);
}