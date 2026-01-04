// Problem : Cherry Pickup II
// LC : https://leetcode.com/problems/cherry-pickup-ii/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach 1 : Memoization (Top-Down DP)
// ============================================================
// State: dp[i][j1][j2]
// i   -> current row
// j1  -> column of robot 1
// j2  -> column of robot 2
//
// Time Complexity  : O(rows * cols * cols * 9)
// Space Complexity : O(rows * cols * cols)
// ============================================================

class SolutionMemo {
private:
    int solve(int i, int j1, int j2,
              int rows, int cols,
              vector<vector<int>>& grid,
              vector<vector<vector<int>>>& dp) {

        if (j1 < 0 || j2 < 0 || j1 >= cols || j2 >= cols)
            return -1e8;

        if (i == rows - 1) {
            if (j1 == j2) return grid[i][j1];
            return grid[i][j1] + grid[i][j2];
        }

        if (dp[i][j1][j2] != -1)
            return dp[i][j1][j2];

        int maxi = -1e8;
        for (int d1 = -1; d1 <= 1; d1++) {
            for (int d2 = -1; d2 <= 1; d2++) {
                int val;
                if (j1 == j2)
                    val = grid[i][j1];
                else
                    val = grid[i][j1] + grid[i][j2];

                val += solve(i + 1, j1 + d1, j2 + d2,
                             rows, cols, grid, dp);

                maxi = max(maxi, val);
            }
        }
        return dp[i][j1][j2] = maxi;
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<vector<int>>> dp(
            rows, vector<vector<int>>(cols, vector<int>(cols, -1)));

        return solve(0, 0, cols - 1, rows, cols, grid, dp);
    }
};

// ============================================================
// Approach 2 : Space Optimized Tabulation
// ============================================================
// Uses only next row state
//
// Time Complexity  : O(rows * cols * cols * 9)
// Space Complexity : O(cols * cols)
// ============================================================

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {

        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<int>> front(cols, vector<int>(cols, -1e8));
        front[0][cols - 1] = grid[0][0] + grid[0][cols - 1];

        for (int i = 1; i < rows; i++) {
            vector<vector<int>> curr(cols, vector<int>(cols, -1e8));

            for (int j1 = 0; j1 < cols; j1++) {
                for (int j2 = 0; j2 < cols; j2++) {

                    for (int d1 = -1; d1 <= 1; d1++) {
                        for (int d2 = -1; d2 <= 1; d2++) {

                            int nj1 = j1 + d1;
                            int nj2 = j2 + d2;

                            if (nj1 >= 0 && nj2 >= 0 &&
                                nj1 < cols && nj2 < cols) {

                                int val;
                                if (j1 == j2)
                                    val = grid[i][j1];
                                else
                                    val = grid[i][j1] + grid[i][j2];

                                curr[j1][j2] = max(
                                    curr[j1][j2],
                                    val + front[nj1][nj2]
                                );
                            }
                        }
                    }
                }
            }
            front.swap(curr);
        }

        int ans = 0;
        for (int j1 = 0; j1 < cols; j1++) {
            for (int j2 = 0; j2 < cols; j2++) {
                ans = max(ans, front[j1][j2]);
            }
        }
        return ans;
    }
};

// ============================================================
// Test case
// ============================================================
int main() {

    vector<vector<int>> grid = {
        {3, 1, 1},
        {2, 5, 1},
        {1, 5, 5},
        {2, 1, 1}
    };

    SolutionMemo sol1;
    Solution sol2;

    cout << "Memoization Answer: "
         << sol1.cherryPickup(grid) << endl;

    cout << "Space Optimized Answer: "
         << sol2.cherryPickup(grid) << endl;

    return 0;
}
