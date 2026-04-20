#include <bits/stdc++.h>
using namespace std;

/*
LeetCode Link:
https://leetcode.com/problems/longest-increasing-subsequence/

INTUITION:
- pick if nums[i] > nums[prev]
- else skip
*/

// ====================== 1. BRUTE FORCE ======================
int solveRec(vector<int>& nums, int i, int prev){
    if(i == nums.size()) return 0;

    int notTake = solveRec(nums, i+1, prev);

    int take = 0;
    if(prev == -1 || nums[i] > nums[prev])
        take = 1 + solveRec(nums, i+1, i);

    return max(take, notTake);
}

// ====================== 2. MEMOIZATION ======================
int solveMemo(vector<int>& nums, int i, int prev,
              vector<vector<int>>& dp){

    if(i == nums.size()) return 0;

    if(dp[i][prev+1] != -1) return dp[i][prev+1];

    int notTake = solveMemo(nums, i+1, prev, dp);

    int take = 0;
    if(prev == -1 || nums[i] > nums[prev])
        take = 1 + solveMemo(nums, i+1, i, dp);

    return dp[i][prev+1] = max(take, notTake);
}

// ====================== 3. TABULATION ======================
int solveTab(vector<int>& nums){
    int n = nums.size();
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    for(int i = n-1; i >= 0; i--){
        for(int prev = i-1; prev >= -1; prev--){

            int notTake = dp[i+1][prev+1];

            int take = 0;
            if(prev == -1 || nums[i] > nums[prev])
                take = 1 + dp[i+1][i+1];

            dp[i][prev+1] = max(take, notTake);
        }
    }

    return dp[0][0];
}

// ====================== 4. SPACE OPTIMIZED ======================
int solveSpaceOpt(vector<int>& nums){
    int n = nums.size();
    vector<int> next(n+1, 0), curr(n+1, 0);

    for(int i = n-1; i >= 0; i--){
        for(int prev = i-1; prev >= -1; prev--){

            int notTake = next[prev+1];

            int take = 0;
            if(prev == -1 || nums[i] > nums[prev])
                take = 1 + next[i+1];

            curr[prev+1] = max(take, notTake);
        }
        next = curr;
    }

    return next[0];
}

// ====================== 5. OPTIMAL (BINARY SEARCH) ======================
// Time: O(n log n)
// Space: O(n)
int solveOptimal(vector<int>& nums){
    vector<int> temp;

    for(int x : nums){
        auto it = lower_bound(temp.begin(), temp.end(), x);

        if(it == temp.end())
            temp.push_back(x);
        else
            *it = x;
    }

    return temp.size();
}

// ====================== DRIVER ======================
int lengthOfLIS(vector<int>& nums){

    // 1. Recursion
    // return solveRec(nums, 0, -1);

    // 2. Memoization
    // vector<vector<int>> dp(nums.size(),
    //                        vector<int>(nums.size()+1, -1));
    // return solveMemo(nums, 0, -1, dp);

    // 3. Tabulation
    // return solveTab(nums);

    // 4. Space Optimized
    // return solveSpaceOpt(nums);

    // 5. Optimal (BEST)
    return solveOptimal(nums);
}

// ====================== MAIN ======================
int main(){
    vector<int> nums = {10,9,2,5,3,7,101,18};

    cout << lengthOfLIS(nums);
    return 0;
}