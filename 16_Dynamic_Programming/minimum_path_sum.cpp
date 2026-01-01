// Problem : Minimum Path Sum
// LC : https://leetcode.com/problems/minimum-path-sum/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach : Space Optimized DP
// ============================================================
// dp[j] = minimum path sum to reach current cell in column j
// Transition:
// dp[j] = min(from top, from left) + grid[i][j]
//
// Time Complexity  : O(m * n)
// Space Complexity : O(n)
// ============================================================

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        vector<int> prev(n, 0);

        // Initialize first row
        prev[0] = grid[0][0];
        for (int j = 1; j < n; j++) {
            prev[j] = prev[j - 1] + grid[0][j];
        }

        for (int i = 1; i < m; i++) {
            vector<int> temp(n, 0);
            for (int j = 0; j < n; j++) {
                if (j == 0)
                    temp[j] = prev[j] + grid[i][j];
                else
                    temp[j] = min(prev[j], temp[j - 1]) + grid[i][j];
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
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };

    Solution sol;
    cout << "Minimum Path Sum: "
         << sol.minPathSum(grid) << endl;

    return 0;
}
