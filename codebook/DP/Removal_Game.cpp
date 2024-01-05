ll dp[5005][5005];
void solve(){
    int n; cin >> n;
    ll pref = 0;
    vector<ll> v(n+1);
    for(int i = 1; i <= n; i++){
        cin >> v[i];
        pref += v[i];
    }
    // dp[i][j] = max_diff(i to j);
    for(int i = n; i > 0; i--){
        for(int j = 1; j <= n; j++){
            if(i > j) continue;
            else if(i == j){
                dp[i][j] = v[i];
            }
            else {
                dp[i][j] = max(v[i] - dp[i+1][j], v[j] - dp[i][j-1]);   // i+1, j-1, care dp's order
            }
        }
    }
    // x + y = sum, dp[1][n] = x - y;
    cout << (pref + dp[1][n]) / 2;
}