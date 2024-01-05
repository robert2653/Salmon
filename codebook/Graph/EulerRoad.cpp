#include <bits/stdc++.h>
using namespace std;
// Undirected: check adj[i].sz == odd => IMPOSSIBLE，road.sz != m+1 => IMPOSSIBLE
// Directed: minimize to 1 -> 2, so check in_degree == out_degree
int n, m;
const int maxn = 1e5 + 5;
set<int> adj[maxn];// rev_adj[maxn];
int in[maxn];
void dfs(int now, vector<int> &road){
    while(!adj[now].empty()){
        int nxt = *adj[now].begin();
        adj[now].erase(nxt);
        dfs(nxt, road);
    }
    road.push_back(now);
}
void solve(){
    cin >> n >> m;
    memset(in, sizeof(in), 0);
    for(int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        adj[u].insert(v);
        in[v]++;
    }
    in[1]++;
    in[n]--;
    for(int i = 1; i <= n; i++){
        if(adj[i].size() != in[i]){
            cout << "IMPOSSIBLE";
            return;
        }
    }
    vector<int> road;
    dfs(1, road);
    if(road.size() != m+1){
        cout << "IMPOSSIBLE";
        return;
    }
    reverse(road.begin(), road.end());
    for(auto i : road) cout << i << " ";
}