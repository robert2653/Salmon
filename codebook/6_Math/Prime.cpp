vector<int> prime, minp;
void sieve(int n) {
    minp.assign(n + 1, 1); // 1 代表是質數，非 1 不是
    minp[0] = minp[1] = -1;
    int m = int(sqrt(n)) + 1;
    for (int i = 2; i <= m; i++) {
        if (minp[i] == 1) {
            prime.push_back(i);
            for (int j = i + i; j <= n; j += i) {
                minp[j] = i;
            }
        }
    }
}
// a^(m-1) = 1 (mod m)
// a^(m-2) = 1/a (mod m)
// EXP2: cout << fast_exp(x, fast_exp(y, p, MOD - 1), MOD)
// FacNums = (x+1)(y+1)(z+1)...
// FacSum = (a^0+a^1...+a^x)(b^0+...+b^y)
// FacMul = N(x+1)(y+1)(z+1)/2