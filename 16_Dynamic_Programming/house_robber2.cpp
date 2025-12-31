// Problem : House Robber II
// LC : https://leetcode.com/problems/house-robber-ii/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach 1 : Memoization (Top-Down DP)
// ============================================================
// Since houses are circular:
// - Case 1: Rob houses from index 0 to n-2
// - Case 2: Rob houses from index 1 to n-1
// Take max of both
//
// Time Complexity  : O(n)
// Space Complexity : O(n)
// ============================================================

class SolutionMemo {
private:
    int solve(int i, int end, vector<int>& nums, vector<int>& dp) {
        if (i > end) return 0;
        if (dp[i] != -1) return dp[i];

        int rob = nums[i] + solve(i + 2, end, nums, dp);
        int skip = solve(i + 1, end, nums, dp);

        return dp[i] = max(rob, skip);
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        vector<int> dp1(n, -1), dp2(n, -1);

        int case1 = solve(0, n - 2, nums, dp1); // exclude last
        int case2 = solve(1, n - 1, nums, dp2); // exclude first

        return max(case1, case2);
    }
};

// ============================================================
// Approach 2 : Space Optimized DP (Bottom-Up)
// ============================================================
// Apply House Robber I logic twice
//
// Time Complexity  : O(n)
// Space Complexity : O(1)
// ============================================================

class Solution {
private:
    int robLinear(vector<int>& nums, int l, int r) {
        int prev2 = 0;
        int prev1 = nums[l];

        for (int i = l + 1; i <= r; i++) {
            int curr = max(prev2 + nums[i], prev1);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        int case1 = robLinear(nums, 0, n - 2); // exclude last
        int case2 = robLinear(nums, 1, n - 1); // exclude first

        return max(case1, case2);
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    vector<int> nums = {2, 3, 2};

    SolutionMemo sol1;
    Solution sol2;

    cout << "Memoization Answer: "
         << sol1.rob(nums) << endl;

    cout << "Optimized DP Answer: "
         << sol2.rob(nums) << endl;

    return 0;
}
