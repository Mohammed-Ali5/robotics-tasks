#include <iostream>
#include <vector>
#include <stack>

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

// Function to perform Depth-First Search
bool dfs(vector<vector<char>>& grid, pair<int, int> current, const pair<int, int>& end) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Mark the current cell as visited
    grid[current.first][current.second] = '*';

    // Define possible movements (up, down, left, right)
    vector<pair<int, int>> movements = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (const auto& move : movements) {
        int newRow = current.first + move.first;
        int newCol = current.second + move.second;

        // Check if the new position is within bounds and not visited
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
            grid[newRow][newCol] == 'E') {
            return true;  // Found the end point
        }

        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
            grid[newRow][newCol] == '0') {
            if (dfs(grid, make_pair(newRow, newCol), end)) {
                return true;  // Found a path
            }
        }
    }

    return false;  // No path found
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

    // Perform DFS to find a path
    if (dfs(mazeGrid, startPoint, endPoint)) {
        cout << "Path found:" << endl;
        printGrid(mazeGrid);
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
