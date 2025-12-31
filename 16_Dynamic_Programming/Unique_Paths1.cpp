// Problem : Unique Paths
// LC : https://leetcode.com/problems/unique-paths/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach 1 : Memoization (Top-Down DP)
// ============================================================
// dp[i][j] = number of ways to reach cell (i, j)
// From (i, j) you can come from:
// - (i-1, j)
// - (i, j-1)
//
// Time Complexity  : O(m * n)
// Space Complexity : O(m * n) + recursion stack
// ============================================================

class SolutionMemo {
private:
    int solve(int i, int j, vector<vector<int>>& dp) {
        if (i == 0 || j == 0) return dp[i][j] = 1;
        if (dp[i][j] != -1) return dp[i][j];

        return dp[i][j] =
            solve(i - 1, j, dp) + solve(i, j - 1, dp);
    }

public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return solve(m - 1, n - 1, dp);
    }
};

// ============================================================
// Approach 2 : Tabulation (Bottom-Up DP)
// ============================================================
// Time Complexity  : O(m * n)
// Space Complexity : O(m * n)
// ============================================================

class SolutionTabulation {
public:
    int uniquePaths(int m, int n) {

        vector<vector<int>> dp(m, vector<int>(n, 0));

        // Base cases
        for (int i = 0; i < m; i++) dp[i][0] = 1;
        for (int j = 0; j < n; j++) dp[0][j] = 1;

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};

// ============================================================
// Approach 3 : Space Optimized DP
// ============================================================
// Uses only previous row
//
// Time Complexity  : O(m * n)
// Space Complexity : O(n)
// ============================================================

class Solution {
public:
    int uniquePaths(int m, int n) {

        vector<int> prev(n, 1);

        for (int i = 1; i < m; i++) {
            vector<int> temp(n, 0);
            temp[0] = 1;
            for (int j = 1; j < n; j++) {
                temp[j] = temp[j - 1] + prev[j];
            }
            prev = temp;
        }
        return prev[n - 1];
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    int m = 3, n = 7;

    SolutionMemo sol1;
    SolutionTabulation sol2;
    Solution sol3;

    cout << "Memoization Answer: "
         << sol1.uniquePaths(m, n) << endl;

    cout << "Tabulation Answer: "
         << sol2.uniquePaths(m, n) << endl;

    cout << "Space Optimized Answer: "
         << sol3.uniquePaths(m, n) << endl;

    return 0;
}
