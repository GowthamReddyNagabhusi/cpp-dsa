// Problem : Bellman Ford Algorithm
// GFG : https://www.geeksforgeeks.org/problems/bellman-ford-algorithm/1

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------
// Approach:
// Bellman-Ford finds shortest paths from a source
// in a graph that may contain negative edge weights.
//
// Steps:
// 1. Initialize distance array with INF, dist[src] = 0.
// 2. Relax all edges exactly (V - 1) times:
//      For each edge (u -> v with weight wt):
//          if dist[u] + wt < dist[v], update dist[v].
// 3. Perform one extra relaxation pass to detect
//    negative weight cycles.
//    If any distance can still be reduced → cycle exists.
// --------------------------------------------

class Solution {
public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        vector<int> dist(V, 1e8);
        dist[src] = 0;

        // Step 1 & 2: Relax edges V-1 times
        for (int i = 0; i < V - 1; i++) {
            for (auto &e : edges) {
                int u = e[0];
                int v = e[1];
                int wt = e[2];

                if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }

        // Step 3: Detect negative cycle
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int wt = e[2];

            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                return {-1};   // Negative cycle detected
            }
        }

        return dist;
    }
};

// --------------------------------------------
// Test case
// --------------------------------------------
int main() {
    Solution sol;

    int V = 5;
    vector<vector<int>> edges = {
        {0,1,-1}, {0,2,4}, {1,2,3},
        {1,3,2}, {1,4,2}, {3,2,5},
        {3,1,1}, {4,3,-3}
    };

    int src = 0;
    vector<int> dist = sol.bellmanFord(V, edges, src);

    if (dist.size() == 1 && dist[0] == -1) {
        cout << "Negative weight cycle detected\n";
    } else {
        cout << "Shortest distances: ";
        for (int d : dist) cout << d << " ";
        cout << endl;
    }

    return 0;
}
