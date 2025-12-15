// Problem : Minimum Spanning Tree (Prim's Algorithm)
// GFG : https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------
// Approach:
// Use Prim's Algorithm to construct the MST.
//
// Steps:
// 1. Build adjacency list for the undirected weighted graph.
// 2. Use a min-heap (priority_queue) storing {edgeWeight, node}.
// 3. Start from node 0 with weight 0.
// 4. At each step:
//      - Pick the node with minimum edge weight.
//      - If already visited, skip.
//      - Mark visited and add weight to MST sum.
//      - Push all adjacent edges of this node into the heap.
// 5. Continue until all vertices are included.
// --------------------------------------------

class Solution {
public:
    int spanningTree(int V, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> adj(V);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int wt = e[2];
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }

        vector<int> vis(V, 0);
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;

        pq.push({0, 0});   // {weight, node}
        int sum = 0;

        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();

            int wt = top.first;
            int u  = top.second;

            if (vis[u]) continue;

            vis[u] = 1;
            sum += wt;

            for (auto &it : adj[u]) {
                int v   = it.first;
                int eWt = it.second;
                if (!vis[v]) {
                    pq.push({eWt, v});
                }
            }
        }

        return sum;
    }
};

// --------------------------------------------
// Test case
// --------------------------------------------
int main() {
    Solution sol;

    int V = 5;
    vector<vector<int>> edges = {
        {0,1,2}, {0,3,6}, {1,2,3},
        {1,3,8}, {1,4,5}, {2,4,7}
    };

    cout << "MST Weight: " << sol.spanningTree(V, edges) << endl;
    return 0;
}
