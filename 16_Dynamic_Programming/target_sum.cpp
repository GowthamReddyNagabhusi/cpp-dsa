#include <bits/stdc++.h>
using namespace std;

/*
LeetCode Link:
https://leetcode.com/problems/target-sum/

INTUITION:
At each index:
- add +nums[i]
- add -nums[i]
No skipping allowed
Count total ways to reach target
*/

// ====================== 1. BRUTE FORCE ======================
// Time: O(2^n)
// Space: O(n)
int solveRec(vector<int>& nums, int target, int sum, int ind){
    if(ind == 0){
        if(nums[0] == 0){
            if(sum == target) return 2;
            else return 0;
        }
        if(sum + nums[0] == target) return 1;
        if(sum - nums[0] == target) return 1;
        return 0;
    }

    int plus = solveRec(nums, target, sum + nums[ind], ind-1);
    int minus = solveRec(nums, target, sum - nums[ind], ind-1);

    return plus + minus;
}

// ====================== 2. MEMOIZATION ======================
// Time: O(n * totalSum)
// Space: O(n * totalSum)
int solveMemo(vector<int>& nums, int target, int sum, int ind,
              vector<vector<int>>& dp, int shift){

    if(ind == 0){
        if(nums[0] == 0){
            if(sum == target) return 2;
            else return 0;
        }
        if(sum + nums[0] == target) return 1;
        if(sum - nums[0] == target) return 1;
        return 0;
    }

    if(dp[ind][sum + shift] != -1)
        return dp[ind][sum + shift];

    int plus = solveMemo(nums, target, sum + nums[ind], ind-1, dp, shift);
    int minus = solveMemo(nums, target, sum - nums[ind], ind-1, dp, shift);

    return dp[ind][sum + shift] = plus + minus;
}

// ====================== 3. TABULATION ======================
// Time: O(n * totalSum)
// Space: O(n * totalSum)
int solveTab(vector<int>& nums, int target){
    int n = nums.size();

    int totalSum = 0;
    for(int x : nums) totalSum += x;

    if(abs(target) > totalSum) return 0;

    int shift = totalSum;

    vector<vector<int>> dp(n, vector<int>(2 * totalSum + 1, 0));

    // Base case
    if(nums[0] == 0){
        dp[0][shift] = 2;
    } else {
        dp[0][shift + nums[0]] = 1;
        dp[0][shift - nums[0]] = 1;
    }

    for(int i = 1; i < n; i++){
        for(int sum = -totalSum; sum <= totalSum; sum++){

            int ways = dp[i-1][sum + shift];
            if(ways != 0){

                dp[i][sum + nums[i] + shift] += ways;
                dp[i][sum - nums[i] + shift] += ways;
            }
        }
    }

    return dp[n-1][target + shift];
}

// ====================== 4. SPACE OPTIMIZED ======================
// Time: O(n * totalSum)
// Space: O(totalSum)
int solveSpaceOpt(vector<int>& nums, int target){
    int totalSum = 0;
    for(int x : nums) totalSum += x;

    if(abs(target) > totalSum) return 0;

    int shift = totalSum;

    vector<int> dp(2 * totalSum + 1, 0);

    // Base case
    if(nums[0] == 0){
        dp[shift] = 2;
    } else {
        dp[shift + nums[0]] = 1;
        dp[shift - nums[0]] = 1;
    }

    for(int i = 1; i < nums.size(); i++){
        vector<int> newDp(2 * totalSum + 1, 0);

        for(int sum = -totalSum; sum <= totalSum; sum++){

            int ways = dp[sum + shift];
            if(ways != 0){

                newDp[sum + nums[i] + shift] += ways;
                newDp[sum - nums[i] + shift] += ways;
            }
        }

        dp = newDp;
    }

    return dp[target + shift];
}

// ====================== DRIVER FUNCTION ======================
int findTargetSumWays(vector<int>& nums, int target){

    // 1. Recursion
    // return solveRec(nums, target, 0, nums.size()-1);

    // 2. Memoization
    // int totalSum = accumulate(nums.begin(), nums.end(), 0);
    // int shift = totalSum;
    // vector<vector<int>> dp(nums.size(),
    //     vector<int>(2 * totalSum + 1, -1));
    // return solveMemo(nums, target, 0, nums.size()-1, dp, shift);

    // 3. Tabulation
    // return solveTab(nums, target);

    // 4. Space Optimized (BEST for this approach)
    return solveSpaceOpt(nums, target);
}

// ====================== MAIN ======================
int main(){
    vector<int> nums = {1,1,1,1,1};
    int target = 3;

    cout << findTargetSumWays(nums, target);

    return 0;
}