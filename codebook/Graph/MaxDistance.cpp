#include <bits/stdc++.h>
using namespace std;
// Max_Dis, Use Topo, Use queue
// If 1 can't reach n, still may be relaxed，Should dis[n] < 0
// Only Directed Graph
void print_ans(int n, vector<int> &par){
    deque<int> ans;
    int now = n;
    while(now != 1){
        ans.push_front(now);
        now = par[now];
    }
    ans.push_front(1);
    cout << ans.size() << endl;
    for(auto i : ans){
        cout << i << " ";
    }
}
void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> dis(n + 1, -1e9); dis[1] = 0;
    vector<int> graph[n+1];
    vector<bool> vis(n+1, 0);
    vector<int> par(n+1);
    vector<int> in(n+1, 0);
    queue<int> q;
    for(int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        in[v]++;
    }
    for(int i = 1; i <= n; i++){
        if(in[i] == 0) q.push(i);
    }
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto nxt : graph[u]){
            if(dis[nxt] < dis[u] + 1){
                dis[nxt] = dis[u] + 1;
                par[nxt] = u;
            }
            in[nxt]--; if(in[nxt] == 0) q.push(nxt);
        }
        vis[u] = 1;
    }
    if(dis[n] < 0){
        cout << "IMPOSSIBLE";
    }
    else print_ans(n, par);
}