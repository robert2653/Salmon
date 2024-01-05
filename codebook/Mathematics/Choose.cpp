ll qpow(ll a,ll n,ll m){
    ll res = 1;
    while(n > 0){
        if(n & 1){
            res = res * a % m;
        }
        a = a * a % m;
        n >>= 1;
    }
    return res % m;
}
const ll m = 1e9+7;
const ll maxn = 1e6+10;
ll fac[maxn];
ll inv[maxn];
void factoial(){
    fac[0] = 1;
    for(int i = 1;i < maxn;i++){
        fac[i] = fac[i - 1] * i % m;
    }
}
void inverse(){
    inv[0] = 1;
    for(int i = 1;i < maxn;i++){
        inv[i] = qpow(fac[i],m - 2,m);
    }
}
ll choose(ll a,ll b){
    return fac[a] * inv[b] % m * inv[a-b] % m;
}
// C(n,k)*C(k,r) = C(n,r) * C(n-r,k-r)
int main(){
    ll n = nxt();
    factoial();
    inverse();
    while(n--){
        ll a = nxt();
        ll b = nxt();
        ll res = choose(a,b);
        cout << res << '\n';
    }
    return 0;
}