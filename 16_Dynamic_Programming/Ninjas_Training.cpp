// Problem : Ninja Training
// GFG : https://www.naukri.com/code360/problems/ninja-s-training_3621003
#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach 1 : Memoization (Top-Down DP)
// ============================================================
// dp[day][last] = max points till day when last task was `last`
// last = {0,1,2} → actual task
// last = 3       → no restriction
//
// Time Complexity  : O(n * 4 * 3) ≈ O(n)
// Space Complexity : O(n * 4) (dp + recursion stack)
// ============================================================

class SolutionMemo {
private:
    int solve(int day, int last,
              vector<vector<int>>& points,
              vector<vector<int>>& dp) {

        if (day == 0) {
            int maxi = 0;
            for (int task = 0; task < 3; task++) {
                if (task != last) {
                    maxi = max(maxi, points[0][task]);
                }
            }
            return dp[0][last] = maxi;
        }

        if (dp[day][last] != -1)
            return dp[day][last];

        int maxi = 0;
        for (int task = 0; task < 3; task++) {
            if (task != last) {
                maxi = max(maxi,
                    points[day][task] +
                    solve(day - 1, task, points, dp)
                );
            }
        }
        return dp[day][last] = maxi;
    }

public:
    int ninjaTraining(int n, vector<vector<int>>& points) {
        vector<vector<int>> dp(n, vector<int>(4, -1));
        return solve(n - 1, 3, points, dp);
    }
};

// ============================================================
// Approach 2 : Tabulation (Bottom-Up DP)
// ============================================================
// Time Complexity  : O(n * 4 * 3) ≈ O(n)
// Space Complexity : O(n * 4)
// ============================================================

class SolutionTabulation {
public:
    int ninjaTraining(int n, vector<vector<int>>& points) {

        vector<vector<int>> dp(n, vector<int>(4, 0));

        // Base case (day = 0)
        dp[0][0] = max(points[0][1], points[0][2]);
        dp[0][1] = max(points[0][0], points[0][2]);
        dp[0][2] = max(points[0][0], points[0][1]);
        dp[0][3] = max(points[0][0],
                       max(points[0][1], points[0][2]));

        for (int day = 1; day < n; day++) {
            for (int last = 0; last < 4; last++) {
                dp[day][last] = 0;
                for (int task = 0; task < 3; task++) {
                    if (task == last) continue;
                    dp[day][last] = max(
                        dp[day][last],
                        points[day][task] + dp[day - 1][task]
                    );
                }
            }
        }
        return dp[n - 1][3];
    }
};

// ============================================================
// Approach 3 : Space Optimization
// ============================================================
// Time Complexity  : O(n * 4 * 3) ≈ O(n)
// Space Complexity : O(4) ≈ O(1)
// ============================================================

class Solution {
public:
    int ninjaTraining(int n, vector<vector<int>>& points) {

        vector<int> prev(4, 0);

        prev[0] = max(points[0][1], points[0][2]);
        prev[1] = max(points[0][0], points[0][2]);
        prev[2] = max(points[0][0], points[0][1]);
        prev[3] = max(points[0][0],
                       max(points[0][1], points[0][2]));

        for (int day = 1; day < n; day++) {
            vector<int> temp(4, 0);
            for (int last = 0; last < 4; last++) {
                for (int task = 0; task < 3; task++) {
                    if (task == last) continue;
                    temp[last] = max(
                        temp[last],
                        points[day][task] + prev[task]
                    );
                }
            }
            prev = temp;
        }
        return prev[3];
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    vector<vector<int>> points = {
        {10, 40, 70},
        {20, 50, 80},
        {30, 60, 90}
    };
    int n = points.size();

    SolutionMemo sol1;
    SolutionTabulation sol2;
    Solution sol3;

    cout << "Memoization Answer: "
         << sol1.ninjaTraining(n, points) << endl;

    cout << "Tabulation Answer: "
         << sol2.ninjaTraining(n, points) << endl;

    cout << "Space Optimized Answer: "
         << sol3.ninjaTraining(n, points) << endl;

    return 0;
}
