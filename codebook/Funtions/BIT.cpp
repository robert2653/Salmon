#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

typedef struct {
    int set_val, add, sum, val;
} node;
node tree[100];
int n, q, nums[100], _1D_BIT[100], _2D_BIT[100][100];

// 1D-BIT
void modify(int x, int mod){
    for(; x <= n; x += (x&-x)){
        _1D_BIT[x] += mod;
    }
}
ll query(int x, int y){
    ll ans = 0;
    for(; x; x -= (x&-x)){
        ans += _1D_BIT[x];
    }
    return ans;
}
// 2D-BIT // Forest Queries (Area)
void modify(int x, int y, int mod){
    for(; x <= n; x += (x&-x)){
        for(int tmp = y; tmp <= n; tmp += (tmp&-tmp)){
            _2D_BIT[x][tmp] += mod;
        }
    }
}
ll query(int x, int y){
    ll ans = 0;
    for(; x; x -= (x&-x)){
        for(int tmp = y; tmp; tmp -= (tmp&-tmp)){
            ans += _2D_BIT[x][tmp];
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    memset(bit,0,sizeof(bit));
    for(int i = 1;i <= n;i++){
        cin >> num[i];
        add(i,num[i]);
    }
    return 0;
}