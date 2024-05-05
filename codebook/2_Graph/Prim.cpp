int n, m, ans = 0;
const int maxn = 2e5 + 5;
vector<pair<int, int>> adj[maxn];
bool Prim() {
    int node_sz = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 1});
    bool vis[maxn] = {false};
    while (!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        ans += cost;
        node_sz++;
        for(auto [v, cost] : adj[u]) {
            if (!vis[v])
                pq.push({cost, v});
        }
    }
    if (node_sz == n) return true;
    return false;
}
void solve() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v, cost; cin >> u >> v >> cost;
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});
    }
    if (Prim()) cout << ans;
    else cout << "IMPOSSIBLE";
}