// Problem : Frog Jump (Minimum Cost)
// GFG / DP Classic

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach 1 : Memoization (Top-Down DP)
// ============================================================
// Idea:
// - Frog at index i can come from:
//   1) i-1
//   2) i-2
// - Cost = abs(height difference)
//
// Recurrence:
// dp[i] = min(
//     dp[i-1] + abs(h[i] - h[i-1]),
//     dp[i-2] + abs(h[i] - h[i-2])
// )
//
// Time  : O(n)
// Space : O(n) (dp array + recursion stack)
// ============================================================

class SolutionMemo {
private:
    int solve(int i, vector<int>& height, vector<int>& dp) {
        if (i == 0) return 0;
        if (i == 1) return abs(height[1] - height[0]);

        if (dp[i] != -1) return dp[i];

        int one = solve(i - 1, height, dp) +
                  abs(height[i] - height[i - 1]);
        int two = solve(i - 2, height, dp) +
                  abs(height[i] - height[i - 2]);

        return dp[i] = min(one, two);
    }

public:
    int minCost(vector<int>& height) {
        int n = height.size();
        vector<int> dp(n, -1);
        return solve(n - 1, height, dp);
    }
};

// ============================================================
// Approach 2 : Space Optimized DP (Bottom-Up)
// ============================================================
// Idea:
// - Same recurrence
// - Only last two states needed
//
// Time  : O(n)
// Space : O(1)
// ============================================================

class Solution {
public:
    int minCost(vector<int>& height) {
        int n = height.size();
        if (n <= 1) return 0;

        int cost2 = 0; // dp[i-2]
        int cost1 = abs(height[1] - height[0]); // dp[i-1]

        for (int i = 2; i < n; i++) {
            int curr = min(
                cost1 + abs(height[i] - height[i - 1]),
                cost2 + abs(height[i] - height[i - 2])
            );
            cost2 = cost1;
            cost1 = curr;
        }
        return cost1;
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    vector<int> height = {10, 20, 30, 10};

    SolutionMemo sol1;
    Solution sol2;

    cout << "Memoization Answer: "
         << sol1.minCost(height) << endl;

    cout << "Optimized DP Answer: "
         << sol2.minCost(height) << endl;

    return 0;
}
