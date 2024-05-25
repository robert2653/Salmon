ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }

    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
ll inv(ll x, ll m){
    ll a, b;
    exgcd(x, m, a, b);
    a %= m;
    if (a < 0) a += m;
    return a;
}
// remain, mod
ll CRT(vector<pair<ll, ll>> &a){
    ll prod = 1;
    for (auto x : a) {
        prod *= x.second;
    }
    ll res = 0;
    for (auto x : a) {
        auto t = prod / x.second;
        res += x.first * t % prod * inv(t, x.second) % prod;
        if(res >= prod) res -= prod;
    }
    return res;
}