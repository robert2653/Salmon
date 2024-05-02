#include <bits/stdc++.h> // weighted tree centroid
using namespace std;
const int maxn = 1e5+5;
using ll = long long;
vector<pair<int, int>> tree[maxn];
ll dp[maxn];
ll ans = 0;
void DP(int now, int par){
    ll mx1 = 0; ll mx2 = 0;
    for(auto [nxt, w] : tree[now]){
        if(nxt == par) continue;
        DP(nxt, now);
        if(mx1 < w + dp[nxt]){ // mx2 = mx1，mx1 = new mx
            mx2 = mx1; mx1 = w + dp[nxt];
        }
        else if(mx2 < w + dp[nxt]){ // mx2 = new
            mx2 = w + dp[nxt];
        }
    }
    dp[now] = mx1;
    ans = max(ans, mx1 + mx2);
}
int main(){
    int n; cin >> n;
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i < n; i++){
        int u, v, w; cin >> u >> v >> w;
        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
    }
    DP(1, 0);
    cout << (ans < 0 ? 0 : ans);
}