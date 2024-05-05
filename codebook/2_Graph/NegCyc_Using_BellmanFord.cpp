// 用 Bellman Ford 找負環
vector<array<int, 3>> graph;    // u, v, w
int main() {
    int src = 0;
    int n, m;    cin >> n >> m;
    vector<int> par(n + 1), dis(n + 1, 1e9);
    for (int i = 0; i < m; i++) {
        int a, b, w; cin >> a >> b >> w;
        graph.push_back({a, b, w});
    }
    dis[1] = 0;
    for (int i = 0; i <= n; i++) {
        src = 0;
        for (auto [u, v, w] : graph) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                par[v] = u;
                src = v;
            }
        }
    }
    if (src) {  // 到第 n + 1 次還在鬆弛
        vector<int> ans;
        cout << "YES" << endl;
        for (int i = 0; i <= n; i++) src = par[src]; // 找那個負環
        ans.push_back(src);
        for (int i = par[src]; i != src; i = par[i]) {  // 輸出負環
            ans.push_back(i);
        }
        ans.push_back(src);
        reverse(ans.begin(), ans.end());
        for (auto i : ans) {
            cout << i << " ";
        }
    }
    else {
        cout << "NO" << "\n";
    }
}