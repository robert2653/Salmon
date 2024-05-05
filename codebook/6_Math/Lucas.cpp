struct nCr {
    int mod;
    nCr(int mod) : mod(mod) {};
    int inverse(int num) {
        if (num == 1) return 1;
        return (mod - ((mod / num) * inverse(mod % num)) % mod) % mod;
    }
    int fast_exp(int x, int p) {
        int ans = 1;
        while (p > 0) {
            if (p & 1) ans = (ans * x) % mod;
            x = x * x % mod;
            p >>= 1;
        }
        return ans;
    }
    vector<int> fac;
    void BuildLucas(int n) {
        fac.resize(n + 1);
        fac[0] = 1;
        for(int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i % mod;
        }
    }
    int C(int m, int n) {
        return m < n ? 0 : fac[m] * inverse(fac[n]) % mod * inverse(fac[m - n]) % mod;
    }
    int Lucas(int m, int n) {
        return n == 0 ? 1 % mod : Lucas(m / mod, n / mod) * C(m % mod, n % mod) % mod;
    }
};