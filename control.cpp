#include "control.h"

Control::Control() : x_(1), y_(1), moves_(0) {}

void Control::reset(int x, int y) 
{
    x_ = x; y_ = y;
    moves_ = 0;
    history_.clear();
}

void Control::moveTo(int x, int y) 
{
    history_.push_back(std::make_pair(x_, y_));
    x_ = x; y_ = y;
    ++moves_;
}

bool Control::undo() 
{
    if (history_.empty()) return false;
    std::pair<int, int> p = history_.back();
    history_.pop_back();
    x_ = p.first;
    y_ = p.second;
    if (moves_ > 0) --moves_;
    return true;
}

bool Control::parseMove(char key, int& dx, int& dy) {
    dx = dy = 0;
    switch (key)
    {
    case 'w': case 'W': case 'ö': case 'Ö': dy = -1; return true;
    case 's': case 'S': case 'û': case 'Û': dy = 1; return true;
    case 'a': case 'A': case 'ô': case 'Ô': dx = -1; return true;
    case 'd': case 'D': case 'à': case 'À': dx = 1; return true;
    }
    return false;
}

bool Control::isUndo(char k) { return k == 'u' || k == 'U'; }
bool Control::isRestart(char k) { return k == 'r' || k == 'R'; }
bool Control::isQuit(char k) { return k == 'q' || k == 'Q'; }