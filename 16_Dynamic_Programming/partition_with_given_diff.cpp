#include <bits/stdc++.h>
using namespace std;

/*
GFG Link:
https://www.geeksforgeeks.org/problems/partitions-with-given-difference/1

INTUITION:
Convert partition problem → subset sum count
target = (sum + diff) / 2
Count number of subsets with sum = target
*/

// ====================== 1. BRUTE FORCE ======================
// Time: O(2^n)
// Space: O(n)
int solveRec(vector<int>& arr, int i, int target) {
    if(i == 0){
        if(target == 0 && arr[0] == 0) return 2;
        if(target == 0 || target == arr[0]) return 1;
        return 0;
    }

    int notPick = solveRec(arr, i-1, target);
    int pick = 0;

    if(arr[i] <= target)
        pick = solveRec(arr, i-1, target - arr[i]);

    return pick + notPick;
}

// ====================== 2. MEMOIZATION ======================
// Time: O(n * target)
// Space: O(n * target)
int solveMemo(vector<int>& arr, int i, int target, vector<vector<int>>& dp) {
    if(i == 0){
        if(target == 0 && arr[0] == 0) return 2;
        if(target == 0 || target == arr[0]) return 1;
        return 0;
    }

    if(dp[i][target] != -1) return dp[i][target];

    int notPick = solveMemo(arr, i-1, target, dp);
    int pick = 0;

    if(arr[i] <= target)
        pick = solveMemo(arr, i-1, target - arr[i], dp);

    return dp[i][target] = pick + notPick;
}

// ====================== 3. TABULATION ======================
// Time: O(n * target)
// Space: O(n * target)
int solveTab(vector<int>& arr, int target) {
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

// ====================== 4. SPACE OPTIMIZED ======================
// Time: O(n * target)
// Space: O(target)
int solveSpaceOpt(vector<int>& arr, int target) {
    int n = arr.size();
    vector<int> dp(target+1, 0);

    if(arr[0] == 0)
        dp[0] = 2;
    else
        dp[0] = 1;

    if(arr[0] != 0 && arr[0] <= target)
        dp[arr[0]] = 1;

    for(int i = 1; i < n; i++){
        for(int t = target; t >= 0; t--){
            if(arr[i] <= t)
                dp[t] += dp[t - arr[i]];
        }
    }

    return dp[target];
}

// ====================== DRIVER FUNCTION ======================
int countPartitions(vector<int>& arr, int diff) {
    int sum = 0;
    for(int x : arr) sum += x;

    if(sum < diff || (sum + diff) % 2) return 0;

    int target = (sum + diff) / 2;

    // Choose any method:

    // 1. Recursion
    // return solveRec(arr, arr.size()-1, target);

    // 2. Memoization
    // vector<vector<int>> dp(arr.size(), vector<int>(target+1, -1));
    // return solveMemo(arr, arr.size()-1, target, dp);

    // 3. Tabulation
    // return solveTab(arr, target);

    // 4. Space Optimized (BEST)
    return solveSpaceOpt(arr, target);
}

// ====================== MAIN ======================
int main() {
    vector<int> arr = {1,1,2,3};
    int diff = 1;

    cout << countPartitions(arr, diff);

    return 0;
}