#include <bits/stdc++.h>
using namespace std;
void solve(){
    int n, m, noon, night;
    cin >> n >> m >> noon >> night;
    int dis[n + 1];
    vector<int> graph[n + 1];
    bool vis[n + 1];
    for(int i = 1; i <= m; i++){
        int u, v, w; cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    // noon is -
    for(int i = 1; i <= n; i++){
        dis[i] = 1e9;   vis[i] = 0;
    }
    pq.push({0, -noon, 1});
    dis[1] = 0;
    while(!pq.empty()){
        vector<int> now = pq.top(); pq.pop();
        int now_noon = -now[1], u = now[2];
        if(vis[u]) continue;
        for(auto [nxt, w] : graph[u]){
            if(noon < w) continue;  // never pass
            int tmp = dis[u] + (now_noon >= w ? w : now_noon + night + w);
            if(tmp < dis[nxt]){
                dis[nxt] = tmp;
                pq.push({dis[nxt], -(now_noon >= w ? now_noon - w : noon - w), nxt});
            }
        }
        vis[u] = true;
    }
    if(dis[n] == 1e9) cout << -1 << endl;
    else cout << dis[n] << endl;
}
// Investigation
void Investigation(){
    vector<vector<
    for(auto [v, w] : graph[u]){
        if(dis[u] + w < dis[v]){
            dis[v] = dis[u] + w;
            pq.push({dis[v], v});
            min_price_nums[v] = min_price_nums[u];
            max_dis_min_price[v] = max_dis_min_price[u] + 1;
            min_dis_min_price[v] = min_dis_min_price[u] + 1;
        }
        else if(dis[u] + w == dis[v]){
            min_price_nums[v] = (min_price_nums[u] + min_price_nums[v]) % mod;
            max_dis_min_price[v] = max(max_dis_min_price[u] + 1, max_dis_min_price[v]);
            min_dis_min_price[v] = min(min_dis_min_price[u] + 1, min_dis_min_price[v]);
        }
    }
}
int main(){
    solve();
    Investigation();
}