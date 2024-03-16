#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    vector<vector<int>> adj(n + 1, vector<int>());
    // dfs_graph
    vector<bool> vis(n + 1, 0);
    auto dfs = [&](auto self, int u) -> void {
        if (vis[u]) return;
        vis[u] = true;
        for (auto v: adj[u]) {
            if(vis[v]) continue;
            self(self, v);
        }
    };
    dfs(dfs, 1);
    // bfs
    vector<int> deep(n + 1, 1e9);
    queue<int> q;
    auto bfs = [&](auto self, int u) -> void {
        vis[u] = true;
        deep[u] = 0;
        q.push(u);
        while (!q.empty()) {
            int now = q.front(); q.pop();
            for (auto nxt : adj[now]) {
                if(vis[nxt]) continue;
                vis[nxt] = true;
                deep[nxt] = deep[now] + 1;
                q.push(nxt);
            }
        }
    };
    bfs(bfs, 1);
}