#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> parent, rank, size;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int findUPar(int node) {
        if (parent[node] == node)
            return node;
        return parent[node] = findUPar(parent[node]); // path compression
    }

    // -----------------------------
    // Union by Rank
    // -----------------------------
    void unionByRank(int u, int v) {
        int upu = findUPar(u);
        int upv = findUPar(v);

        if (upu == upv) return;

        if (rank[upu] < rank[upv]) {
            parent[upu] = upv;
        }
        else if (rank[upu] > rank[upv]) {
            parent[upv] = upu;
        }
        else {
            parent[upv] = upu;
            rank[upu]++;
        }
    }

    // -----------------------------
    // Union by Size
    // -----------------------------
    void unionBySize(int u, int v) {
        int upu = findUPar(u);
        int upv = findUPar(v);

        if (upu == upv) return;

        if (size[upu] < size[upv]) {
            parent[upu] = upv;
            size[upv] += size[upu];
        } else {
            parent[upv] = upu;
            size[upu] += size[upv];
        }
    }
};

// --------------------------------------------
// Test cases
// --------------------------------------------
int main() {

    // Test case 1: Union by Rank
    cout << "Test Case 1 (Union by Rank):\n";
    DisjointSet ds1(7);

    ds1.unionByRank(1, 2);
    ds1.unionByRank(2, 3);
    ds1.unionByRank(4, 5);
    ds1.unionByRank(6, 5);

    cout << (ds1.findUPar(1) == ds1.findUPar(3) ? "1 & 3 connected\n" : "1 & 3 not connected\n");
    cout << (ds1.findUPar(4) == ds1.findUPar(6) ? "4 & 6 connected\n" : "4 & 6 not connected\n");
    cout << (ds1.findUPar(3) == ds1.findUPar(5) ? "3 & 5 connected\n" : "3 & 5 not connected\n");

    cout << "\n";

    // Test case 2: Union by Size
    cout << "Test Case 2 (Union by Size):\n";
    DisjointSet ds2(6);

    ds2.unionBySize(0, 1);
    ds2.unionBySize(1, 2);
    ds2.unionBySize(3, 4);
    ds2.unionBySize(2, 4);

    for (int i = 0; i < 6; i++) {
        cout << "Parent of " << i << " is " << ds2.findUPar(i) << "\n";
    }

    cout << "\n";

    // Test case 3: Mixed usage
    cout << "Test Case 3 (Mixed):\n";
    DisjointSet ds3(5);

    ds3.unionBySize(0, 1);
    ds3.unionByRank(2, 3);
    ds3.unionBySize(1, 2);

    cout << (ds3.findUPar(0) == ds3.findUPar(3) ? "0 & 3 connected\n" : "0 & 3 not connected\n");
    cout << (ds3.findUPar(4) == ds3.findUPar(0) ? "4 & 0 connected\n" : "4 & 0 not connected\n");

    return 0;
}
