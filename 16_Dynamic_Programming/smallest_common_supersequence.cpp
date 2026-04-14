#include <bits/stdc++.h>
using namespace std;

/*
LeetCode Link:
https://leetcode.com/problems/shortest-common-supersequence/

INTUITION:
SCS is built using the LCS table.
Length of SCS = n + m - LCS.
*/

// ====================== 1. BRUTE FORCE ======================
// Time: Exponential
// Space: O(n + m)
string solveRec(string &s1, string &s2, int i, int j) {
    if (i == 0) return s2.substr(0, j);
    if (j == 0) return s1.substr(0, i);

    if (s1[i - 1] == s2[j - 1])
        return solveRec(s1, s2, i - 1, j - 1) + s1[i - 1];

    string op1 = solveRec(s1, s2, i - 1, j) + s1[i - 1];
    string op2 = solveRec(s1, s2, i, j - 1) + s2[j - 1];

    return (op1.size() < op2.size()) ? op1 : op2;
}

// ====================== 2. MEMOIZATION ======================
// Time: O(n * m)
// Space: O(n * m)
string solveMemo(string &s1, string &s2, int i, int j,
                 vector<vector<string>> &dp) {
    if (i == 0) return s2.substr(0, j);
    if (j == 0) return s1.substr(0, i);

    if (dp[i][j] != "#") return dp[i][j];

    if (s1[i - 1] == s2[j - 1])
        return dp[i][j] =
            solveMemo(s1, s2, i - 1, j - 1, dp) + s1[i - 1];

    string op1 = solveMemo(s1, s2, i - 1, j, dp) + s1[i - 1];
    string op2 = solveMemo(s1, s2, i, j - 1, dp) + s2[j - 1];

    return dp[i][j] =
        (op1.size() < op2.size()) ? op1 : op2;
}

// ====================== 3. TABULATION ======================
// Time: O(n * m)
// Space: O(n * m)
string solveTab(string &str1, string &str2) {
    int m = str1.size();
    int n = str2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Build LCS table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Reconstruct SCS
    string ans = "";
    int i = m, j = n;

    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            ans.push_back(str1[i - 1]);
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            ans.push_back(str1[i - 1]);
            i--;
        }
        else {
            ans.push_back(str2[j - 1]);
            j--;
        }
    }

    while (i > 0) ans.push_back(str1[--i]);
    while (j > 0) ans.push_back(str2[--j]);

    reverse(ans.begin(), ans.end());
    return ans;
}

// ====================== 4. SPACE OPTIMIZED ======================
// Note: Only length can be optimized, reconstruction requires full DP.
int solveSpaceOptLength(string &s1, string &s2) {
    int m = s1.size(), n = s2.size();
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1])
                curr[j] = 1 + prev[j - 1];
            else
                curr[j] = max(prev[j], curr[j - 1]);
        }
        prev = curr;
    }

    int lcs = prev[n];
    return m + n - lcs;
}

// ====================== DRIVER FUNCTION ======================
string shortestCommonSupersequence(string str1, string str2) {

    // 1. Recursion
    // return solveRec(str1, str2, str1.size(), str2.size());

    // 2. Memoization
    // vector<vector<string>> dp(
    //     str1.size() + 1,
    //     vector<string>(str2.size() + 1, "#"));
    // return solveMemo(str1, str2,
    //                  str1.size(), str2.size(), dp);

    // 3. Tabulation (BEST for reconstruction)
    return solveTab(str1, str2);
}

// ====================== MAIN ======================
int main() {
    string str1 = "abac";
    string str2 = "cab";

    cout << shortestCommonSupersequence(str1, str2);
    return 0;
}