#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
vector<int> tree[maxn];
int sub[maxn];
void dfs(int now){
    for(auto nxt : tree[now]){
        dfs(nxt);
        sub[now] += sub[nxt] + 1;
    }
}
int main(){
    memset(sub, 0, sizeof(sub));
    int n; cin >> n;
    for(int i = 2; i <= n; i++){
        int b; cin >> b;
        tree[b].push_back(i);
    }
    dfs(1);
    for(int i = 1; i <= n; i++){
        cout << sub[i] << " ";
    }
}