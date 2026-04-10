#include <bits/stdc++.h>
using namespace std;

/*
LeetCode Link:
https://leetcode.com/problems/longest-palindromic-subsequence/

INTUITION:
LPS(s) = LCS(s, reverse(s))
*/

// ====================== 1. BRUTE FORCE ======================
// Time: O(2^n)
// Space: O(n)
int solveRec(string &s1, string &s2, int i, int j){
    if(i < 0 || j < 0) return 0;

    if(s1[i] == s2[j])
        return 1 + solveRec(s1, s2, i-1, j-1);

    return max(solveRec(s1, s2, i-1, j),
               solveRec(s1, s2, i, j-1));
}

// ====================== 2. MEMOIZATION ======================
// Time: O(n^2)
// Space: O(n^2)
int solveMemo(string &s1, string &s2, int i, int j,
              vector<vector<int>> &dp){
    if(i < 0 || j < 0) return 0;

    if(dp[i][j] != -1) return dp[i][j];

    if(s1[i] == s2[j])
        return dp[i][j] = 1 + solveMemo(s1, s2, i-1, j-1, dp);

    return dp[i][j] = max(
        solveMemo(s1, s2, i-1, j, dp),
        solveMemo(s1, s2, i, j-1, dp)
    );
}

// ====================== 3. TABULATION ======================
// Time: O(n^2)
// Space: O(n^2)
int solveTab(string &s1, string &s2){
    int n = s1.size();
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[n][n];
}

// ====================== 4. SPACE OPTIMIZED ======================
// Time: O(n^2)
// Space: O(n)
int solveSpaceOpt(string &s1, string &s2){
    int n = s1.size();
    vector<int> prev(n+1, 0), curr(n+1, 0);

    for(int i = 1; i <= n; i++){
        fill(curr.begin(), curr.end(), 0);
        for(int j = 1; j <= n; j++){
            if(s1[i-1] == s2[j-1])
                curr[j] = 1 + prev[j-1];
            else
                curr[j] = max(prev[j], curr[j-1]);
        }
        prev = curr;
    }

    return prev[n];
}

// ====================== DRIVER FUNCTION ======================
int longestPalindromeSubseq(string s){
    string rev = s;
    reverse(rev.begin(), rev.end());

    // 1. Recursion
    // return solveRec(s, rev, s.size()-1, rev.size()-1);

    // 2. Memoization
    // vector<vector<int>> dp(s.size(), vector<int>(s.size(), -1));
    // return solveMemo(s, rev, s.size()-1, rev.size()-1, dp);

    // 3. Tabulation
    // return solveTab(s, rev);

    // 4. Space Optimized (BEST)
    return solveSpaceOpt(s, rev);
}

// ====================== MAIN ======================
int main(){
    string s = "bbbab";
    cout << longestPalindromeSubseq(s);
    return 0;
}