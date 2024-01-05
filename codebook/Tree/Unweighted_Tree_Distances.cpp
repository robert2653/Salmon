#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int dep1[maxn], dep2[maxn];
vector<int> tree[maxn];
int start, maxdep = 1, End;
void dfs1(int par, int now){
    for(auto nxt : tree[now]){
        if(par != nxt){
            dep1[nxt] = dep1[now] + 1;
            if(dep1[nxt] > maxdep){
                maxdep = dep1[nxt];
                start = nxt;
            }
            dfs1(now, nxt);
        }
    }
}
void find_depth1(int par, int now){
    for(auto nxt : tree[now]){
        if(par != nxt){
            dep1[nxt] = dep1[now] + 1;
            if(dep1[nxt] > maxdep){
                maxdep = dep1[nxt];
                End = nxt;
            }
            find_depth1(now, nxt);
        }
    }
}
void find_depth2(int par, int now){
    for(auto nxt : tree[now]){
        if(par != nxt){
            dep2[nxt] = dep2[now] + 1;
            find_depth2(now, nxt);
        }
    }
}
int main(){
    int n; cin >> n;
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dep1[1] = 1;
    dfs1(0, 1);
    dep1[start] = 1;
    maxdep = 1;
    find_depth1(start, start);
    dep2[End] = 1;
    find_depth2(End, End);
    for(int i = 1; i <= n; i++){
        cout << max(dep1[i], dep2[i]) - 1 << " ";
    }
}