// 只含 0, 1, 8 的回文數
const int N = 44;
ll memo[N + 1][N + 1]; // memset -1, once
ll solve(string s) {
    vector<int> a {0};
    while (!s.empty()) {
        a.push_back(s.back() - '0');
        s.pop_back();
    }
    int len = a.size() - 1;
    vector<int> now(len + 1, -1); // 紀錄目前的數字
    auto dfs = [&](auto self, int p, int eff, bool f0, bool lim) -> ll {
        if (!p) return 1; // eff: 扣除前導 0 的長度
        if (!lim && !f0 && memo[p][eff] != -1) return memo[p][eff];
        ll res = 0;
        int lst = lim ? a[p] : 9; // or 1 for binary
        for (int i = 0; i <= lst; i++) {
            if (i != 0 && i != 1 && i != 8) continue;
            bool nlim = lim && i == lst;
            now[p] = i;
            if (f0 && i == 0) { // 處理前導零
                res += self(self, p - 1, eff - 1, true, nlim);
            } else if (p > eff / 2) { // 前半段
                res += self(self, p - 1, eff, false, nlim);
            } else if (now[p] == now[eff - p + 1]) {
                res += self(self, p - 1, eff, false, nlim);
            }
        }
        if (!lim && !f0) memo[p][eff] = res;
        return res;
    };
    return dfs(dfs, len, len, true, true);
}
ll memo[N + 1][10]; // memset -1, once
// 不貼上限、不前導零、枚舉 p 往後所有數字中，每個 digit x 出現的次數
ll solve(int x, ll n) {
    vector<int> a {0};
    vector<ll> sum {0}; // 貼上限時，位數 p 以下有多少數字
    while (n) {
        a.push_back(n % 10);
        sum.push_back(sum.back() + (n % 10) * power(10, a.size() - 2));
        n /= 10;
    }
    int len = a.size() - 1;
    auto dfs = [&](auto self, int p, bool f0, bool lim) -> ll {
        if (!p) return 0; // 貢獻來自於當前 digit
        if (!lim && !f0 && memo[p][x] != -1) return memo[p][x];
        ll res = 0;
        int lst = lim ? a[p] : 9; // or 1 for binary
        for (int i = 0; i <= lst; i++) {
            bool nlim = lim && i == lst;
            if (f0 && i == 0) { // 處理前導零
                res += self(self, p - 1, true, nlim);
            } else if (nlim) { // 枚舉的前幾位都貼在 n 上
                res += self(self, p - 1, false, nlim);
                if (i == x) res += sum[p - 1] + 1;
            } else {
                res += self(self, p - 1, false, nlim);
                if (i == x) res += power(10, p - 1);
            }
        }
        if (!lim && !f0) memo[p][x] = res;
        return res;
    };
    return dfs(dfs, len, true, true);
}
// 連續兩位 digit > 1
ll memo[N + 1][10]; // memset -1, once
// 不貼上限、不前導零、前一位為 prv 時、枚舉 p 往後所有數字的合法個數
ll solve(ll x) { // 建 a...
    auto dfs = [&](auto self, int p, int prv, bool f0, bool lim) -> ll {
        if (!p) return 1; // 貢獻來自於當前數字數量
        if (!lim && !f0 && memo[p][prv] != -1) return memo[p][prv];
        ll res = 0;
        int lst = lim ? a[p] : 9; // or 1 for binary
        for (int i = 0; i <= lst; i++) {
            if (prv != -1 && abs(i - prv) < 2) continue;
            bool nlim = lim && i == lst;
            if (f0 && i == 0) { // 處理前導零
                res += self(self, p - 1, -1, true, nlim);
            } else {
                res += self(self, p - 1, i, false, nlim);
            }
        }
        if (!lim && !f0) memo[p][prv] = res;
        return res;
    };
    return dfs(dfs, len, -1, true, true);
}