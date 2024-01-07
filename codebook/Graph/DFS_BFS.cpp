#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6;
vector<int> adj[maxn];
bool vis[maxn];
void DFS(int s){
    if(vis[s]) return;
    vis[s] = true;
    for(auto u: adj[s]){
        DFS(u);
    }
}
queue<int> q;
int dis[maxn];
void BFS(int x){
    vis[x] = true;
    dis[x] = 0;
    q.push(x);
    while(!q.empty()){
        int now = q.front();q.pop();
        for(auto nxt : adj[now]){
            if(vis[nxt]) continue;
            vis[nxt] = true;
            dis[nxt] = dis[now] + 1;
            q.push(nxt);
        }
    }
}