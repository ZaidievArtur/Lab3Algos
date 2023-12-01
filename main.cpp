#include <iostream>
#include <queue>
#include <vector>

#define N 5

bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

std::vector<std::pair<int, int>> findPath(std::vector<std::vector<int>>& matrix, std::pair<int, int> start) {
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(N, false));
    std::vector<std::vector<std::pair<int, int>>> parent(N, std::vector<std::pair<int, int>>(N, { -1, -1 }));
    std::queue<std::pair<int, int>> q;

    q.push(start);
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (matrix[x][y] == 0 && (x == 0 || x == N - 1 || y == 0 || y == N - 1)) {
            std::vector<std::pair<int, int>> path;
            while (x != start.first || y != start.second) {
                path.push_back({ x, y });
                std::pair<int, int> p = parent[x][y];
                x = p.first;
                y = p.second;
            }
            path.push_back(start);
            return path;
        }

        int dx[] = { 1, -1, 0, 0 };
        int dy[] = { 0, 0, 1, -1 };
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (isValid(newX, newY) && !visited[newX][newY] && matrix[newX][newY] == 0) {
                q.push({ newX, newY });
                visited[newX][newY] = true;
                parent[newX][newY] = { x, y };
            }
        }
    }

    return {};
}

int main() {
    std::vector<std::vector<int>> matrix = {
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 1},
            {1, 1, 1, 0, 1},
            {1, 0, 0, 0, 1},
            {0, 1, 1, 1, 1}
    };

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            std::cout << matrix[row][col];
        }
        std::cout << '\n';
    }

    int sx, sy;
    std::cout << "Enter start point indexes:\n";
    std::cin >> sx >> sy;

    if (matrix[sx][sy] == 1) {
        std::cout << "Wall";

        return -1;
    }

    std::vector<std::pair<int, int>> path = findPath(matrix, {sx, sy});
    if (!path.empty()) {
        std::cout << "Shortest path:\n";

        for (int index = path.size() - 1; index >= 0; index--) {
            std::cout << "(" << path[index].first << ", " << path[index].second << ")";

            if (index != 0)
                std::cout << " -> ";
        }
    }
    else {
        std::cout << "No exit\n";
    }

    return 0;
}
