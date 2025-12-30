// Problem : Climbing Stairs
// LC : https://leetcode.com/problems/climbing-stairs/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach 1 : Memoization (Top-Down DP)
// ============================================================
// Idea:
// - From step i, you can come from (i-1) or (i-2)
// - Use recursion + dp[] to avoid recomputation
//
// Time  : O(n)
// Space : O(n) (dp array + recursion stack)
// ============================================================

class SolutionMemo {
private:
    int solve(int n, vector<int>& dp) {
        if (n <= 1) return 1;

        if (dp[n] != -1) return dp[n];

        return dp[n] = solve(n - 1, dp) + solve(n - 2, dp);
    }

public:
    int climbStairs(int n) {
        vector<int> dp(n + 1, -1);
        return solve(n, dp);
    }
};

// ============================================================
// Approach 2 : Space Optimized DP (Bottom-Up)
// ============================================================
// Idea:
// - Same recurrence: dp[i] = dp[i-1] + dp[i-2]
// - Only last two values are needed
//
// Time  : O(n)
// Space : O(1)
// ============================================================

class Solution {
public:
    int climbStairs(int n) {
        int prev1 = 1; // dp[i-1]
        int prev2 = 1; // dp[i-2]

        for (int i = 2; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    int n = 5;

    SolutionMemo sol1;
    Solution sol2;

    cout << "Memoization Answer: " << sol1.climbStairs(n) << endl;
    cout << "Optimized DP Answer: " << sol2.climbStairs(n) << endl;

    return 0;
}
