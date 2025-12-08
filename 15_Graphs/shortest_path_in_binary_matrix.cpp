// Problem : Shortest Path in Binary Matrix (8-direction BFS)
// LC : https://leetcode.com/problems/shortest-path-in-binary-matrix/

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------
// Approach:
// Use BFS since every move has equal weight (1).
// 1. If start (0,0) is blocked → return -1.
// 2. Maintain dist[][] initialized to -1.
// 3. BFS queue stores {{row, col}, distance}.
// 4. Explore all 8 directions; if a cell is valid, open (0), and
//    either unvisited or found a shorter path, update it and push to queue.
// 5. BFS ensures shortest distance when edges have unit weight.
// 6. Answer is dist[n-1][n-1], or -1 if unreachable.
// --------------------------------------------

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<pair<int,int>, int>> q;

        if (grid[0][0] == 0) {
            dist[0][0] = 1;
            q.push({{0, 0}, 1});
        }

        int dir[8][2] = {
            {-1, 0}, {-1, 1}, {0, 1},  {1, 1},
            {1, 0},  {1, -1}, {0, -1}, {-1, -1}
        };

        while (!q.empty()) {
            auto [cell, d] = q.front();
            q.pop();

            int r = cell.first;
            int c = cell.second;

            for (auto &v : dir) {
                int nr = r + v[0];
                int nc = c + v[1];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    if (grid[nr][nc] == 0) {
                        if (dist[nr][nc] == -1 || dist[nr][nc] > d + 1) {
                            dist[nr][nc] = d + 1;
                            q.push({{nr, nc}, d + 1});
                        }
                    }
                }
            }
        }

        return dist[n - 1][n - 1];
    }
};

// --------------------------------------------
// Test case
// --------------------------------------------
int main() {
    Solution sol;

    vector<vector<int>> grid = {
        {0, 1},
        {1, 0}
    };

    int ans = sol.shortestPathBinaryMatrix(grid);
    cout << "Shortest Path: " << ans << endl;

    return 0;
}
