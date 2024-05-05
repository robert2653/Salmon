// CSES_Sum_of_Divisors
const int mod = 1e9 + 7;
const int inv_2 = 500000004;
// n / 1 * 1 + n / 2 * 2 + n / 3 * 3 + ... + n / n * n
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int ans = 0;
    int n; cin >> n;
    for (int l = 1, r; l <= n; l = r + 1) {
	    r = n / (n / l);
        int val = n / l;    // n / l 到 n / r 一樣的值
        int sum = (((l + r) % mod) * ((r - l + 1) % mod)) % mod * inv_2;    // l 加到 r
        val %= mod; sum %= mod;
	    ans += val * sum;
        ans %= mod;
    }
    cout << ans << "\n";
}