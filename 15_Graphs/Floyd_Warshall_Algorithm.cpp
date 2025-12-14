// Problem : Floyd Warshall Algorithm
// GFG : https://www.geeksforgeeks.org/problems/implementing-floyd-warshall/1

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------
// Approach:
// Floyd–Warshall computes shortest paths between
// all pairs of vertices.
//
// Steps:
// 1. dist[i][j] represents the shortest distance
//    from node i to node j.
// 2. Use an intermediate node k:
//      Try to improve path i → j via k.
//      dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
// 3. Run three nested loops for k, i, j.
// 4. Works with negative edges (but no negative cycles).
// --------------------------------------------

class Solution {
public:
    void floydWarshall(vector<vector<int>> &dist) {
        int n = dist.size();

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != 1e8 && dist[k][j] != 1e8) {
                        dist[i][j] = min(dist[i][j],
                                          dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }
};

// --------------------------------------------
// Test case
// --------------------------------------------
int main() {
    Solution sol;

    const int INF = 100000000;

    vector<vector<int>> dist = {
    {0,   3,   INF, 7},
    {8,   0,   2,   INF},
    {5,   INF, 0,   1},
    {2,   INF, INF, 0}
    };


    sol.floydWarshall(dist);

    cout << "All-pairs shortest paths:\n";
    for (auto &row : dist) {
        for (int x : row) {
            if (x == 1e8) cout << "INF ";
            else cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}
