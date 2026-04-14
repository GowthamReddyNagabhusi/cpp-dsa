#include <bits/stdc++.h>
using namespace std;

/*
LeetCode Link:
https://leetcode.com/problems/distinct-subsequences/

INTUITION:
Count the number of distinct subsequences of s that equal t.
*/

// ====================== 1. BRUTE FORCE ======================
// Time: O(2^m)
// Space: O(m+n)
long long solveRec(string &s, string &t, int i, int j) {
    if (j < 0) return 1;  // matched all characters of t
    if (i < 0) return 0;  // s exhausted

    if (s[i] == t[j])
        return solveRec(s, t, i-1, j-1) +
               solveRec(s, t, i-1, j);
    else
        return solveRec(s, t, i-1, j);
}

// ====================== 2. MEMOIZATION ======================
// Time: O(m * n)
// Space: O(m * n)
long long solveMemo(string &s, string &t, int i, int j,
                    vector<vector<long long>> &dp) {
    if (j < 0) return 1;
    if (i < 0) return 0;

    if (dp[i][j] != -1) return dp[i][j];

    if (s[i] == t[j])
        return dp[i][j] =
            solveMemo(s, t, i-1, j-1, dp) +
            solveMemo(s, t, i-1, j, dp);
    else
        return dp[i][j] =
            solveMemo(s, t, i-1, j, dp);
}

// ====================== 3. TABULATION ======================
// Time: O(m * n)
// Space: O(m * n)
long long solveTab(string &s, string &t) {
    int m = s.size();
    int n = t.size();

    vector<vector<long long>> dp(m+1,
                                 vector<long long>(n+1, 0));

    // Base case: empty t
    for (int i = 0; i <= m; i++)
        dp[i][0] = 1;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i-1] == t[j-1])
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
            else
                dp[i][j] = dp[i-1][j];
        }
    }

    return dp[m][n];
}

// ====================== 4. SPACE OPTIMIZED ======================
// Time: O(m * n)
// Space: O(n)
long long solveSpaceOpt(string &s, string &t) {
    int m = s.size();
    int n = t.size();

    vector<long long> dp(n+1, 0);
    dp[0] = 1;

    for (int i = 1; i <= m; i++) {
        for (int j = n; j >= 1; j--) {
            if (s[i-1] == t[j-1]) {
                dp[j] += dp[j-1];
            }
        }
    }

    return dp[n];
}

// ====================== DRIVER FUNCTION ======================
int numDistinct(string s, string t) {

    // 1. Recursion
    // return (int)solveRec(s, t, s.size()-1, t.size()-1);

    // 2. Memoization
    // vector<vector<long long>> dp(
    //     s.size(), vector<long long>(t.size(), -1));
    // return (int)solveMemo(s, t,
    //                       s.size()-1, t.size()-1, dp);

    // 3. Tabulation
    // return (int)solveTab(s, t);

    // 4. Space Optimized (BEST)
    return (int)solveSpaceOpt(s, t);
}

// ====================== MAIN ======================
int main() {
    string s = "rabbbit";
    string t = "rabbit";

    cout << numDistinct(s, t);
    return 0;
}