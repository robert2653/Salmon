int main() {
    string s1, s2; cin >> s1 >> s2;
    int size1 = s1.size(), size2 = s2.size();
    // dp[i][j] 為 s1 的前 i 個字元，跟 s2 的前 j 個字元
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, 0));
    s1 = "0" + s1, s2 = "0" + s2;
    for (int i = 1; i <= size1; i++) dp[i][0] = i;
    for (int i = 1; i <= size2; i++) dp[0][i] = i;
    for (int i = 1; i <= size1; i++){
        for (int j = 1; j <= size2; j++) {
            if (s1[i] == s2[j]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                // s1 新增等價於 s2 砍掉
                // dp[i][j] = min(修改, s1 新增, s2 新增);
                dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
            }
        }
    }
    cout << dp[size1][size2];
}