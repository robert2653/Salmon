// CSES Monster Game II
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// dp[i] = min(f[j] * s[i] + dp[j])
//   y   =     m        x  +   b

constexpr ll inf = 4E18;
struct Line {
    ll m, b;
    Line(ll m = 0, ll b = inf) : m(m), b(b) {}
    ll eval(ll x) const { return m * x + b; }
};
struct LiChaoSeg { // 取 max 再變換就好
    int n;
    vector<Line> info;
    LiChaoSeg(int n_ = 0) { init(n_); }
    void init(int n_ = 0) {
        n = n_;
        info.assign(4 << __lg(n), Line());
    }
    void update(Line line, int node, int l, int r) {
        int m = (l + r) / 2;
        bool left = line.eval(l) < info[node].eval(l);
        bool mid = line.eval(m) < info[node].eval(m);
        if (mid) swap(info[node], line); // 如果新線段比較好
        if (r - l == 1) return;
        else if (left != mid) update(line, 2 * node, l, m);
        // 代表左半有交點
        else update(line, 2 * node + 1, m, r); 
        // 代表如果有交點一定在右半
    }
    void add_line(Line line) { update(line, 1, 0, n); }
    ll query(int x, int node, int l, int r) {
        if (r - l == 1) return info[node].eval(x);
        int m = (l + r) / 2;
        if (x < m) return min(info[node].eval(x), query(x, 2 * node, l, m));
        else return min(info[node].eval(x), query(x, 2 * node + 1, m, r));
    }
    ll query(int x) { return query(x, 1, 0, n); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; ll x;
    cin >> n >> x;

    vector<ll> s(n), f(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> f[i];

    ll max_s = *max_element(s.begin(), s.end());
    LiChaoSeg lct(max_s);
    lct.add_line(Line(x, 0));

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll dp = lct.query(s[i]);
        if (i == n - 1) {
            ans = dp;
            break;
        }
        lct.add_line(Line(f[i], dp));
    }

    cout << ans << "\n";

    return 0;
}