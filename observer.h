#pragma once
#include <vector>
#include <algorithm>

class IGameObserver 
{
public:
    virtual ~IGameObserver() {}
    virtual void onMove(int, int, int) {}
    virtual void onLevelComplete(int, int ) {}
    virtual void onGameComplete(int) {}
};

class Subject 
{
public:
    void attach(IGameObserver* obs) { observers_.push_back(obs); }
    void detach(IGameObserver* obs) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), obs),
            observers_.end());
    }

protected:
    void notifyMove(int x, int y, int m) {
        for (size_t i = 0; i < observers_.size(); ++i)
            observers_[i]->onMove(x, y, m);
    }
    void notifyLevelComplete(int lvl, int m) {
        for (size_t i = 0; i < observers_.size(); ++i)
            observers_[i]->onLevelComplete(lvl, m);
    }
    void notifyGameComplete(int m) {
        for (size_t i = 0; i < observers_.size(); ++i)
            observers_[i]->onGameComplete(m);
    }

private:
    std::vector<IGameObserver*> observers_;
};


class StatsObserver : public IGameObserver 
{
public:
    void onMove(int, int, int) override { ++moves_; }
    void onLevelComplete(int lvl, int) override { level_ = lvl; }
    void onGameComplete(int total) override { total_ = total; }
    int movesCount() const { return moves_; }
    int lastLevel() const { return level_; }
    int finalTotal() const { return total_; }
private:
    int moves_ = 0, level_ = 0, total_ = 0;
};