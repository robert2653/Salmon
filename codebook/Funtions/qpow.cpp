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
