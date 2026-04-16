#include <bits/stdc++.h>
using namespace std;

/*
LeetCode Link:
https://leetcode.com/problems/wildcard-matching/

INTUITION:
- '?' matches one char
- '*' matches zero or more chars
*/

// ====================== 1. BRUTE FORCE ======================
// Time: Exponential
// Space: O(n+m)
bool solveRec(string &s, string &p, int i, int j){
    if(i < 0 && j < 0) return true;
    if(j < 0) return false;

    if(i < 0){
        for(int k = 0; k <= j; k++){
            if(p[k] != '*') return false;
        }
        return true;
    }

    if(p[j] == s[i] || p[j] == '?')
        return solveRec(s, p, i-1, j-1);

    if(p[j] == '*')
        return solveRec(s, p, i-1, j) ||
               solveRec(s, p, i, j-1);

    return false;
}

// ====================== 2. MEMOIZATION ======================
// Time: O(n*m)
// Space: O(n*m)
bool solveMemo(string &s, string &p, int i, int j,
               vector<vector<int>> &dp){

    if(i < 0 && j < 0) return true;
    if(j < 0) return false;

    if(i < 0){
        for(int k = 0; k <= j; k++){
            if(p[k] != '*') return false;
        }
        return true;
    }

    if(dp[i][j] != -1) return dp[i][j];

    if(p[j] == s[i] || p[j] == '?')
        return dp[i][j] =
            solveMemo(s, p, i-1, j-1, dp);

    if(p[j] == '*')
        return dp[i][j] =
            solveMemo(s, p, i-1, j, dp) ||
            solveMemo(s, p, i, j-1, dp);

    return dp[i][j] = false;
}

// ====================== 3. TABULATION ======================
// Time: O(n*m)
// Space: O(n*m)
bool solveTab(string &s, string &p){
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));

    dp[0][0] = true;

    for(int j = 1; j <= n; j++){
        if(p[j-1] == '*')
            dp[0][j] = dp[0][j-1];
    }

    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){

            if(p[j-1] == '*'){
                dp[i][j] = dp[i][j-1] || dp[i-1][j];
            }
            else if(p[j-1] == '?' || p[j-1] == s[i-1]){
                dp[i][j] = dp[i-1][j-1];
            }
            else dp[i][j] = false;
        }
    }

    return dp[m][n];
}

// ====================== 4. SPACE OPTIMIZED ======================
// Time: O(n*m)
// Space: O(n)
bool solveSpaceOpt(string &s, string &p){
    int m = s.size(), n = p.size();
    vector<bool> prev(n+1, false), curr(n+1, false);

    prev[0] = true;

    for(int j = 1; j <= n; j++){
        if(p[j-1] == '*')
            prev[j] = prev[j-1];
    }

    for(int i = 1; i <= m; i++){
        curr[0] = false;

        for(int j = 1; j <= n; j++){

            if(p[j-1] == '*'){
                curr[j] = curr[j-1] || prev[j];
            }
            else if(p[j-1] == '?' || p[j-1] == s[i-1]){
                curr[j] = prev[j-1];
            }
            else curr[j] = false;
        }

        prev = curr;
    }

    return prev[n];
}

// ====================== DRIVER FUNCTION ======================
bool isMatch(string s, string p){

    // 1. Recursion
    // return solveRec(s, p, s.size()-1, p.size()-1);

    // 2. Memoization
    // vector<vector<int>> dp(s.size(), vector<int>(p.size(), -1));
    // return solveMemo(s, p, s.size()-1, p.size()-1, dp);

    // 3. Tabulation
    // return solveTab(s, p);

    // 4. Space Optimized (BEST)
    return solveSpaceOpt(s, p);
}

// ====================== MAIN ======================
int main(){
    string s = "adceb";
    string p = "*a*b";

    cout << isMatch(s, p);
    return 0;
}