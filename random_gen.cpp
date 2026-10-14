#include "random_gen.h"
#include <cstdlib>

std::pair<int, int> RandomGenerator::load(Grid& grid, int ) 
{
    int wallChance = 25 + difficulty_ * 5;
    if (wallChance > 50) wallChance = 50;

    const int exitX = width_ - 2;
    const int exitY = height_ - 2;
    const int MAX_ATTEMPTS = 50;

    for (int attempt = 0; attempt < MAX_ATTEMPTS; ++attempt) {
        Grid local;
        local.cells.assign(height_, std::string(width_, ' '));

        for (int y = 0; y < height_; ++y) {
            for (int x = 0; x < width_; ++x) {
                bool border = (y == 0 || y == height_ - 1
                    || x == 0 || x == width_ - 1);
                if (border) { local.cells[y][x] = '#'; continue; }

                bool nearStart = (x <= 3 && y <= 3);
                bool isExitCell = (x == exitX && y == exitY);

                if (nearStart || isExitCell)
                    local.cells[y][x] = ' ';
                else
                    local.cells[y][x] = (rand() % 100 < wallChance) ? '#' : ' ';
            }
        }

        local.cells[1][1] = ' ';
        local.cells[exitY][exitX] = 'E';

        if (isReachable(local, 1, 1, exitX, exitY)) {
            grid = local;
            return std::make_pair(1, 1);
        }
    }

    grid.cells.assign(height_, std::string(width_, ' '));
    for (int y = 0; y < height_; ++y)
        for (int x = 0; x < width_; ++x)
            grid.cells[y][x] =
            (y == 0 || y == height_ - 1 || x == 0 || x == width_ - 1)
            ? '#' : ' ';
    grid.cells[exitY][exitX] = 'E';
    return std::make_pair(1, 1);
}