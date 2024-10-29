// CSES_Sum_of_Divisors
const int Mod = 1E9 + 7;
const int inv_2 = 500000004;
// n / 1 * 1 + n / 2 * 2 + n / 3 * 3 + ... + n / n * n
void integerPartition() {
    ll ans = 0, n; cin >> n;
    for (ll l = 1, r; l <= n; l = r + 1) {
	    r = n / (n / l);
        ll val = n / l; // n / l 到 n / r 一樣的值
        ll sum = (((l + r) % Mod) * ((r - l + 1) % Mod)) % Mod * inv_2; // l 加到 r
        val %= Mod; sum %= Mod;
	    ans += val * sum;
        ans %= Mod;
    }
    cout << ans << "\n";
}