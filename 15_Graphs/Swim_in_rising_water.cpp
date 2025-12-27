// Problem : Swim in Rising Water
// LC : https://leetcode.com/problems/swim-in-rising-water/

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

// ============================================================
// Approach (DSU + Sorting / Kruskal-like):
// 1. Each cell is a node: id = row * n + col.
// 2. Sort all cells by their height (time).
// 3. Activate cells one by one in increasing height order.
// 4. When a cell is activated, union it with all already-
//    active neighboring cells (4 directions).
// 5. As soon as start (0,0) and end (n-1,n-1) belong to the
//    same DSU component, current height is the answer.
// ============================================================

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        DisjointSet dsu(n * n);

        vector<pair<int, pair<int,int>>> cells;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cells.push_back({grid[i][j], {i, j}});
            }
        }

        sort(cells.begin(), cells.end());

        vector<vector<int>> active(n, vector<int>(n, 0));
        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};

        for (auto &it : cells) {
            int time = it.first;
            int r = it.second.first;
            int c = it.second.second;

            active[r][c] = 1;

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n &&
                    active[nr][nc]) {
                    dsu.unionBySize(r * n + c, nr * n + nc);
                }
            }

            // Check connectivity
            if (dsu.findUPar(0) == dsu.findUPar(n * n - 1))
                return time;
        }

        return -1;
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    Solution sol;

    vector<vector<int>> grid = {
        {0, 2},
        {1, 3}
    };

    cout << "Minimum Time: "
         << sol.swimInWater(grid) << endl;

    return 0;
}
