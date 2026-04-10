#include <bits/stdc++.h>
using namespace std;

/*
INTUITION:
- Match → 1 + f(i-1, j-1)
- Not match → max(f(i-1, j), f(i, j-1))
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
vector<vector<int>> solveTab(int n, int m, string &s1, string &s2){
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp;
}

// ====================== 4. SPACE OPTIMIZED ======================
// Time: O(n*m)
// Space: O(m)
int solveSpaceOpt(string &s1, string &s2){
    int n = s1.size(), m = s2.size();

    vector<int> prev(m+1, 0), curr(m+1, 0);

    for(int i = 1; i <= n; i++){
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

// ====================== BUILD LCS STRING ======================
string buildLCS(int n, int m, string &s1, string &s2){
    vector<vector<int>> dp = solveTab(n, m, s1, s2);

    int len = dp[n][m];
    string s(len, ' ');

    int i = n, j = m, ind = len - 1;

    while(i > 0 && j > 0){
        if(s1[i-1] == s2[j-1]){
            s[ind--] = s1[i-1];
            i--; j--;
        }
        else if(dp[i-1][j] > dp[i][j-1]){
            i--;
        }
        else j--;
    }

    return s;
}

// ====================== DRIVER ======================
int lcs(string s1, string s2){

    // 1. Recursion
    // return solveRec(s1, s2, s1.size()-1, s2.size()-1);

    // 2. Memoization
    // vector<vector<int>> dp(s1.size(), vector<int>(s2.size(), -1));
    // return solveMemo(s1, s2, s1.size()-1, s2.size()-1, dp);

    // 3. Tabulation
    // return solveTab(s1.size(), s2.size(), s1, s2)[s1.size()][s2.size()];

    // 4. Space Optimized (BEST for length)
    return solveSpaceOpt(s1, s2);
}

// ====================== MAIN ======================
int main(){
    string s1 = "abcde";
    string s2 = "bdgek";

    cout << lcs(s1, s2) << endl;
    cout << buildLCS(s1.size(), s2.size(), s1, s2);

    return 0;
}