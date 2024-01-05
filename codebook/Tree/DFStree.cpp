int timer;
const int maxn = 200200;
int pos[maxn], sz[maxn];
vector<int> g[maxn];
void dfs(int now, int pa) {
    pos[now] = ++timer;
    sz[now] = 1;
    for (int v : g[now]) {
        if (v == pa) continue;
        dfs(v, now);
        sz[now] += sz[v];
    }
}
cout << query(pos[a] + sz[a] - 1) - query(pos[a] - 1) << "\n";