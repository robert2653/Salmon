// Flight Discount
void dijkstra() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>(n));
    vector<array<int, 2>> dis(n, {inf, inf});    // 0 for not used
    for (int i = 1; i <= m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> pq;  // 0 for w, 1 for u, 2 for discount
    dis[0][0] = dis[0][1] = 0;
    pq.emplace(0, 0, 0);
    while (!pq.empty()) {
        auto [dist, u, us] = pq.top(); pq.pop();
        if (dis[u][us] < dist) continue;
        if (us) {
            for (auto [v, w] : adj[u]) {
                if (dis[u][1] + w < dis[v][1]) {
                    dis[v][1] = dis[u][1] + w;
                    pq.emplace(dis[v][1], v, 1);
                }
            }
        }
        else {
            for (auto [v, w] : adj[u]) {
                if (dis[u][0] + w < dis[v][0]) {
                    dis[v][0] = dis[u][0] + w;
                    pq.emplace(dis[v][0], v, 0);
                }
                if (dis[u][0] + w / 2 < dis[v][1]) {
                    dis[v][1] = dis[u][0] + w / 2;
                    pq.emplace(dis[v][1], v, 1);
                }
            }
        }
    }
    cout << min(dis[n - 1][0], dis[n - 1][1]);
}