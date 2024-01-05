ll qpow(ll a,ll n,ll m){
    ll res = 1;
    while (n > 0)
    {
        if(n & 1){
            res = res * a % m;
        }
        a = a * a % m;
        n >>= 1;
    }
    return res % m;
}
int main(){
    // a ^ x = b (mod n)
    ll a,b,n,ans;
    map<ll ,ll>value;
    while(cin >> a >> b >> n){
        ll minn = __LONG_LONG_MAX__;
        ll m = (ll)sqrt(n)+1;
        value.clear();
        if(b == 1){
            cout << "0\n";
            continue;
        }
        for(int i = 1;i < m;i++){
            value[qpow(a,i*m,n)] = i;
        }
        bool done = false;
        for(int j = 0;j < m;j++){
            ll cur = (qpow(a,j,n) * b) % n;
            if(value[cur]){
                ans = value[cur] * m - j;
                if(ans < n && ans >= 0){
                    done = true;
                    minn = min(minn,ans);
                }
            }
        }
        if(done) cout << minn << "\n";
        else cout << "NOT FOUND\n";
    }
    return 0;
}