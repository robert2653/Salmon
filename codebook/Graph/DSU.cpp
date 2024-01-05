#include <bits/stdc++.h>
using namespace std;
// After each day, print the number of components
// and the size of the largest component
const int maxn = 2e5 + 5;
int ans, mx_sz = 1;
int boss[maxn];
int set_sz[maxn];
int find_boss(int x){
    if(boss[x] == x) return x;
    return boss[x] = find_boss(boss[x]);
}
void dsu(int x, int y){
    int boss_x = find_boss(x);
    int boss_y = find_boss(y);
    if(boss_x != boss_y){
        ans--;
        if(set_sz[boss_x] < set_sz[boss_y]){
            swap(boss_x, boss_y);
        }
        boss[boss_y] = boss_x;
        set_sz[boss_x] += set_sz[boss_y];
        mx_sz = max(mx_sz, set_sz[boss_x]);
    }
    cout << ans << " " << mx_sz << endl;
}
void solve(){
    int n, q; cin >> n >> q;
    ans = n;
    for(int i = 1; i <= n; i++){
        boss[i] = i;
        set_sz[i] = 1;
    }
    for(int i = 1; i <= q; i++){
        int x, y;
        cin >> x >> y;
        dsu(x, y);
    }
}