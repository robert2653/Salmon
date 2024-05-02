#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
vector<int> graph[maxn];
int color[maxn], parent[maxn];
bool vis[maxn];
int n, m;
void print_ans(int ori) {
    int now = parent[ori];
    deque<int> ans;
    ans.push_front(ori);
    while (now != ori) {
        ans.push_front(now);
        now = parent[now];
    }
    ans.push_front(ori);
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i << " ";
    }
    exit(0);
}
void dfs(int now) {
    color[now] = 1;
    vis[now] = 1;
    for (auto nxt : graph[now]) {
        parent[nxt] = now;
        if (color[nxt] == 1) {
            print_ans(nxt);
        }
        else if (color[nxt] == 0) {
            dfs(nxt);
        }
    }
    color[now] = 2;
}
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            dfs(i);
    }
    cout << "IMPOSSIBLE";
}