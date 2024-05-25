struct nCr {
    ll inverse(int num) {
        if (num == 1) return 1;
        return (mod - ((mod / num) * inverse(mod % num)) % mod) % mod;
    }
    ll fast_exp(ll x, ll p) {
        x %= mod;
        ll ans = 1;
        while (p > 0) {
            if (p & 1) ans = (ans * x) % mod;
            x = x * x % mod;
            p >>= 1;
        }
        return ans;
    }
    vector<ll> fac;
    void buildFac(int n) {
        fac.resize(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i % mod;
        }
    }
    ll C(int m, int n) {
        return m < n ? 0 : fac[m] * inverse(fac[n]) % mod * inverse(fac[m - n]) % mod;
    }
    ll Lucas(ll m, ll n) {
        return n == 0 ? 1 % mod : Lucas(m / mod, n / mod) * C(m % mod, n % mod) % mod;
    }
};