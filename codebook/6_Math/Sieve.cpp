vector<int> prime, minp;
void sieve(int n) {
    minp.assign(n + 1, 1); // 1 代表是質數，非 1 不是
    minp[0] = minp[1] = -1;
    int m = int(sqrt(n)) + 1;
    for (int i = 2; i <= m; i++) {
        if (minp[i] == 1) {
            prime.push_back(i);
            for (int j = 2; i * j <= n; j++) {
                minp[i * j] = i;
            }
        }
    }
}
// a ^ (m-1) = 1 (Mod m)
// a ^ (m-2) = 1/a (Mod m)
// Exp2: cout << power(x, power(y, p, Mod - 1), Mod)
// Num = (x+1) * (y+1) * (z+1)...
// Sum = (a^0 + a^1+...+ a^x) * (b^0 +...+ b^y)
// Mul = N * (x+1) * (y+1) * (z+1) / 2