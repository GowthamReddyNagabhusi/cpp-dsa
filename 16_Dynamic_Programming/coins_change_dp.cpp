#include <bits/stdc++.h>
using namespace std;

/*
LeetCode Link:
https://leetcode.com/problems/coin-change/

INTUITION:
At each coin:
- notPick → move to i-1
- pick → take coin and stay at i (unbounded)
Goal: minimize number of coins
*/

// ====================== 1. BRUTE FORCE ======================
// Time: Exponential
// Space: O(n)
int solveRec(vector<int>& arr, int i, int target) {
    if(i == 0){
        if(target % arr[0] == 0) return target / arr[0];
        return 1e9;
    }

    int notPick = solveRec(arr, i-1, target);

    int pick = 1e9;
    if(arr[i] <= target)
        pick = 1 + solveRec(arr, i, target - arr[i]);

    return min(pick, notPick);
}

// ====================== 2. MEMOIZATION ======================
// Time: O(n * amount)
// Space: O(n * amount)
int solveMemo(vector<int>& arr, int i, int target, vector<vector<int>>& dp) {
    if(i == 0){
        if(target % arr[0] == 0) return target / arr[0];
        return 1e9;
    }

    if(dp[i][target] != -1) return dp[i][target];

    int notPick = solveMemo(arr, i-1, target, dp);

    int pick = 1e9;
    if(arr[i] <= target)
        pick = 1 + solveMemo(arr, i, target - arr[i], dp);

    return dp[i][target] = min(pick, notPick);
}

// ====================== 3. TABULATION ======================
// Time: O(n * amount)
// Space: O(n * amount)
int solveTab(vector<int>& arr, int target) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(target+1, 0));

    // Base case
    for(int t = 0; t <= target; t++){
        if(t % arr[0] == 0)
            dp[0][t] = t / arr[0];
        else
            dp[0][t] = 1e9;
    }

    for(int i = 1; i < n; i++){
        for(int t = 0; t <= target; t++){
            int notPick = dp[i-1][t];

            int pick = 1e9;
            if(arr[i] <= t)
                pick = 1 + dp[i][t - arr[i]];

            dp[i][t] = min(pick, notPick);
        }
    }

    return dp[n-1][target];
}

// ====================== 4. SPACE OPTIMIZED ======================
// Time: O(n * amount)
// Space: O(amount)
int solveSpaceOpt(vector<int>& arr, int target) {
    int n = arr.size();
    vector<int> dp(target+1, 0);

    // Base case
    for(int t = 0; t <= target; t++){
        if(t % arr[0] == 0)
            dp[t] = t / arr[0];
        else
            dp[t] = 1e9;
    }

    for(int i = 1; i < n; i++){
        for(int t = arr[i]; t <= target; t++){
            dp[t] = min(dp[t], 1 + dp[t - arr[i]]);
        }
    }

    return dp[target];
}

// ====================== DRIVER FUNCTION ======================
int coinChange(vector<int>& coins, int amount) {

    // 1. Recursion
    // return solveRec(coins, coins.size()-1, amount);

    // 2. Memoization
    // vector<vector<int>> dp(coins.size(), vector<int>(amount+1, -1));
    // int ans = solveMemo(coins, coins.size()-1, amount, dp);
    // return (ans >= 1e9) ? -1 : ans;

    // 3. Tabulation
    // int ans = solveTab(coins, amount);
    // return (ans >= 1e9) ? -1 : ans;

    // 4. Space Optimized (BEST)
    int ans = solveSpaceOpt(coins, amount);
    return (ans >= 1e9) ? -1 : ans;
}

// ====================== MAIN ======================
int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    cout << coinChange(coins, amount);

    return 0;
}