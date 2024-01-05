#include <bits/stdc++.h>
using namespace std;
// Fing Aint SCC and Build a DAG, then Topo DP
const int maxn = 1e5+5;
vector<int> v, adj[maxn], rev_adj[maxn], DAG[maxn];
int order[maxn], coin[maxn], in[maxn];
int n, m, k = 0;
bool vis[maxn];
void dfs(int now){
    if(!vis[now]){
        vis[now] = 1;
        for(auto i : adj[now]){
            dfs(i);
        }
        v.push_back(now);
    }
}
void rev_dfs(int now){
    if(!vis[now]){
        vis[now] = 1;
        order[now] = k;
        for(auto i : rev_adj[now]){
            rev_dfs(i);
        }
    }
}
void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> coin[i];
    }
    for(int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }
    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            dfs(i);
        }
    }
    reverse(v.begin(), v.end());
    memset(vis, sizeof(vis), false);
    for(auto i : v){
        if(!vis[i]){
            k++;
            rev_dfs(i);
        }
    }
    // Categorized SCC
    int sum_coin[k + 1], dp_coin[k + 1];
    init(sum_coin, 0); init(dp_coin, 0);
    int ans = -1e9;
    for(int i = 1; i <= n; i++){
        sum_coin[order[i]] += coin[i];   // Now team(k) += coin;
        for(auto j : adj[i]){
            if(order[i] != order[j]){
                DAG[order[i]].push_back(order[j]);
                in[order[j]]++;
            }
        }
    }
    // Topo DP
    queue<int> q;
    for(int i = 1; i <= k; i++){
        if(in[i] == 0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int now = q.front(); q.pop();
        dp_coin[now] += sum_coin[now];
        ans = max(ans, dp_coin[now]);
        for(auto v : DAG[now]){
            in[v]--;
            dp_coin[v] = max(dp_coin[v], dp_coin[now]);
            if(in[v] == 0) q.push(v);
        }
    }
    cout << ans;
}