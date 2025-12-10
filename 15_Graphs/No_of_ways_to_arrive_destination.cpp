// Problem : Number of Ways to Arrive at Destination (Dijkstra + Path Counting)
// LC : https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------
// Approach:
// Modified Dijkstra:
// For each node, maintain:
//   - dis[node]  → shortest distance found so far
//   - ways[node] → number of shortest paths to reach node
//
// Steps:
// 1. Build adjacency list.
// 2. Initialize dis[] = INF, ways[] = 0.
//    dis[0] = 0, ways[0] = 1.
// 3. Use min-heap storing {distance, node}.
// 4. For each neighbor:
//      case A: Found shorter distance:
//          update dis[nbr]
//          ways[nbr] = ways[node]
//      case B: Found another equal shortest path:
//          ways[nbr] += ways[node]
//    (modulo 1e9+7)
// 5. Continue until Dijkstra completes.
// 6. Answer = ways[n-1].
// --------------------------------------------

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        const long long MOD = 1e9 + 7;

        vector<vector<pair<int,int>>> adj(n);
        for (auto &r : roads) {
            adj[r[0]].push_back({r[1], r[2]});
            adj[r[1]].push_back({r[0], r[2]});
        }

        vector<long long> dis(n, LLONG_MAX);
        vector<long long> ways(n, 0);

        priority_queue<
            pair<long long,int>,
            vector<pair<long long,int>>,
            greater<pair<long long,int>>
        > pq;

        dis[0] = 0;
        ways[0] = 1;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();

            long long d = top.first;
            int node = top.second;

            if (d > dis[node]) continue;

            for (auto &p : adj[node]) {
                int nbr = p.first;
                long long wt = p.second;

                if (d + wt < dis[nbr]) {
                    dis[nbr] = d + wt;
                    ways[nbr] = ways[node];
                    pq.push({dis[nbr], nbr});
                }
                else if (d + wt == dis[nbr]) {
                    ways[nbr] = (ways[nbr] + ways[node]) % MOD;
                }
            }
        }

        return (int)ways[n - 1];
    }
};

// --------------------------------------------
// Test case
// --------------------------------------------
int main() {
    Solution sol;

    int n = 7;
    vector<vector<int>> roads = {
        {0,6,7}, {0,1,2}, {1,2,3}, {1,3,3}, {6,3,3},
        {3,5,1}, {6,5,1}, {2,5,1}, {0,4,5}, {4,6,2}
    };

    int ans = sol.countPaths(n, roads);
    cout << "Number of Shortest Paths: " << ans << endl;

    return 0;
}
