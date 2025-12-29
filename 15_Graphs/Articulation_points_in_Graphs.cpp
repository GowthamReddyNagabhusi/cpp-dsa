// Problem : Articulation Points in Graph
// GFG : https://practice.geeksforgeeks.org/problems/articulation-point-1/1

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach : DFS + Tarjan's Algorithm (Articulation Points)
// ============================================================
// Definitions:
// tin[u]  -> time of insertion of node u
// low[u]  -> lowest tin reachable from u
//
// Articulation Point Conditions:
// 1. Root node:
//    - If it has more than 1 DFS child
//
// 2. Non-root node u:
//    - If there exists a child v such that
//      low[v] >= tin[u]
//
// Steps:
// 1. Run DFS from every unvisited node (graph may be disconnected)
// 2. Maintain tin[] and low[]
// 3. Track DFS children count for root
// 4. Mark articulation points using above rules
// ============================================================

class Solution {
private:
    int timer = 0;

    void dfs(int node, int parent,
             vector<int>& tin,
             vector<int>& low,
             vector<int>& vis,
             vector<int> adj[],
             vector<int>& mark) {

        vis[node] = 1;
        tin[node] = low[node] = timer++;
        int child = 0;

        for (auto it : adj[node]) {
            if (it == parent) continue;

            if (!vis[it]) {
                dfs(it, node, tin, low, vis, adj, mark);
                low[node] = min(low[node], low[it]);

                // Non-root articulation condition
                if (low[it] >= tin[node] && parent != -1) {
                    mark[node] = 1;
                }

                child++;
            }
            else {
                // Back edge
                low[node] = min(low[node], tin[it]);
            }
        }

        // Root articulation condition
        if (parent == -1 && child > 1) {
            mark[node] = 1;
        }
    }

public:
    vector<int> articulationPoints(int V, vector<int> adj[]) {

        vector<int> tin(V), low(V), vis(V, 0), mark(V, 0);
        vector<int> ans;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, -1, tin, low, vis, adj, mark);
            }
        }

        for (int i = 0; i < V; i++) {
            if (mark[i]) ans.push_back(i);
        }

        if (ans.empty()) return {-1};
        return ans;
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    int V = 5;
    vector<int> adj[V];

    adj[0] = {1, 2};
    adj[1] = {0, 2};
    adj[2] = {0, 1, 3, 4};
    adj[3] = {2};
    adj[4] = {2};

    Solution sol;
    vector<int> ans = sol.articulationPoints(V, adj);

    cout << "Articulation Points:\n";
    for (int x : ans) cout << x << " ";
    cout << endl;

    return 0;
}
