#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define int long long
const int maxn = 2e5 + 5;
struct project {
    int from, end, gain, id;
};
void solve(){
    int n; cin >> n;
    vector<project> projects(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> projects[i].from >> projects[i].end >> projects[i].gain;
        projects[i].id = i;
    }
    sort(all(projects), [](project a, project b) {
        if (a.end == b.end) return a.gain < b.gain;
        return a.end < b.end;
    });
    vector<array<int, 3>> dp(n + 1, {0, 0, 0}); // nums, gain, time
    vector<int> par(n + 1, 0), ans, add(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        int idx = --upper_bound(projects.begin(), projects.begin() + i, project({0, projects[i].from, 0, 0}),
        [](const project &a, const project &b) -> bool {
            return a.end < b.end;
        }) - projects.begin();   // 二分搜最接近 from 的 end
        // cerr << idx << "\n";
        dp[i] = dp[i - 1];
        par[i] = i - 1;
        if (dp[i][1] < dp[idx][1] + projects[i].gain || 
        (dp[i][1] == dp[idx][1] + projects[i].gain && dp[i][2] > dp[idx][2] + projects[i].end - projects[i].from)) {
            dp[i] = {dp[idx][0] + 1, dp[idx][1] + projects[i].gain, dp[idx][2] + projects[i].end - projects[i].from};
            par[i] = idx;
            add[i] = projects[i].id;
        }
    }
    cout << dp[n][0] << " " << dp[n][1] << " " << dp[n][2] << endl;
    for (int now = n; now > 0; now = par[now]) {
        if (add[now] != -1)
            ans.push_back(add[now]);
    }
    sort(all(ans));
    for(auto &i : ans) cout << i << " ";
}