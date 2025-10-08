// 只含 0, 1, 8 的回文數
const int N = 44;
vector<vector<ll>> memo(N + 1, vector<ll>(N + 1, -1));
ll solve(string n) {
    vector<int> a {0};
    string tmp = n;
    while (!tmp.empty()) {
        a.push_back(tmp.back() - '0');
        tmp.pop_back();
    }
    n = tmp;
    int len = a.size() - 1;
    // 當前 digit 不會有貢獻，交給 dfs 處理答案就好
    vector<int> now(len + 1, -1); // 紀錄目前的數字
    auto dfs = [&](auto self, int p, int eff, bool f0, bool lim) -> ll {
        if (!p) { // 記得想好要回傳 0 還是 1
            return 1;
        }
        if (!lim && !f0 && memo[p][eff] != -1) {
            return memo[p][eff];
        }
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