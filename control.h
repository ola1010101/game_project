#pragma once
#include <vector>
#include <utility>
#include <string>

class Control 
{
public:
    Control();

    void reset(int x, int y);
    void moveTo(int x, int y);
    bool undo();

    int getX() const { return x_; }
    int getY() const { return y_; }
    int getMoves() const { return moves_; }
    void resetMoves() { moves_ = 0; history_.clear(); }

    static bool parseMove(char key, int& dx, int& dy);

    static bool isUndo(char key);
    static bool isRestart(char key);
    static bool isQuit(char key);

private:
    int x_, y_;
    int moves_;
    std::vector<std::pair<int, int>> history_;
};