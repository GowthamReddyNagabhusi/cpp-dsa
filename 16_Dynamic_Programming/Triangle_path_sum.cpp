// Problem : Triangle (Minimum Path Sum)
// LC : https://leetcode.com/problems/triangle/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach 1 : Memoization (Top-Down DP)
// ============================================================
// dp[i][j] = minimum path sum to reach (i, j)
//
// Time Complexity  : O(n^2)
// Space Complexity : O(n^2) + recursion stack
// ============================================================

class SolutionMemo {
private:
    vector<vector<int>> dp;
    vector<vector<bool>> vis;

    int solve(int row, int col, vector<vector<int>>& t) {
        if (row == 0 && col == 0)
            return t[0][0];

        if (vis[row][col])
            return dp[row][col];

        int res;
        if (col == 0)
            res = t[row][col] + solve(row - 1, col, t);
        else if (col == row)
            res = t[row][col] + solve(row - 1, col - 1, t);
        else
            res = t[row][col] +
                  min(solve(row - 1, col, t),
                      solve(row - 1, col - 1, t));

        vis[row][col] = true;
        return dp[row][col] = res;
    }

public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        dp.assign(n, vector<int>(n, 0));
        vis.assign(n, vector<bool>(n, false));

        int ans = INT_MAX;
        for (int j = 0; j < n; j++) {
            ans = min(ans, solve(n - 1, j, triangle));
        }
        return ans;
    }
};

// ============================================================
// Approach 2 : Space Optimized DP (Bottom-Up)
// ============================================================
// Uses only previous row
//
// Time Complexity  : O(n^2)
// Space Complexity : O(n)
// ============================================================

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {

        int n = triangle.size();
        vector<int> prev(n, 0), cur(n, 0);

        prev[0] = triangle[0][0];

        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0)
                    cur[j] = triangle[i][j] + prev[j];
                else if (j == i)
                    cur[j] = triangle[i][j] + prev[j - 1];
                else
                    cur[j] = triangle[i][j] +
                             min(prev[j], prev[j - 1]);
            }
            prev.swap(cur);
        }

        return *min_element(prev.begin(), prev.begin() + n);
    }
};

// ============================================================
// Test case
// ============================================================
int main() {

    vector<vector<int>> triangle = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };

    SolutionMemo sol1;
    Solution sol2;

    cout << "Memoization Answer: "
         << sol1.minimumTotal(triangle) << endl;

    cout << "Space Optimized Answer: "
         << sol2.minimumTotal(triangle) << endl;

    return 0;
}
