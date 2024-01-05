// combine
// arrange: nested loop exchange
ll dp[2][1000001];
void solve(){
    int n, x; cin >> n >> x;
    vector<int> coin(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> coin[i];
    }
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= x; j++){
            dp[i & 1][j] = dp[!(i & 1)][j];
            if(j >= coin[i]){
                (dp[i & 1][j] += dp[i & 1][j - coin[i]]) %= mod;
            }
        }
    }
    cout << dp[n & 1][x];
}
// Minimize coins nums
void solve(){
    int n, x; cin >> n >> x;
    vector<int> coin(n);
    for(int i = 0; i < n; i++){
        cin >> coin[i];
    }
    ll dp[x+1]; // init(dp, 0);
    dp[0] = 0;
    for(int i = 1; i <= x; i++){
        dp[i] = llinf;
        for(auto &j : coin){
            if(j <= i){
                dp[i] = min(dp[i], dp[i - j] + 1);
            }
        }
    }
    cout << (dp[x] == llinf ? -1 : dp[x]);
}