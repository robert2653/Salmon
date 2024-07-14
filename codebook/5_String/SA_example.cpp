#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// https://atcoder.jp/contests/abc362/tasks/abc362_g

struct SuffixArray {
    int n;
    vector<int> sa, rk, lc;
    // n: 字串长度
    // sa: 后缀数组，sa[i] 表示第 i 小的后缀的起始位置
    // rk: 排名数组，rk[i] 表示从位置 i 开始的后缀的排名
    // lc: LCP 数组，lc[i] 表示 sa[i] 和 sa[i+1] 的最长公共前缀长度
    SuffixArray(const string &s) {
        n = s.length();
        sa.resize(n);
        lc.resize(n - 1);
        rk.resize(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int a, int b) { return s[a] < s[b]; });
        rk[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        int k = 1;
        vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while (rk[sa[n - 1]] < n - 1) {
            tmp.clear();
            for (int i = 0; i < k; ++i)
                tmp.push_back(n - k + i);
            for (auto i : sa)
                if (i >= k)
                    tmp.push_back(i - k);
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; ++i)
                ++cnt[rk[i]];
            for (int i = 1; i < n; ++i)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i)
                sa[--cnt[rk[tmp[i]]]] = tmp[i];
            swap(rk, tmp);
            rk[sa[0]] = 0;
            for (int i = 1; i < n; ++i)
                rk[sa[i]] = rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == n || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            k *= 2;
        }
        for (int i = 0, j = 0; i < n; ++i) {
            if (rk[i] == 0) {
                j = 0;
            } else {
                for (j -= j > 0; i + j < n && sa[rk[i] - 1] + j < n && s[i + j] == s[sa[rk[i] - 1] + j]; )
                    ++j;
                lc[rk[i] - 1] = j;
            }
        }
    }
};

void solve() {
    string s; cin >> s;
    int n = s.length();
    // s += "$";  // 添加一個終止符
    SuffixArray SA(s);

    int q; cin >> q;

    while (q--) {
        string t; cin >> t;
        int m = t.length();
        // sa[i] 表示第 i 小的后缀的起始位置，所以可以二分搜找到跟 t 長度一樣且跟 t 長的一模一樣的 sa 位置
        
        // 二分搜索找到下界
        int low = lower_bound(SA.sa.begin(), SA.sa.end(), t, [&](int i, const string& t) {
            return s.compare(i, m, t) < 0;
        }) - SA.sa.begin();
        
        // 二分搜索找到上界
        int high = upper_bound(SA.sa.begin(), SA.sa.end(), t, [&](const string& t, int i) {
            return s.compare(i, m, t) > 0;
        }) - SA.sa.begin();
        
        cout << high - low << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}