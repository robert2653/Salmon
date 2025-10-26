auto prim = [&](int n, vector<vector<pair<int, int>>> &adj) -> bool {
    int sz = 0; ll ans = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, 0); // w, vertex
    vector<bool> vis(n);
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        ans += w, sz++;
        for (auto [v, w] : g[u])
            if (!vis[v]) pq.emplace(w, v);
    }
    if (sz == n) return true;
    return false;
};