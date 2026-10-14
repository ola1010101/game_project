#pragma once
#include "control.h"
#include "bfs.h"

class MoveCommand 
{
public:
    MoveCommand(Control& ctrl, const Grid& grid, int dx, int dy)
        : ctrl_(ctrl), grid_(grid), dx_(dx), dy_(dy),
        executed_(false), moved_(false) {
    }

    void execute()
    {
        int nx = ctrl_.getX() + dx_;
        int ny = ctrl_.getY() + dy_;
        if (!grid_.inBounds(nx, ny) || grid_.at(nx, ny) == '#') {
            moved_ = false;
            executed_ = true;
            return;
        }
        ctrl_.moveTo(nx, ny);
        moved_ = true;
        executed_ = true;
    }

    void undo()
    {
        if (executed_ && moved_) ctrl_.undo();
    }

    bool moved() const { return moved_; }

private:
    Control& ctrl_;
    const Grid& grid_;
    int dx_, dy_;
    bool executed_;
    bool moved_;
};