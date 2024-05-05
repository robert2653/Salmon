// 兩個人比賽，每個人輪流取一個數字且只能是頭尾
// 問兩人都選得好，第一個人可取得的最大分數
int main() {
    int n; cin >> n;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    int pref = 0;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        pref += v[i];
    }
    // dp[i][j] 是 i 到 j 區間選完，的最大分數差
    for (int i = n; i > 0; i--) { 
        for (int j = i; j <= n; j++) {
            if (i == j) {
                dp[i][j] = v[i];
            }
            else {
                // 選左差距大，還是選右差距大
                dp[i][j] = max(v[i] - dp[i + 1][j], v[j] - dp[i][j - 1]);
            }
        }
    }
    // x + y = sum, dp[1][n] = x - y;
    cout << (pref + dp[1][n]) / 2;
}