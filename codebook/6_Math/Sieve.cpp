vector<int> minp, primes;
vector<int> phi, mu, pnum; // 質因數種類數
vector<int> mpnum, dnum; // 最小質因數的冪次數, 約數數量
vector<int> powpref, dsum; // 約數和
// dmul[i] = i ^ (dnum[i] / 2) for dnum[i] even
// dmul[i] = k ^ dnum[i], k * k = i else
void sieve(int n) {
    minp.resize(n + 1);
    phi.resize(n + 1);
    mu.resize(n + 1);
    pnum.resize(n + 1);
    
    mpnum.resize(n + 1);
    dnum.resize(n + 1);
    
    powpref.resize(n + 1);
    dsum.resize(n + 1);

    phi[1] = mu[1] = 1;
    dsum[1] = 1;
    powpref[1] = dsum[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!minp[i]) {
            minp[i] = i;
            primes.push_back(i);

            phi[i] = i - 1;
            mu[i] = -1;
            pnum[i] = 1;

            mpnum[i] = 1;
            dnum[i] = 2;

            powpref[i] = i + 1;
            dsum[i] = i + 1;
        }
        for (int p : primes) {
            if (i * p > n) break;
            minp[i * p] = p;
            if (p == minp[i]) {
                phi[i * p] = phi[i] * p;
                mu[i * p] = 0;
                pnum[i * p] = pnum[i];

                mpnum[i * p] = mpnum[i] + 1;
                dnum[i * p] = dnum[i] / mpnum[i * p] * (mpnum[i * p] + 1);

                powpref[i * p] = powpref[i] * p + 1;
                dsum[i * p] = dsum[i] / powpref[i] * powpref[i * p];
                break;
                // i * p = (p * x) * p
                // i * q = (p * x) * q
                // 到達 x * q 再用 p 篩掉就好
            } else {
                phi[i * p] = phi[i] * (p - 1);
                mu[i * p] = -mu[i];
                pnum[i * p] = pnum[i] + 1;

                mpnum[i * p] = 1;
                dnum[i * p] = dnum[i] * 2;

                powpref[i * p] = p + 1;
                dsum[i * p] = dsum[i] * (p + 1);
            }
        }
    }
}
// a ^ (m-1) = 1 (Mod m)
// a ^ (m-2) = 1/a (Mod m)
// exp2: cout << power(x, power(y, p, Mod - 1), Mod)
// num = (x+1) * (y+1) * (z+1)...
// sum = (a^0 + a^1+...+ a^x) * (b^0 +...+ b^y) = (a^{x+1} - 1) / (a-1) * ...
// mul = N ^ ((x+1) * (y+1) * (z+1) / 2)