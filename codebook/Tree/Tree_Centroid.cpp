#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
vector<int> tree[maxn];
int cen = 0, n;
int dfs(int par, int now){
    bool flag = 1;
    int size = 0;
    for(auto nxt : tree[now]){
        if(par != nxt){
            int subsize = dfs(now, nxt);
            if(subsize > n / 2) flag = false;
            size += subsize;
        }
    }
    if(n - 1 - size > n / 2) flag = false;
    if(flag) cen = now;
    return size + 1;
}
int main(){
    cin >> n;
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    for(int i = 1; i <= n; i++){
        for(auto nxt : tree[i])
            dfs(i, nxt);
        if(cen) break;
    }
}