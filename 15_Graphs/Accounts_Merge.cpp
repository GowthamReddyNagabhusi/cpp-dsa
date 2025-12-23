// Problem : Accounts Merge
// LC : https://leetcode.com/problems/accounts-merge/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Disjoint Set Union (Union by Size + Path Compression)
// ============================================================
class Disjoint {
    vector<int> parent, size;

public:
    Disjoint(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findP(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = findP(parent[x]);
    }

    void UnionBySize(int x, int y) {
        int px = findP(x);
        int py = findP(y);

        if (px == py) return;

        if (size[px] < size[py]) {
            parent[px] = py;
            size[py] += size[px];
        } else {
            parent[py] = px;
            size[px] += size[py];
        }
    }
};

// ============================================================
// Approach:
// 1. Each account index is treated as a node in DSU.
// 2. Use a hashmap to map each email → first account index seen.
// 3. If an email is already seen, union the current account
//    with the previously stored account index.
// 4. After building DSU, group emails by their ultimate parent.
// 5. For each group:
//      - Account name comes from the parent index.
//      - Emails are sorted lexicographically.
// 6. Return merged accounts.
// ============================================================

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, int> emailToAcc;
        int n = accounts.size();

        Disjoint dsu(n);

        // Step 1: Union accounts sharing the same email
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string email = accounts[i][j];

                if (emailToAcc.count(email)) {
                    dsu.UnionBySize(i, emailToAcc[email]);
                } else {
                    emailToAcc[email] = i;
                }
            }
        }

        // Step 2: Group emails by parent account
        unordered_map<int, vector<string>> groups;
        for (auto &it : emailToAcc) {
            int parent = dsu.findP(it.second);
            groups[parent].push_back(it.first);
        }

        // Step 3: Build answer
        vector<vector<string>> ans;
        for (auto &grp : groups) {
            vector<string> temp;
            temp.push_back(accounts[grp.first][0]); // account name

            sort(grp.second.begin(), grp.second.end());
            for (string &email : grp.second)
                temp.push_back(email);

            ans.push_back(temp);
        }

        return ans;
    }
};

// ============================================================
// Test case
// ============================================================
int main() {
    Solution sol;

    vector<vector<string>> accounts = {
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"Mary", "mary@mail.com"},
        {"John", "johnnybravo@mail.com"}
    };

    vector<vector<string>> res = sol.accountsMerge(accounts);

    for (auto &acc : res) {
        for (auto &s : acc) cout << s << " ";
        cout << endl;
    }

    return 0;
}
