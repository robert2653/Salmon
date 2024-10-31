string LCS(const string &a, const string &b) {
    int m = a.length(), n = b.length(), L = 0;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int len = dp[m][n];
    string ans(len, 'c');
    while (m >= 1 && n >= 1) {
        if (a[m - 1] == b[n - 1]) {
            ans[len - 1] = a[m - 1];
            m--, n--, len--;
        }
        else {
            if (dp[m - 1][n] > dp[m][n - 1]) m--;
            else n--;
        }
    }
    return ans;
}