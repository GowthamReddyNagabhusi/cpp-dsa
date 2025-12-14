// Problem : Find the City With the Smallest Number of Neighbors at a Threshold Distance
// LC : https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------
// Approach:
// Use Floyd–Warshall to compute all-pairs shortest paths.
//
// Steps:
// 1. Initialize dist matrix with INF, dist[i][i] = 0.
// 2. Fill distances using given edges (undirected graph).
// 3. Run Floyd–Warshall:
//        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]).
// 4. For each city i, count how many cities j have
//        dist[i][j] <= distanceThreshold.
// 5. Choose the city with the minimum such count.
//    If tie occurs, pick the city with the larger index.
// --------------------------------------------

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        const int INF = 1000000000;

        vector<vector<int>> dist(n, vector<int>(n, INF));

        for (int i = 0; i < n; i++)
            dist[i][i] = 0;

        for (auto &e : edges) {
            dist[e[0]][e[1]] = e[2];
            dist[e[1]][e[0]] = e[2];
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = min(dist[i][j],
                                          dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        pair<int,int> ans = {-1, INF};

        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (i != j && dist[i][j] <= distanceThreshold)
                    cnt++;
            }

            if (cnt <= ans.second)
                ans = {i, cnt};
        }

        return ans.first;
    }
};

// --------------------------------------------
// Test case
// --------------------------------------------
int main() {
    Solution sol;

    int n = 4;
    vector<vector<int>> edges = {
        {0,1,3}, {1,2,1}, {1,3,4}, {2,3,1}
    };
    int threshold = 4;

    cout << "City: " << sol.findTheCity(n, edges, threshold) << endl;
    return 0;
}
