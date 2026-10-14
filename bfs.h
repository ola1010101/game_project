#pragma once
#include <string>
#include <vector>

struct Grid 
{
    std::vector<std::string> cells;
    int width()  const { return cells.empty() ? 0 : (int)cells[0].size(); }
    int height() const { return (int)cells.size(); }
    bool inBounds(int x, int y) const {
        return y >= 0 && y < height() && x >= 0 && x < (int)cells[y].size();
    }
    char at(int x, int y) const {
        return inBounds(x, y) ? cells[y][x] : '#';
    }
};

bool isReachable(const Grid& g, int sx, int sy, int ex, int ey);