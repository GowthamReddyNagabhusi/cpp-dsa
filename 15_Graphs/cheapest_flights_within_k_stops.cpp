// Problem : Cheapest Flights Within K Stops (BFS + Relaxation)
// LC : https://leetcode.com/problems/cheapest-flights-within-k-stops/

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------
// Approach:
// BFS-like traversal with (node, cost, stops) but with relaxation.
// 1. Build adjacency list: u -> {v, price}.
// 2. Maintain a distance array dist[] storing best cost found so far.
// 3. Push {0 stops, src, cost 0} into queue.
// 4. Pop each state:
//        If stops > k → skip.
//        For each neighbor:
//            If cost + edgeCost < dist[nbr]:
//                 update dist[nbr]
//                 push next state with stops+1
// 5. BFS ensures we explore all routes with <= k stops, but only
//    continue if we find a cheaper cost.
// 6. If dist[dst] was updated → return it, otherwise return -1.
// --------------------------------------------

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int,int>>> adj(n);
        for (auto &f : flights) {
            adj[f[0]].push_back({f[1], f[2]});
        }

        vector<int> dist(n, INT_MAX);

        queue<pair<int, pair<int,int>>> q; 
        // {stops, {node, cost}}

        q.push({0, {src, 0}});
        dist[src] = 0;

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();

            int stops = cur.first;
            int node  = cur.second.first;
            int cost  = cur.second.second;

            if (stops > k) continue;

            for (auto &nbr : adj[node]) {
                int nextNode = nbr.first;
                int price    = nbr.second;

                if (cost + price < dist[nextNode]) {
                    dist[nextNode] = cost + price;
                    q.push({stops + 1, {nextNode, cost + price}});
                }
            }
        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};

// --------------------------------------------
// Test case
// --------------------------------------------
int main() {
    Solution sol;

    int n = 4;
    vector<vector<int>> flights = {
        {0,1,100},
        {1,2,100},
        {2,3,100},
        {0,2,500}
    };
    int src = 0, dst = 3, k = 1;

    int cost = sol.findCheapestPrice(n, flights, src, dst, k);
    cout << "Minimum Cost: " << cost << endl;

    return 0;
}
