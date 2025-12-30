// Problem : Frog Jump with K Steps
// GFG / DP Classic

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach : DP (Bottom-Up)
// ============================================================
// dp[i] = minimum cost to reach stone i
// From i, frog can jump to any of the previous k stones
// ============================================================

// Time Complexity  : O(n * k)
// Space Complexity : O(n)


class Solution {
public:
    int minimizeCost(int n, int k, vector<int>& height) {
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                if (i - j >= 0) {
                    dp[i] = min(dp[i],
                        dp[i - j] + abs(height[i] - height[i - j]));
                }
            }
        }
        return dp[n - 1];
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    vector<int> height = {10, 30, 40, 50, 20};
    int n = height.size(), k = 3;

    Solution sol;
    cout << "Minimum Cost: "
         << sol.minimizeCost(n, k, height) << endl;

    return 0;
}
