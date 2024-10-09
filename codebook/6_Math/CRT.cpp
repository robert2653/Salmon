ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
ll inv(ll x, ll m) {
    ll a, b;
    exgcd(x, m, a, b);
    a %= m;
    if (a < 0) a += m;
    return a;
}
// gcd(mod) = 1, res % mod_i = remain_i
// a: remain, mod
ll CRT(vector<pair<ll, ll>> &a) {
    ll s = 1, res = 0;
    for (auto [r, m] : a) s *= m;
    for (auto [r, m] : a) {
        ll t = s / m;
        res += r * t % s * inv(t, m) % s;
        if (res >= s) res -= s;
    }
    return res;
}