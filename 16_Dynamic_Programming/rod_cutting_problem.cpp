#include <bits/stdc++.h>
using namespace std;

/*
GFG Link:
https://www.geeksforgeeks.org/problems/rod-cutting0840/1

INTUITION:
- Unbounded Knapsack (MAX)
- pick → stay
- notPick → move
*/

// ====================== 1. BRUTE FORCE ======================
// Time: Exponential
// Space: O(n)
int solveRec(vector<int>& price, int i, int len){
    if(i == 0){
        return len * price[0];
    }

    int notPick = solveRec(price, i-1, len);

    int pick = INT_MIN;
    int rodLen = i + 1;
    if(rodLen <= len){
        pick = price[i] + solveRec(price, i, len - rodLen);
    }

    return max(pick, notPick);
}

// ====================== 2. MEMOIZATION ======================
// Time: O(n * n)
// Space: O(n * n)
int solveMemo(vector<int>& price, int i, int len,
              vector<vector<int>>& dp){

    if(i == 0){
        return len * price[0];
    }

    if(dp[i][len] != -1) return dp[i][len];

    int notPick = solveMemo(price, i-1, len, dp);

    int pick = INT_MIN;
    int rodLen = i + 1;
    if(rodLen <= len){
        pick = price[i] + solveMemo(price, i, len - rodLen, dp);
    }

    return dp[i][len] = max(pick, notPick);
}

// ====================== 3. TABULATION ======================
// Time: O(n * n)
// Space: O(n * n)
int solveTab(vector<int>& price){
    int n = price.size();
    vector<vector<int>> dp(n, vector<int>(n+1, 0));

    // Base case
    for(int len = 0; len <= n; len++){
        dp[0][len] = len * price[0];
    }

    for(int i = 1; i < n; i++){
        int rodLen = i + 1;
        for(int len = 0; len <= n; len++){

            int notPick = dp[i-1][len];

            int pick = INT_MIN;
            if(rodLen <= len){
                pick = price[i] + dp[i][len - rodLen];
            }

            dp[i][len] = max(pick, notPick);
        }
    }

    return dp[n-1][n];
}

// ====================== 4. SPACE OPTIMIZED ======================
// Time: O(n * n)
// Space: O(n)
int solveSpaceOpt(vector<int>& price){
    int n = price.size();
    vector<int> dp(n+1, 0);

    // Base case
    for(int len = 0; len <= n; len++){
        dp[len] = len * price[0];
    }

    for(int i = 1; i < n; i++){
        int rodLen = i + 1;
        for(int len = rodLen; len <= n; len++){
            dp[len] = max(dp[len], price[i] + dp[len - rodLen]);
        }
    }

    return dp[n];
}

// ====================== DRIVER FUNCTION ======================
int cutRod(vector<int> &price){

    // 1. Recursion
    // return solveRec(price, price.size()-1, price.size());

    // 2. Memoization
    // int n = price.size();
    // vector<vector<int>> dp(n, vector<int>(n+1, -1));
    // return solveMemo(price, n-1, n, dp);

    // 3. Tabulation
    // return solveTab(price);

    // 4. Space Optimized (BEST)
    return solveSpaceOpt(price);
}

// ====================== MAIN ======================
int main(){
    vector<int> price = {2,5,7,8,10};
    cout << cutRod(price);
    return 0;
}