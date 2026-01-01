// Problem : Unique Paths II
// LC : https://leetcode.com/problems/unique-paths-ii/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach : Space Optimized DP
// ============================================================
// dp[j] = number of ways to reach current cell in column j
// If obstacle → dp[j] = 0
//
// Time Complexity  : O(m * n)
// Space Complexity : O(n)
// ============================================================

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        vector<int> prev(n, 0);

        // Initialize first row
        for (int j = 0; j < n; j++) {
            if (grid[0][j] == 1) break;
            prev[j] = 1;
        }

        for (int i = 1; i < m; i++) {
            vector<int> temp(n, 0);

            // First column
            if (grid[i][0] == 0)
                temp[0] = prev[0];

            for (int j = 1; j < n; j++) {
                if (grid[i][j] == 0) {
                    temp[j] = prev[j] + temp[j - 1];
                }
            }
            prev.swap(temp);
        }

        return prev[n - 1];
    }
};

// ============================================================
// Test case
// ============================================================
int main() {

    vector<vector<int>> grid = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    Solution sol;
    cout << "Unique Paths: "
         << sol.uniquePathsWithObstacles(grid) << endl;

    return 0;
}
