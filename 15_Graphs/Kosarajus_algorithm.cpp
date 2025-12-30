// Problem : Strongly Connected Components (Kosaraju's Algorithm)
// GFG : https://practice.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Approach : Kosaraju’s Algorithm (SCC in Directed Graph)
// ============================================================
// Idea:
// 1. Perform DFS and store nodes in stack according to finish time
// 2. Reverse the graph
// 3. Pop nodes from stack and run DFS on reversed graph
// 4. Each DFS call in step 3 gives one SCC
//
// Why it works:
// - Nodes finishing last in original graph are SCC roots in reversed graph
// ============================================================

class Solution {
private:
    // Step 1: DFS to store nodes by finish time
    void dfs1(int node, vector<int>& vis,
              stack<int>& st, vector<vector<int>>& adj) {

        vis[node] = 1;
        for (auto it : adj[node]) {
            if (!vis[it]) {
                dfs1(it, vis, st, adj);
            }
        }
        st.push(node);
    }

    // Step 3: DFS on reversed graph
    void dfs2(int node, vector<int>& vis,
              vector<vector<int>>& rev_adj) {

        vis[node] = 1;
        for (auto it : rev_adj[node]) {
            if (!vis[it]) {
                dfs2(it, vis, rev_adj);
            }
        }
    }

public:
    int kosaraju(vector<vector<int>>& adj) {

        int n = adj.size();
        vector<int> vis(n, 0);
        stack<int> st;

        // Step 1: Order nodes by finish time
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs1(i, vis, st, adj);
            }
        }

        // Step 2: Reverse the graph
        vector<vector<int>> rev_adj(n);
        for (int i = 0; i < n; i++) {
            for (auto it : adj[i]) {
                rev_adj[it].push_back(i);
            }
        }

        // Step 3: Process nodes in stack order
        fill(vis.begin(), vis.end(), 0);
        int scc = 0;

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!vis[node]) {
                scc++;
                dfs2(node, vis, rev_adj);
            }
        }

        return scc;
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    vector<vector<int>> adj = {
        {1},
        {2},
        {0, 3},
        {4},
        {}
    };

    Solution sol;
    cout << "Number of SCCs: " << sol.kosaraju(adj) << endl;

    return 0;
}
