// 考慮前 i 個，預算有 j 塊錢的最多 page
int main(){
    int n, bud;
    cin >> n >> bud;
    vector<vector<int>> dp(n + 1, vector<int>(bud + 1));
    vector<int> Page(n + 1, 0);
    vector<int> Price(n + 1, 0); 
    
    for(int i = 1; i <= n; i++){
        cin >> Price[i];
    }
    for(int i = 1; i <= n; i++){
        cin >> Page[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= bud; j++) {
            if (j >= Price[i]) {  // 買得起
                // 不買或買
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - Price[i]] + Page[i]);
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << dp[n][bud] << "\n";
}