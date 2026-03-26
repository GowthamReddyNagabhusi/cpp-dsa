// Problem : Subset Sum Problem
// GFG : https://practice.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach : Space Optimized DP
// ============================================================
// dp[j] = whether a subset with sum j is possible
// Transition:
// dp[j] = dp[j] (not take) || dp[j - arr[i]] (take)
//
// Time Complexity  : O(n * sum)
// Space Complexity : O(sum)
// ============================================================

class Solution {
public:
    bool isSubsetSum(vector<int>& arr, int sum) {

        int n = arr.size();
        vector<bool> prev(sum + 1, false);

        // Base case
        prev[0] = true;
        if (arr[0] <= sum)
            prev[arr[0]] = true;

        for (int i = 1; i < n; i++) {
            vector<bool> curr(sum + 1, false);
            curr[0] = true;

            for (int j = 1; j <= sum; j++) {
                bool notTake = prev[j];
                bool take = false;

                if (arr[i] <= j)
                    take = prev[j - arr[i]];

                curr[j] = take || notTake;
            }
            prev.swap(curr);
        }
        return prev[sum];
    }
};

// ============================================================
// Test case
// ============================================================
int main() {

    vector<int> arr = {3, 34, 4, 12, 5, 2};
    int sum = 9;

    Solution sol;
    cout << "Subset Sum Exists: "
         << (sol.isSubsetSum(arr, sum) ? "Yes" : "No") << endl;

    return 0;
}
