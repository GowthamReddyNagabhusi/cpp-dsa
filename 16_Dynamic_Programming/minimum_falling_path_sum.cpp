// Problem : Minimum Falling Path Sum
// LC : https://leetcode.com/problems/minimum-falling-path-sum/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach : Space Optimized DP
// ============================================================
// dp[j] = minimum falling path sum to reach column j of current row
// Transition:
// From (i, j) we can come from:
// - (i-1, j)
// - (i-1, j-1)
// - (i-1, j+1)
//
// Time Complexity  : O(n^2)
// Space Complexity : O(n)
// ============================================================

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {

        int n = matrix.size();
        vector<int> prev(n, 0), cur(n, 0);

        // Base case: first row
        prev = matrix[0];

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 0)
                    cur[j] = min(prev[j], prev[j + 1]) + matrix[i][j];
                else if (j == n - 1)
                    cur[j] = min(prev[j], prev[j - 1]) + matrix[i][j];
                else
                    cur[j] = min({prev[j], prev[j - 1], prev[j + 1]})
                             + matrix[i][j];
            }
            prev.swap(cur);   // avoid vector assignment warning
        }

        return *min_element(prev.begin(), prev.end());
    }
};

// ============================================================
// Test case
// ============================================================
int main() {

    vector<vector<int>> matrix = {
        {2, 1, 3},
        {6, 5, 4},
        {7, 8, 9}
    };

    Solution sol;
    cout << "Minimum Falling Path Sum: "
         << sol.minFallingPathSum(matrix) << endl;

    return 0;
}
