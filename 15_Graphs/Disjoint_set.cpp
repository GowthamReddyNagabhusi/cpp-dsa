#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> parent, rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int findUPar(int node) {
        if (parent[node] == node)
            return node;
        return parent[node] = findUPar(parent[node]); // path compression
    }

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
};

// --------------------------------------------
// Test cases
// --------------------------------------------
int main() {

    // Test case 1: Basic unions
    cout << "Test Case 1:\n";
    DisjointSet ds1(7);

    ds1.unionByRank(1, 2);
    ds1.unionByRank(2, 3);
    ds1.unionByRank(4, 5);
    ds1.unionByRank(6, 5);

    if (ds1.findUPar(3) == ds1.findUPar(1))
        cout << "1 and 3 are in the same set\n";
    else
        cout << "1 and 3 are NOT in the same set\n";

    if (ds1.findUPar(4) == ds1.findUPar(6))
        cout << "4 and 6 are in the same set\n";
    else
        cout << "4 and 6 are NOT in the same set\n";

    if (ds1.findUPar(3) == ds1.findUPar(5))
        cout << "3 and 5 are in the same set\n";
    else
        cout << "3 and 5 are NOT in the same set\n";

    cout << "\n";

    // Test case 2: Connecting all nodes
    cout << "Test Case 2:\n";
    DisjointSet ds2(5);

    ds2.unionByRank(0, 1);
    ds2.unionByRank(1, 2);
    ds2.unionByRank(3, 4);
    ds2.unionByRank(2, 4);

    for (int i = 0; i < 5; i++) {
        cout << "Parent of " << i << " is " << ds2.findUPar(i) << "\n";
    }

    cout << "\n";

    // Test case 3: No unions
    cout << "Test Case 3:\n";
    DisjointSet ds3(4);

    for (int i = 0; i < 4; i++) {
        cout << "Parent of " << i << " is " << ds3.findUPar(i) << "\n";
    }

    return 0;
}
