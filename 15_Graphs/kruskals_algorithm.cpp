// Problem : Minimum Spanning Tree (Kruskal's Algorithm)
// GFG : https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------
// Disjoint Set Union (Union by Size + Path Compression)
// --------------------------------------------
class DisjointSet {
    vector<int> parent, size;

public:
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findUPar(int node) {
        if (parent[node] == node)
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionBySize(int u, int v) {
        int pu = findUPar(u);
        int pv = findUPar(v);

        if (pu == pv) return;

        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

// --------------------------------------------
// Approach (Kruskal’s Algorithm):
// 1. Sort all edges by weight.
// 2. Initialize DSU for cycle detection.
// 3. Iterate over edges in increasing weight order.
// 4. If edge connects two different components:
//        - Include it in MST
//        - Union the components
// 5. Stop after processing all edges.
// --------------------------------------------

class Solution {
public:
    int kruskalsMST(int V, vector<vector<int>> &edges) {

        sort(edges.begin(), edges.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[2] < b[2];
             });

        DisjointSet ds(V);
        int mstWt = 0;

        for (auto &e : edges) {
            int u  = e[0];
            int v  = e[1];
            int wt = e[2];

            if (ds.findUPar(u) != ds.findUPar(v)) {
                mstWt += wt;
                ds.unionBySize(u, v);
            }
        }

        return mstWt;
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

    cout << "MST Weight: " << sol.kruskalsMST(V, edges) << endl;
    return 0;
}
