#include <bits/stdc++.h>
using namespace std;

/*
LeetCode Link:
https://leetcode.com/problems/delete-operation-for-two-strings/

INTUITION:
Minimum deletions required to make two strings equal:
= n + m - 2 * LCS(word1, word2)
*/

// ====================== 1. BRUTE FORCE ======================
// Time: O(2^(n+m))
// Space: O(n+m)
int solveRec(string &s1, string &s2, int i, int j){
    if(i < 0 || j < 0) return 0;

    if(s1[i] == s2[j])
        return 1 + solveRec(s1, s2, i-1, j-1);

    return max(solveRec(s1, s2, i-1, j),
               solveRec(s1, s2, i, j-1));
}

// ====================== 2. MEMOIZATION ======================
// Time: O(n*m)
// Space: O(n*m)
int solveMemo(string &s1, string &s2, int i, int j,
              vector<vector<int>>& dp){
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
// Time: O(n*m)
// Space: O(n*m)
int solveTab(string &s1, string &s2){
    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[n][m];
}

// ====================== 4. SPACE OPTIMIZED ======================
// Time: O(n*m)
// Space: O(m)
int solveSpaceOpt(string &s1, string &s2){
    int n = s1.size();
    int m = s2.size();

    vector<int> prev(m+1, 0), curr(m+1, 0);

    for(int i = 1; i <= n; i++){
        fill(curr.begin(), curr.end(), 0);
        for(int j = 1; j <= m; j++){
            if(s1[i-1] == s2[j-1])
                curr[j] = 1 + prev[j-1];
            else
                curr[j] = max(prev[j], curr[j-1]);
        }
        prev = curr;
    }

    return prev[m];
}

// ====================== DRIVER FUNCTION ======================
int minDistance(string word1, string word2){

    // 1. Recursion
    // int lcs = solveRec(word1, word2,
    //                    word1.size()-1, word2.size()-1);

    // 2. Memoization
    // vector<vector<int>> dp(word1.size(),
    //                        vector<int>(word2.size(), -1));
    // int lcs = solveMemo(word1, word2,
    //                     word1.size()-1, word2.size()-1, dp);

    // 3. Tabulation
    // int lcs = solveTab(word1, word2);

    // 4. Space Optimized (BEST)
    int lcs = solveSpaceOpt(word1, word2);

    return word1.size() + word2.size() - 2 * lcs;
}

// ====================== MAIN ======================
int main(){
    string word1 = "sea";
    string word2 = "eat";

    cout << minDistance(word1, word2);
    return 0;
}