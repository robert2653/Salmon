const int N = 2E5;
ll pref[N];
void init() {
    pref[1] = 1;
    vector<ll> wei(N);  // wei = 0 代表是質數，-1 代表可被平方數整除
    for (ll i = 2; i < N; i++) {
        if (wei[i] == -1) {
            pref[i] = pref[i - 1];
            continue; // 包含平方
        }
        if (wei[i] == 0) {
            wei[i] = 1;
            for (ll j = 2; i * j < N; j++) {
                if (j % i == 0) wei[i * j] = -1;
                else if (wei[i * j] != -1) wei[i * j]++;
            }
        }
        pref[i] = pref[i - 1] + (wei[i] % 2 == 0 ? 1 : -1);
    }
}
void solve() {
    ll a, b, c, d, k; cin >> a >> b >> c >> d >> k;
    auto cal = [&](ll x, ll y) -> int {
        int res = 0;
        for (int l = 1, r; l <= min(x, y); l = r + 1) {
            r = min(x / (x / l), y / (y / l));
            res += (pref[r] - pref[l - 1]) * (x / l) * (y / l);  // 代推出來的式子
        }
        return res;
    };
    cout << cal(b / k, d / k) - cal((a - 1) / k, d / k) - cal(b / k, (c - 1) / k) + cal((a - 1) / k, (c - 1) / k) << "\n";
}