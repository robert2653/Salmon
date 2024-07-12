void hamiltonianPath(){
    int n, m; cin >> n >> m;
    vector adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[--v].push_back(--u);
    }
    // 以...為終點，走過...
    vector dp(n, vector<int>(findBit(n)));
    dp[0][1] = 1;
    for (int mask = 1; mask < findBit(n); mask++) {
        if ((mask & 1) == 0) continue;
        for (int i = 0; i < n; i++) {
            if ((mask & findBit(i)) == 0) continue;
            if (i == n - 1 && mask != findBit(n) - 1) continue;
            int pre_mask = mask ^ findBit(i);
            for (int j : adj[i]) {
                if ((pre_mask & findBit(j)) == 0) continue;
                dp[i][mask] = (dp[i][mask] + dp[j][pre_mask]) % Mod;
            }
        }
    }
    cout << dp[n - 1][findBit(n) - 1] << "\n";
}
void elevatorRides() {
    int n, x; cin >> n >> x; vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<array<int, 2>> dp(findBit(n));
    dp[0][0] = 1; // 次數、已使用人數
    for (int mask = 1; mask < findBit(n); mask++) {
        dp[mask][0] = dp[mask][1] = 2e9;
        for (int i = 0; i < n; i++) {
            if ((mask & findBit(i)) == 0) continue;
            int pre_mask = mask ^ findBit(i);
            if (dp[pre_mask][1] + a[i] <= x) {
                if (dp[pre_mask][0] < dp[mask][0] || dp[pre_mask][0] == dp[mask][0] && dp[pre_mask][1] + a[i] < dp[mask][1]) {
                    dp[mask][0] = dp[pre_mask][0];
                    dp[mask][1] = dp[pre_mask][1] + a[i];
                }
            } else if (dp[pre_mask][0] + 1 < dp[mask][0] || dp[pre_mask][0] + 1 == dp[mask][0] && a[i] < dp[mask][1]) {
                dp[mask][0] = dp[pre_mask][0] + 1;
                dp[mask][1] = a[i];
            }
        }
    }
    cout << dp[findBit(n) - 1][0] << "\n";
}