// 在有向圖中，從 A 到 B 的最短距離
// 保證出度是 1 所以對 1 個點來說，從他出發只可能遇到一個環
int n, q;
int dp[200005][30];   // 倍增表
vector<vector<int>> cycles;
vector<int> no, cycle_idx, vis; // Order & Can be in cycle, or out
void set_out_of_cycle_no(int now, unordered_set<int> &done) {
    // 把不在環內的也編號，v 是 u 的編號 -1
    if (done.find(now) != done.end()) return;
    set_out_of_cycle_no(dp[now][0], done);
    done.insert(now);   // post order
    no[now] = no[dp[now][0]] - 1;
}
int wiint_go_to(int u, int k) { // 回傳當 u 走 k 步時會到的地方
    for (int i = 0; i <= 18; i++) {
        if (k & (1 << i)) {
            u = dp[u][i];
        }
    }
    return u;
}
void find_cycle(int now) {
    unordered_set<int> appear;
    vector<int> v;
    bool flag = true;   // 代表有環
    while (appear.find(now) == appear.end()) {
        appear.insert(now);
        v.push_back(now);
        if (vis[now]) {
            flag = false;
            break;
        }
        now = dp[now][0];
    }
    for (auto i : v)  vis[i] = true;
    if (!flag)  return;
    // now 是環的起點，我們先找到他在 v 的哪裡
    int z = find(v.begin(), v.end(), now) - v.begin();
    vector<int> cycle(v.begin() + z, v.end());
    cycles.push_back(cycle);
}
int main() {
    cin >> n >> q;
    no.assign(n + 1, -1);
    cycle_idx.assign(n + 1, -1);
    vis.assign(n + 1, 0);
    for (int u = 1; u <= n; u++) cin >> dp[u][0];
    for (int i = 1; i <= 18; i++) // 倍增表
        for (int u = 1; u <= n; u++)
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) find_cycle(i);
    }
    int idx = 0;
    unordered_set<int> done;
    for (auto &i : cycles) {
        int c = 0;
        for (auto &j : i) {
            no[j] = c++;
            cycle_idx[j] = idx;
            done.insert(j);
        }
        idx++;
    }
    for (int i = 1; i <= n; i++) set_out_of_cycle_no(i, done);
    for (int i = 1; i <= q; i++) {
        int u, v; cin >> u >> v;
        // 在同個環內
        if (cycle_idx[u] == cycle_idx[v] && cycle_idx[u] != -1 && cycle_idx[v] != -1) {
            int cyc_size = cycles[cycle_idx[u]].size();
            cout << (no[v] - no[u] + cyc_size) % cyc_size << "\n";
        }
        // 都不再環內
        else if (cycle_idx[u] == -1 && cycle_idx[v] == -1) { // Both are not in a Cycle
            if (no[u] > no[v]) {
                cout << -1 << "\n";
                continue;
            }
            if (wiint_go_to(u, no[v] - no[u]) == v) {
                cout << no[v] - no[u] << "\n";
            }
            else cout << -1 << "\n";
        }
        else if (cycle_idx[u] == -1 && cycle_idx[v] != -1) { // v 在環內，二分搜
            int l = -1, r = n;
            while (l <= r) {
                int m = (l + r) / 2;
                if (cycle_idx[wiint_go_to(u, m)] == cycle_idx[v]) r = m - 1;
                else l = m + 1;
            }
            if (l <= n) {   // 如果 n 步內可以到
                int in_cycle_of_u = wiint_go_to(u, l);
                int cycle_size = cycles[cycle_idx[v]].size();
                cout << l + (no[v] - no[in_cycle_of_u] + cycle_size) % cycle_size << "\n";
            }
            else cout << -1 << "\n";
        }
        else { // u 在環內 b 不在，直接不可能
            cout << -1 << "\n";
        }
    }
}