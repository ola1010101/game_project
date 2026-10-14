#include "leaderboard.h"
#include "renderer.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <conio.h>

Leaderboard::Leaderboard(const std::string& file) : file_(file) 
{
    load();
}

void Leaderboard::load()
{
    scores_.clear();
    std::ifstream f(file_.c_str());
    if (!f) return;
    PlayerScore s;
    while (f >> s.name >> s.totalMoves >> s.levelsCompleted)
        scores_.push_back(s);
    sortByMoves();
}

void Leaderboard::save() const 
{
    std::ofstream f(file_.c_str());
    if (!f) return;
    for (size_t i = 0; i < scores_.size(); ++i)
        f << scores_[i].name << ' '
        << scores_[i].totalMoves << ' '
        << scores_[i].levelsCompleted << '\n';
}

void Leaderboard::sortByMoves() 
{
    std::sort(scores_.begin(), scores_.end(),
        [](const PlayerScore& a, const PlayerScore& b) {
            return a.totalMoves < b.totalMoves;
        });
}

void Leaderboard::add(const std::string& name, int moves, int levels)
{
    PlayerScore s;
    s.name = name;
    s.totalMoves = moves;
    s.levelsCompleted = levels;
    scores_.push_back(s);
    sortByMoves();
    if (scores_.size() > MAX_ENTRIES) scores_.resize(MAX_ENTRIES);
    save();
}

void Leaderboard::show() const
{
    Renderer::clearScreen();
    Renderer::setColor(Color::Cyan);
    std::cout << "=== ТАБЛИЦА ЛИДЕРОВ ===\n";
    Renderer::setColor(Color::Gray);
    std::cout << "(только для полного прохождения 5 уровней)\n";
    Renderer::setColor(Color::White);
    std::cout << "==================================\n";

    if (scores_.empty()) {
        std::cout << "Пока нет результатов!\n";
    }
    else {
        std::cout << "Место  Имя          Ходов  Уровни\n";
        std::cout << "----------------------------------\n";
        for (size_t i = 0; i < scores_.size(); ++i) {
            std::cout << " " << (i + 1) << "     " << scores_[i].name;
            for (size_t j = scores_[i].name.length(); j < 10; ++j)
                std::cout << ' ';
            std::cout << scores_[i].totalMoves << "     "
                << scores_[i].levelsCompleted << "/5\n";
        }
    }

    Renderer::setColor(Color::Gray);
    std::cout << "\nНажмите любую клавишу...";
    Renderer::setColor(Color::White);
    _getch();
}