// Problem : Making A Large Island
// LC : https://leetcode.com/problems/making-a-large-island/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Disjoint Set Union (Union by Size + Path Compression)
// ============================================================
class Disjoint {
    vector<int> parent;
public:
    vector<int> size;

    Disjoint(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findP(int u) {
        if (parent[u] == u) return u;
        return parent[u] = findP(parent[u]);
    }

    void UnionBySize(int u, int v) {
        int pu = findP(u);
        int pv = findP(v);
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
// Approach:
// 1. Treat each cell as a node: id = (row * n + col).
// 2. Union all adjacent land cells (value = 1).
// 3. For each water cell (0):
//      - Check its 4-direction neighbors.
//      - Collect unique parent components using a set.
//      - Sum their component sizes + 1 (flip current cell).
// 4. Track the maximum possible island size.
// 5. If no zero exists, return n * n.
// ============================================================

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        Disjoint dsu(n * n);

        // Step 1: Union adjacent land cells
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    if (i + 1 < n && grid[i + 1][j] == 1)
                        dsu.UnionBySize(i * n + j, (i + 1) * n + j);
                    if (j + 1 < n && grid[i][j + 1] == 1)
                        dsu.UnionBySize(i * n + j, i * n + (j + 1));
                }
            }
        }

        int max_size = 0;
        vector<int> dr = {1, -1, 0, 0};
        vector<int> dc = {0, 0, 1, -1};

        // Step 2: Try flipping each zero
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    unordered_set<int> comps;

                    for (int k = 0; k < 4; k++) {
                        int ni = i + dr[k];
                        int nj = j + dc[k];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n &&
                            grid[ni][nj] == 1) {
                            comps.insert(dsu.findP(ni * n + nj));
                        }
                    }

                    int curr = 1;
                    for (int c : comps)
                        curr += dsu.size[c];

                    max_size = max(max_size, curr);
                }
            }
        }

        // If no zero was flipped → whole grid is 1
        return (max_size == 0) ? n * n : max_size;
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    Solution sol;

    vector<vector<int>> grid = {
        {1, 0},
        {0, 1}
    };

    cout << "Largest Island Size: "
         << sol.largestIsland(grid) << endl;

    return 0;
}
