// Problem : Critical Connections in a Network
// LC : https://leetcode.com/problems/critical-connections-in-a-network/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach : DFS + Tarjan's Algorithm (Bridges in Graph)
// ============================================================
// Definitions:
// tin[u]  -> time of insertion of node u in DFS
// low[u]  -> lowest tin reachable from u (including back edges)
//
// Bridge condition:
// Edge (u, v) is a bridge if
// low[v] > tin[u]
//
// Steps:
// 1. Build adjacency list
// 2. Run DFS from every unvisited node (graph may be disconnected)
// 3. Maintain tin[] and low[] arrays
// 4. Apply bridge condition during DFS backtracking
// ============================================================

class Solution {
private:
    int timer = 1;

    void dfs(int node, int parent,
             vector<vector<int>>& adj,
             vector<int>& vis,
             vector<int>& tin,
             vector<int>& low,
             vector<vector<int>>& bridges) {

        vis[node] = 1;
        tin[node] = low[node] = timer++;
        
        for (auto it : adj[node]) {
            if (it == parent) continue;

            if (!vis[it]) {
                dfs(it, node, adj, vis, tin, low, bridges);

                low[node] = min(low[node], low[it]);

                // Bridge condition
                if (low[it] > tin[node]) {
                    bridges.push_back({node, it});
                }
            }
            else {
                // Back edge
                low[node] = min(low[node], tin[it]);
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(
        int n, vector<vector<int>>& connections) {

        vector<vector<int>> adj(n);
        for (auto &it : connections) {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        vector<int> vis(n, 0), tin(n), low(n);
        vector<vector<int>> bridges;

        // Graph may be disconnected
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, -1, adj, vis, tin, low, bridges);
            }
        }

        return bridges;
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    Solution sol;

    int n = 4;
    vector<vector<int>> connections = {
        {0,1}, {1,2}, {2,0}, {1,3}
    };

    vector<vector<int>> ans = sol.criticalConnections(n, connections);

    cout << "Critical Connections:\n";
    for (auto &e : ans) {
        cout << e[0] << " " << e[1] << "\n";
    }

    return 0;
}
