// Problem : Most Stones Removed with Same Row or Column
// LC : https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Disjoint Set Union (Union by Size + Path Compression)
// ============================================================
class DisjointSet {
    vector<int> parent, size;

public:
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int findUPar(int node) {
        if (parent[node] == node) return node;
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

// ============================================================
// Solution 1
// DSU on Stone Indices (Row/Column Mapping using HashMaps)
// ============================================================
// Approach:
// 1. Treat each stone as a node.
// 2. If two stones share the same row or column,
//    connect their indices using DSU.
// 3. Use hash maps to remember the first stone seen
//    in each row and column.
// 4. After building DSU, count connected components.
// 5. From each component, we can remove all stones except one.
//    Answer = total stones - number of components.
// ============================================================

class Solution1 {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        unordered_map<int,int> rowMap, colMap;
        vector<pair<int,int>> edges;

        for (int i = 0; i < n; i++) {
            int r = stones[i][0];
            int c = stones[i][1];

            if (rowMap.count(r)) edges.push_back({rowMap[r], i});
            else rowMap[r] = i;

            if (colMap.count(c)) edges.push_back({colMap[c], i});
            else colMap[c] = i;
        }

        DisjointSet ds(n);
        for (auto &e : edges) {
            ds.unionBySize(e.first, e.second);
        }

        int components = 0;
        for (int i = 0; i < n; i++) {
            if (ds.findUPar(i) == i) components++;
        }

        return n - components;
    }
};

// ============================================================
// Solution 2
// DSU on Rows + Columns (Bipartite Graph Technique)
// ============================================================
// Approach:
// 1. Treat each row and each column as a node.
// 2. For every stone (r, c), connect row-node r
//    with column-node (c + offset).
// 3. Track only the nodes that actually appear.
// 4. Count number of connected components among used nodes.
// 5. Each connected component can leave only one stone.
//    Answer = total stones - components.
// ============================================================

class Solution2 {
public:
    int removeStones(vector<vector<int>>& stones) {
        int maxRow = 0, maxCol = 0;
        for (auto &s : stones) {
            maxRow = max(maxRow, s[0]);
            maxCol = max(maxCol, s[1]);
        }

        DisjointSet ds(maxRow + maxCol + 2);
        unordered_set<int> used;

        for (auto &s : stones) {
            int r = s[0];
            int c = s[1] + maxRow + 1;
            ds.unionBySize(r, c);
            used.insert(r);
            used.insert(c);
        }

        int components = 0;
        for (int node : used) {
            if (ds.findUPar(node) == node)
                components++;
        }

        return stones.size() - components;
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    vector<vector<int>> stones = {
        {0,0}, {0,1}, {1,0}, {1,2}, {2,1}, {2,2}
    };

    Solution1 sol1;
    Solution2 sol2;

    cout << "Solution 1 Answer: " << sol1.removeStones(stones) << endl;
    cout << "Solution 2 Answer: " << sol2.removeStones(stones) << endl;

    return 0;
}
