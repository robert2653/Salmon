ll N = 1e6;
vi adj[N];
bool vis[N];
void DFS(ll s){
    if(vis[s])return;
    vis[s] = true;
    for(auto u:adj[s]){
        DFS(u);
    }
}
ll timer;
void dfs(ll now, ll pa) {
    pos[now] = ++timer;
    add(timer,v[now]);
    sz[now] = 1;
    for (ll v : g[now]) {
        if (v == pa) continue;
        dfs(v, now);
        sz[now] += sz[v];
    }
}
queue<ll>q;
ll dis[N];
void BFS(ll x){
    vis[x] = true;
    dis[x] = 0;
    q.push(x);
    while(!q.empty()){
        ll s = q.front();q.pop();
        for(auto u:adj[s]){
            if(vis[u])continue;
            vis[u] = true;
            dis[u] = dis[s]+1;
            q.push(u);
        }
    }
}