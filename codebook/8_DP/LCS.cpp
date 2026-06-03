string LCS(const string &a, const string &b) {
    int n = a.length(), m = b.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int l = dp[n][m];
    string ans(l, 0);
    while (n >= 1 && m >= 1) {
        if (a[n - 1] == b[m - 1]) {
            ans[l - 1] = a[n - 1];
            n--, m--, l--;
        } else {
            if (dp[n - 1][m] > dp[n][m - 1]) n--;
            else m--;
        }
    }
    return ans;
}