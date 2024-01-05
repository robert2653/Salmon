#include <bits/stdc++.h>
using namespace std;
bool vis[505];
int lev[505], n, m, ans;
typedef struct {
    int to, w, rev_ind;
} edge;
vector<edge> adj[505];
bool label_level(){ // Tag the depth，if can't reach end => return false
    memset(lev, -1, sizeof(lev));
    lev[1] = 0;
    queue<int> q;   q.push(1);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto i : adj[u]){
            if(i.w > 0 && lev[i.to] == -1){
                q.push(i.to);
                lev[i.to] = lev[u] + 1;
            }
        }
    }
    return (lev[n] == -1 ? false : true);
}
int dfs(int u, int flow){
    if(u == n) return flow;
    for(auto &i : adj[u]){
        if(lev[i.to] == lev[u] + 1 && !vis[i.to] && i.w > 0) {
            vis[i.to] = true;
            int ret = dfs(i.to, min(flow, i.w));
            if(ret > 0) {
                i.w -= ret;
                adj[i.to][i.rev_ind].w += ret;
                return ret;
            }
        }
    }
    return 0;   // if can't reach end => return 0
}
void dinic(){
    while(label_level()){
        while(1){
            init(vis, 0);
            int tmp = dfs(1, inf);
            if(tmp == 0) break;
            ans += tmp;
        }
    }
}
void build(){
    rep(i, 1, m){
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w, (int)adj[v].sz});   // inverse flow's index
        adj[v].push_back({u, 0, (int)adj[u].sz-1}); // have pushed one，need to -1
    }
}
// Police Chase，need to open adj to Augment && ori to determine what pb give
// Dinic、dfs2，then use reach as u，if the edge pb has given && w == 0 && v is not in reach，is the ans
void dfs2(int now, unordered_set<int> &reach){
    if(!vis[now]){
        vis[now] = 1;
        reach.insert(now);
        for(auto i : adj[now]){
            if(i.w > 0){
                dfs2(i.to, reach);
            }
        }
    }
}
// two two pair // School Dance
// Dinic，then w == 0 edge, which pb has given is the ans

// Distinct Route
// edge set valid var，if we need to argument pos road，the reverse edge set true valid；
// if we need argument the argumented edge，both set false，last, from v dfs ans times
bool get_road(int now, vector<int> &ans, vector<bool> &vis){
    if(now == 1) return true;
    for(auto &v : adj[now]){
        if(v.arg_valid && !vis[v.to]){
            ans.push_back(v.to);
            vis[v.to] = true;
            bool flag = get_road(v.to, ans, vis);
            if(flag){
                v.arg_valid = false;
                return true;
            }
            ans.pop_back();
        }
    }
    return false;
}