#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// Function to print the grid
void printGrid(const vector<vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to perform Breadth-First Search
vector<pair<int, int>> bfs(const vector<vector<char>>& grid, pair<int, int> start, pair<int, int> end) {
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, make_pair(-1, -1)));

    queue<pair<int, int>> q;
    q.push(start);
    visited[start.first][start.second] = true;

    // Define possible movements (up, down, left, right)
    vector<pair<int, int>> movements = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();

        for (const auto& move : movements) {
            int newRow = current.first + move.first;
            int newCol = current.second + move.second;

            // Check if the new position is within bounds and not visited
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                !visited[newRow][newCol] && grid[newRow][newCol] != 'X') {
                visited[newRow][newCol] = true;
                q.push(make_pair(newRow, newCol));

                // If the destination is reached, reconstruct the path
                if (make_pair(newRow, newCol) == end) {
                    vector<pair<int, int>> path;
                    while (current != start) {
                        path.push_back(current);
                        current = parent[current.first][current.second];
                    }
                    path.push_back(start);
                    reverse(path.begin(), path.end());
                    return path;
                }

                // Update parent for backtracking
                parent[newRow][newCol] = current;
            }
        }
    }

    return {};  // No path found
}

int main() {
    // Define the maze grid
    vector<vector<char>> mazeGrid = {
        {'S', '0', '0', '0', '0'},
        {'0', 'X', 'X', '0', 'X'},
        {'0', '0', '0', '0', '0'},
        {'X', '0', 'X', 'X', '0'},
        {'0', '0', '0', '0', 'E'},
    };

    // Find start and end points
    pair<int, int> startPoint, endPoint;
    for (int i = 0; i < mazeGrid.size(); ++i) {
        for (int j = 0; j < mazeGrid[i].size(); ++j) {
            if (mazeGrid[i][j] == 'S') {
                startPoint = make_pair(i, j);
            } else if (mazeGrid[i][j] == 'E') {
                endPoint = make_pair(i, j);
            }
        }
    }

    // Perform BFS to find the shortest path
    vector<pair<int, int>> shortestPath = bfs(mazeGrid, startPoint, endPoint);

    // Print the result
    if (!shortestPath.empty()) {
        cout << "Shortest Path:" << endl;
        for (const auto& step : shortestPath) {
            mazeGrid[step.first][step.second] = '*';
        }
        printGrid(mazeGrid);
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
