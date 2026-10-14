#include "bfs.h"
#include <queue>
#include <utility>

bool isReachable(const Grid& g, int sx, int sy, int ex, int ey)
{
    if (!g.inBounds(sx, sy) || !g.inBounds(ex, ey)) return false;
    if (g.at(sx, sy) == '#' || g.at(ex, ey) == '#') return false;

    int H = g.height(), W = g.width();
    std::vector<std::vector<bool>> visited(H, std::vector<bool>(W, false));
    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(sx, sy));
    visited[sy][sx] = true;

    const int dx[] = { 1, -1, 0, 0 };
    const int dy[] = { 0, 0, 1, -1 };

    while (!q.empty())
    {
        std::pair<int, int> c = q.front(); q.pop();
        if (c.first == ex && c.second == ey) return true;

        for (int d = 0; d < 4; ++d) {
            int nx = c.first + dx[d];
            int ny = c.second + dy[d];
            if (g.inBounds(nx, ny) && !visited[ny][nx] && g.at(nx, ny) != '#') {
                visited[ny][nx] = true;
                q.push(std::make_pair(nx, ny));
            }
        }
    }
    return false;
}