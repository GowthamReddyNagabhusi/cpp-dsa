/*
===========================================================
Problem: Perfect Sum Problem (Count Subsets with Sum = K)
Link: https://www.geeksforgeeks.org/problems/perfect-sum-problem5633/1

Given an array, count number of subsets whose sum equals target.

===========================================================

APPROACHES:

1. Brute Force (Recursion)
   Time Complexity: O(2^n)
   Space Complexity: O(n)

2. Memoization (Top-Down DP)
   Time Complexity: O(n * target)
   Space Complexity: O(n * target) + recursion stack

3. Tabulation (Bottom-Up DP)
   Time Complexity: O(n * target)
   Space Complexity: O(n * target)

===========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // =========================
    // 1. BRUTE FORCE
    // =========================
    int solveRec(vector<int>& arr, int target, int i){
        if(i == 0){
            if(target == 0 && arr[0] == 0) return 2;
            if(target == 0 || target == arr[0]) return 1;
            return 0;
        }

        int notPick = solveRec(arr, target, i-1);
        int pick = 0;

        if(arr[i] <= target)
            pick = solveRec(arr, target - arr[i], i-1);

        return pick + notPick;
    }

    int perfectSumRec(vector<int>& arr, int target){
        int n = arr.size();
        return solveRec(arr, target, n-1);
    }


    // =========================
    // 2. MEMOIZATION
    // =========================
    int solveMemo(vector<int>& arr, int target, int i, vector<vector<int>>& dp){
        if(i == 0){
            if(target == 0 && arr[0] == 0) return 2;
            if(target == 0 || target == arr[0]) return 1;
            return 0;
        }

        if(dp[i][target] != -1) return dp[i][target];

        int notPick = solveMemo(arr, target, i-1, dp);
        int pick = 0;

        if(arr[i] <= target)
            pick = solveMemo(arr, target - arr[i], i-1, dp);

        return dp[i][target] = pick + notPick;
    }

    int perfectSumMemo(vector<int>& arr, int target){
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(target+1, -1));
        return solveMemo(arr, target, n-1, dp);
    }


    // =========================
    // 3. TABULATION
    // =========================
    int perfectSumTab(vector<int>& arr, int target){
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(target+1, 0));

        // Base case
        if(arr[0] == 0)
            dp[0][0] = 2;
        else
            dp[0][0] = 1;

        if(arr[0] != 0 && arr[0] <= target)
            dp[0][arr[0]] = 1;

        for(int i = 1; i < n; i++){
            for(int t = 0; t <= target; t++){
                int notPick = dp[i-1][t];
                int pick = 0;

                if(arr[i] <= t)
                    pick = dp[i-1][t - arr[i]];

                dp[i][t] = pick + notPick;
            }
        }

        return dp[n-1][target];
    }
};


// =========================
// MAIN FUNCTION (TEST CASES)
// =========================
int main(){
    Solution sol;

    vector<vector<int>> testArrays = {
        {1,2,3,3},
        {0,0,1},
        {2,3,5,6,8,10},
        {0,0,0}
    };

    vector<int> targets = {6, 1, 10, 0};

    for(int i = 0; i < testArrays.size(); i++){
        cout << "Test Case " << i+1 << ":\n";
        cout << "Array: ";
        for(int x : testArrays[i]) cout << x << " ";
        cout << "\nTarget: " << targets[i] << "\n";

        cout << "Brute Force: " 
             << sol.perfectSumRec(testArrays[i], targets[i]) << "\n";

        cout << "Memoization: " 
             << sol.perfectSumMemo(testArrays[i], targets[i]) << "\n";

        cout << "Tabulation: " 
             << sol.perfectSumTab(testArrays[i], targets[i]) << "\n";

        cout << "--------------------------\n";
    }

    return 0;
}