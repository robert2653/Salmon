// CSES Longest Flight Route
// 只能用在 DAG，用拓樸按順序鬆弛
void print_ans(int n, vector<int> &par) {
    deque<int> ans;
    int now = n;
    while(now != 0) {
        ans.push_front(now);
        now = par[now];
    }
    ans.push_front(0);
    cout << ans.size() << "\n";
    for(auto i : ans) {
        cout << i << " ";
    }
}
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> graph(n);
    vector<int> dis(n, -1e9); dis[1] = 0;
    vector<int> par(n), in(n);
    queue<int> q;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        in[v]++;
    }
    for (int i = 0; i < n; i++) {
        if (in[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : graph[u]) {
            if (dis[v] < dis[u] + 1) {  // 鬆弛
                dis[v] = dis[u] + 1;
                par[v] = u;
            }
            in[v]--;
            if (in[v] == 0) q.push(v);
        }
    }
    if (dis[n - 1] < 0) {
        // 如果 1 不能到達 n，n 也有可能被鬆弛
        // 所以要看的是 dis[n] < 0
        cout << "IMPOSSIBLE";
    }
    else print_ans(n, par);
}