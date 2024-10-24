// Flight Discount
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll inf = 1E18;

void dijkstra() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].emplace_back(v, w);
    }

    vector<ll> dis(n * 2, inf);
    vector<int> vis(n * 2);
    priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
    
    dis[0] = 0;
    pq.emplace(0, 0, 0);
    while (!pq.empty()) {
        auto [d, u, c] = pq.top();
        pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        u /= 2;
        for (auto [v, w] : g[u]) {
            ll ndis = d + w;
            int nv = v * 2 + c;
            if (dis[nv] > ndis) {
                dis[nv] = ndis;
                pq.emplace(ndis, nv, c);
            }
            if (!c) {
                ndis = d + w / 2;
                nv = v * 2 + 1;
                if (dis[nv] > ndis) {
                    dis[nv] = ndis;
                    pq.emplace(ndis, nv, 1);
                }
            }
        }
    }
    cout << dis[n * 2 - 1] << "\n";
    return 0;
}