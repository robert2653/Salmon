// 排程有權重問題，輸出價值最多且時間最少
struct project {
    int from, end, gain, id;
};
int main() {
    int n; cin >> n;
    vector<project> projects(n + 1);
    for (int i = 1; i <= n; i++) {
        int f, e, g; cin >> f >> e >> g;
        projects[i] = {f, e, g, i};
    }
    sort(all(projects), [](project a, project b) {
        if (a.end == b.end) return a.gain < b.gain;
        return a.end < b.end;
    });
    vector<array<int, 3>> dp(n + 1); // nums, gain, time
    vector<int> par(n + 1, 0), ans, add(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        int id = --upper_bound(projects.begin(), projects.begin() + i, project({0, projects[i].from, 0, 0}), [](project &a, project &b) {
            return a.end < b.end;
        }) - projects.begin();   // 二分搜最接近 from 的 end
        dp[i] = dp[i - 1];
        par[i] = i - 1;
        if (dp[i][1] < dp[id][1] + projects[i].gain || (dp[i][1] == dp[id][1] + projects[i].gain && dp[i][2] > dp[id][2] - projects[i].from + projects[i].end)) {
            // 如果報酬率一樣，比時間少的
            dp[i] = {dp[id][0] + 1, dp[id][1] + projects[i].gain, dp[id][2] + projects[i].end - projects[i].from};
            par[i] = id;
            add[i] = projects[i].id;
        }
    }
    for (auto i : dp[n])
        cout << i << " " << "\n";
    for (int now = n; now > 0; now = par[now])
        if (add[now] != -1)
            ans.push_back(add[now]);
    sort(all(ans));
    for (auto &i : ans) cout << i << " ";
}