// Problem : Path With Minimum Effort (Dijkstra on Grid)
// LC : https://leetcode.com/problems/path-with-minimum-effort/

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------
// Approach:
// Modified Dijkstra on a 2D grid.
// Instead of summing weights, each move cost = abs(height difference).
// The "effort" of a path is the maximum edge weight along that path.
// For every neighbor cell:
//      new_effort = max(curr_effort, abs(h[r][c] - h[nr][nc]))
// Relax the effort if we find a better (smaller) one.
//
// Use a min-heap storing {effort, {row, col}}.
// Dijkstra guarantees the first time we reach (rows-1, cols-1)
// is the minimum effort path.
// --------------------------------------------

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();

        vector<vector<int>> dist(rows, vector<int>(cols, -1));

        priority_queue<
            pair<int, pair<int,int>>,
            vector<pair<int, pair<int,int>>>,
            greater<pair<int, pair<int,int>>>
        > pq;

        pq.push({0, {0, 0}});
        dist[0][0] = 0;

        int dir[4][2] = {
            {-1,0}, {0,1}, {1,0}, {0,-1}
        };

        while (!pq.empty()) {
            auto [curr_effort, cell] = pq.top();
            pq.pop();

            int r = cell.first;
            int c = cell.second;

            for (auto &d : dir) {
                int nr = r + d[0];
                int nc = c + d[1];

                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {

                    int edgeWeight = abs(heights[r][c] - heights[nr][nc]);
                    int new_effort = max(curr_effort, edgeWeight);

                    if (dist[nr][nc] == -1 || dist[nr][nc] > new_effort) {
                        dist[nr][nc] = new_effort;
                        pq.push({new_effort, {nr, nc}});
                    }
                }
            }
        }

        return dist[rows - 1][cols - 1];
    }
};

// --------------------------------------------
// Test case
// --------------------------------------------
int main() {
    Solution sol;

    vector<vector<int>> heights = {
        {1, 2, 2},
        {3, 8, 2},
        {5, 3, 5}
    };

    int ans = sol.minimumEffortPath(heights);
    cout << "Minimum Effort: " << ans << endl;

    return 0;
}
