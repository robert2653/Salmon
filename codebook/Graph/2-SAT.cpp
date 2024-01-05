#include <bits/stdc++.h>
using namespace std;
// +(-) u or +(-) v
const int maxn = 1e5 + 5;
vector<int> adj[2 * maxn], rev_adj[2 * maxn];
vector<int> order;
int cat[2 * maxn];
int k = 1;
bool vis[2 * maxn];
void dfs(int now){
    if (!vis[now]){
        vis[now] = 1;
        for (auto v : adj[now]){
            dfs(v);
        }
        order.push_back(now);
    }
}
void rev_dfs(int now){
    if (!vis[now]){
        cat[now] = k;
        vis[now] = 1;
        for (auto v : rev_adj[now]){
            rev_dfs(v);
        }
    }
}
void solve(){
    int n, m;
    cin >> m >> n;
    for(int i = 1; i <= m; i++){
        int u, v;
        char a, b;
        cin >> a >> u >> b >> v;
        if (a == '-'){
            u = 2 * n - u + 1; // reverse
        }
        if (b == '-'){
            v = 2 * n - v + 1; // reverse
        }
        adj[2 * n - u + 1].push_back(v); // from -u to v;  // if -u, then v
        adj[2 * n - v + 1].push_back(u); // from -v to u;  // if -v, then u
        rev_adj[v].push_back(2 * n - u + 1);
        rev_adj[u].push_back(2 * n - v + 1);
    }
    for(int i = 1; i <= 2 * n; i++){
        if (!vis[i]){
            dfs(i);
        }
    }
    memset(vis, 0, sizeof(vis));
    reverse(order.begin(), order.end());
    for (auto i : order){
        if (!vis[i]){
            rev_dfs(i);
            k++;
        }
    }
    char ans[2 * n + 1];
    for(int i = 1; i <= n; i++){
        if (cat[i] == cat[2 * n - i + 1]){
            cout << "IMPOSSIBLE";
            return;
        }
        if (cat[i] > cat[2 * n - i + 1]){
            ans[i] = '+';
        }
        else ans[i] = '-';
    }
    for(int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
}