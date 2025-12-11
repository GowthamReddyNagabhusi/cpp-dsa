// Problem : Minimum Multiplications to Reach End
// GFG : https://www.geeksforgeeks.org/problems/minimum-multiplications-to-reach-end/1

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------
// Approach:
// This is a graph problem where each value from 0 to 99999 is a node.
// From a node x, you can go to (x * arr[i]) % 100000 in 1 step.
// Since all edges have weight 1 → use BFS.
//
// Steps:
// 1. dist[] array stores minimum steps to reach each value.
// 2. Start BFS from 'start' with distance 0.
// 3. For every allowed multiplier m in arr:
//        next = (current * m) % 100000
//        if we find a shorter path → update and push to queue.
// 4. Stop early if we reach 'end'.
// --------------------------------------------

class Solution {
public:
    int minimumMultiplications(vector<int>& arr, int start, int end) {
        if (start == end) return 0;

        const int MOD = 100000;
        vector<int> dist(MOD, INT_MAX);
        queue<pair<int,int>> q;     // {cost, node}

        dist[start] = 0;
        q.push({0, start});

        while (!q.empty()) {
            auto front = q.front();
            q.pop();

            int cost = front.first;
            int node = front.second;

            for (int m : arr) {
                int nxt = (node * m) % MOD;

                if (cost + 1 < dist[nxt]) {
                    dist[nxt] = cost + 1;

                    if (nxt == end)
                        return cost + 1;

                    q.push({cost + 1, nxt});
                }
            }
        }

        return -1;
    }
};

// --------------------------------------------
// Test case
// --------------------------------------------
int main() {
    Solution sol;

    vector<int> arr = {2, 5, 7};
    int start = 3;
    int end   = 30;

    int res = sol.minimumMultiplications(arr, start, end);
    cout << "Minimum Steps: " << res << endl;

    return 0;
}
