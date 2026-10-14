#pragma once
#include <utility>
#include "levels.h"


class RandomGenerator : public ILevelSource 
{
public:
    RandomGenerator(int width, int height, int difficulty)
        : width_(width), height_(height), difficulty_(difficulty) {
    }

    std::pair<int, int> load(Grid& grid, int levelNum);
    bool isRandom() const { return true; }

private:
    int width_, height_, difficulty_;
};