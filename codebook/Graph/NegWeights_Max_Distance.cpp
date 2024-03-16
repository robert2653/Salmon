#include <bits/stdc++.h>
using namespace std;
// CSES High Score
const int maxn = 2505;
vector<array<int, 3>> graph;    // u, v, w
vector<pair<int, int>> adj[maxn];
vector<int> rev_adj[maxn];
int dis[maxn];
bool vis[maxn];
bool nvis[maxn];
void dfs(int par, int now){
    if (vis[now] == 1) return;
    vis[now] = 1;
    for (auto [i, w] : adj[now]){
        if (i != par){
            dfs(now, i);
        }
    }
}
void rev_dfs(int par, int now){
    if (nvis[now] == 1) return;
    nvis[now] = 1;
    for (auto i : rev_adj[now]){
        if (i != par){
            rev_dfs(now, i);
        }
    }
}
void solve(){
    int n, m; cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph.push_back({u, v, w});
        adj[u].push_back({v, w});
        rev_adj[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) dis[i] = -1e9;
    dis[1] = 0;
    for(int i = 1; i <= n; i++){
        for (auto [u, v, w] : graph){
            if (dis[u] + w > dis[v]){
                dis[v] = dis[u] + w;
            }
        }
    }
    dfs(0, 1);
    rev_dfs(0, n);
    for (auto [u, v, w] : graph){
        if (dis[u] + w > dis[v] && nvis[u] && nvis[v] && vis[u] && vis[v]){
            cout << -1; // 無限多的分數
            return;
        }
    }
    cout << dis[n];
}