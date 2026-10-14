#pragma once
#include <string>
#include <vector>
#include "bfs.h"

class ILevelSource 
{
public:
    virtual ~ILevelSource() {}
    virtual std::pair<int, int> load(Grid& grid, int levelNum) = 0;
    virtual bool isRandom() const { return false; }
    virtual int totalLevels() const { return 1; }
};

class BuiltinLevels : public ILevelSource
{
public:
    std::pair<int, int> load(Grid& grid, int levelNum);
    int totalLevels() const { return 5; }
};