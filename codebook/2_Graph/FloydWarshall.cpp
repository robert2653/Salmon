const int inf = 1e18;
int main() {
    int n, m, q; cin >> n >> m >> q;
    vector<vector<int>> graph(n, vector<int>(n, inf));
    vector<vector<int>> dis(n, vector<int>(n));
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        graph[u][v] = min(graph[u][v], w);
        graph[v][u] = min(graph[v][u], w);
    }
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            dis[i][j] = graph[i][j];
        }   
    }
    for (int i = 0; i < n; i++) // 自己到自己是 0
        dis[i][i] = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        cout << (dis[u][v] >= inf ? -1 : dis[u][v]) << "\n";
    }
}