#include <iostream>
#include <vector>
#include<queue>

using namespace std;

bool isValid(int x, int y, int rows, int cols, const vector<vector<int>>& maze, const vector<vector<bool>>& visited){
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0 && !visited[x][y]);
}

bool bfs(const vector<vector<int>>& maze, pair<int, int> start, pair<int, int> target){
    int rows = maze.size();
    int cols = maze[0].size();

    vector<pair<int, int>> directions {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<pair<int, int>> q;

    q.push(start);
    visited[start.first][start.second] = true;

    while(!q.empty()){
        auto [x, y] = q.front();
        q.pop();

        if(x == target.first && y == target.second){
            return true;
        }

        //обойти соеденение клетки
        for(auto [dx, dy] : directions){
            int newX = x + dx;
            int newY = y + dy;

            if(isValid(newX, newY, rows, cols, maze, visited)){
                visited[newX][newY] = true;
                q.push({newX, newY});
            }
        }
    }
    return false;
}

int main() {
    // Лабиринт: 0 — проходимая клетка, 1 — стена
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0};  // Начальная точка
    pair<int, int> target = {4, 4}; // Целевая точка

    if (bfs(maze, start, target)) {
        cout << "Путь найден!" << endl;
    } else {
        cout << "Путь не существует." << endl;
    }

    return 0;
}