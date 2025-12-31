// Problem : House Robber
// LC : https://leetcode.com/problems/house-robber/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach 1 : Memoization (Top-Down DP)
// ============================================================
// dp[i] = maximum money that can be robbed till index i
// Choice:
// - Rob current house → dp[i-2] + nums[i]
// - Skip current house → dp[i-1]
//
// Time Complexity  : O(n)
// Space Complexity : O(n) (dp array + recursion stack)
// ============================================================

class SolutionMemo {
private:
    int solve(int i, vector<int>& nums, vector<int>& dp) {
        if (i < 0) return 0;
        if (i == 0) return nums[0];

        if (dp[i] != -1) return dp[i];

        int rob = nums[i] + solve(i - 2, nums, dp);
        int skip = solve(i - 1, nums, dp);

        return dp[i] = max(rob, skip);
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1);
        return solve(n - 1, nums, dp);
    }
};

// ============================================================
// Approach 2 : Space Optimized DP (Bottom-Up)
// ============================================================
// Uses only last two states
//
// Time Complexity  : O(n)
// Space Complexity : O(1)
// ============================================================

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        int max2 = nums[0];                 // dp[i-2]
        int max1 = max(nums[0], nums[1]);   // dp[i-1]

        for (int i = 2; i < n; i++) {
            int curr = max(max2 + nums[i], max1);
            max2 = max1;
            max1 = curr;
        }
        return max1;
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    vector<int> nums = {2, 7, 9, 3, 1};

    SolutionMemo sol1;
    Solution sol2;

    cout << "Memoization Answer: "
         << sol1.rob(nums) << endl;

    cout << "Optimized DP Answer: "
         << sol2.rob(nums) << endl;

    return 0;
}
