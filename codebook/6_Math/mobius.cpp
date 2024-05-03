#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 5;
int mobius_pref[maxn];

void init() {
    mobius_pref[1] = 1;
    vector<int> wei(maxn);  // wei = 0 代表是質數，-1 代表可被平方數整除
    for (int i = 2; i < maxn; i++) {
        if (wei[i] == -1) {
            mobius_pref[i] = mobius_pref[i - 1];
            continue; // 包含平方
        }
        if (wei[i] == 0) {
            wei[i] = 1;
            for (int j = 2; i * j < maxn; j++) {
                if (j % i == 0) wei[i * j] = -1;
                else if (wei[i * j] != -1) wei[i * j]++;
            }
        }
        mobius_pref[i] = mobius_pref[i - 1] + (wei[i] % 2 == 0 ? 1 : -1);
    }
}
void solve() {
    int a, b, c, d, k; cin >> a >> b >> c >> d >> k;
    auto cal = [&](int x, int y) -> int {
        int res = 0;
        for (int l = 1, r; l <= min(x, y); l = r + 1) {
            r = min(x / (x / l), y / (y / l));
            res += (mobius_pref[r] - mobius_pref[l - 1]) * (x / l) * (y / l);  // 代推出来的式子
        }
        return res;
    };
    cout << cal(b / k, d / k) - cal((a - 1) / k, d / k) - cal(b / k, (c - 1) / k) + cal((a - 1) / k, (c - 1) / k) << "\n";
}