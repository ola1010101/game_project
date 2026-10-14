#pragma once
#include <string>
#include <vector>

struct PlayerScore 
{
    std::string name;
    int totalMoves;
    int levelsCompleted;
};

class Leaderboard 
{
public:
    explicit Leaderboard(const std::string& file = "leaderboard.txt");
    void add(const std::string& name, int moves, int levels);
    void show() const;

private:
    std::vector<PlayerScore> scores_;
    std::string file_;
    static const size_t MAX_ENTRIES = 10;

    void load();
    void save() const;
    void sortByMoves();
};