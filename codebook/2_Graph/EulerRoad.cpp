// 無向圖、尤拉環: 檢查每個點的出度為偶數
// 有向圖、尤拉路: 可以看成 1 走到 n，所以檢查所有點的出度等於入度
int n, m;
const int maxn = 1e5 + 5;
vector<set<int>> adj;
vector<int> in;
void dfs(int now, vector<int> &road) {
    while (!adj[now].empty()) {
        int nxt = *adj[now].begin();
        adj[now].erase(nxt);
        dfs(nxt, road);
    }
    road.push_back(now);
}
void solve() {
    cin >> n >> m;
    in.assign(n + 1, 0);
    adj.assign(n + 1, set<int>());
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].insert(v);
        in[v]++;
    }
    in[1]++;
    in[n]--;
    for (int i = 1; i <= n; i++) {
        if(adj[i].size() != in[i]) {
            cout << "IMPOSSIBLE";
            return;
        }
    }
    vector<int> road;
    dfs(1, road);
    if (road.size() != m + 1) {
        cout << "IMPOSSIBLE";
        return;
    }
    reverse(road.begin(), road.end());
    for(auto i : road) cout << i << " ";
}