// Problem : Number of Operations to Make Network Connected
// LC : https://leetcode.com/problems/number-of-operations-to-make-network-connected/

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------
// Disjoint Set Union (Union by Size + Extra Edge Count)
// --------------------------------------------
class DisjointSet {
    vector<int> parent, size;
    int extra;   // counts redundant edges

public:
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
        extra = 0;
    }

    int findUPar(int node) {
        if (parent[node] == node)
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionBySize(int u, int v) {
        int pu = findUPar(u);
        int pv = findUPar(v);

        if (pu == pv) {
            extra++;   // redundant edge
            return;
        }

        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }

    // --------------------------------------------
    // Compute minimum operations needed
    // --------------------------------------------
    int Ops(int n) {
        int components = 0;

        for (int i = 0; i < n; i++) {
            if (parent[i] == i)
                components++;
        }

        if (components == 1) return 0;

        // Need (components - 1) edges to connect all components
        if (extra >= components - 1)
            return components - 1;

        return -1;
    }
};

// --------------------------------------------
// Approach:
// 1. Use DSU to connect nodes.
// 2. Count redundant edges (extra).
// 3. Count number of connected components.
// 4. To connect C components, need at least (C - 1) edges.
// 5. If extra edges ≥ (C - 1) → possible, else impossible.
// --------------------------------------------

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        DisjointSet ds(n);

        for (auto &c : connections) {
            ds.unionBySize(c[0], c[1]);
        }

        return ds.Ops(n);
    }
};

// --------------------------------------------
// Test case
// --------------------------------------------
int main() {
    Solution sol;

    int n = 6;
    vector<vector<int>> connections = {
        {0,1}, {0,2}, {0,3}, {1,2}, {1,3}
    };

    cout << "Minimum Operations: "
         << sol.makeConnected(n, connections) << endl;

    return 0;
}
