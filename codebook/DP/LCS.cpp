void solve(){
    int m, n; cin >> m >> n;
    string s1, s2;
    cin >> s1 >> s2;
    s1.insert(s1.begin(), '1');
    s2.insert(s2.begin(), '1');
    int L = 0;
    int dp[m+1][n+1];   init(dp, 0);
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(s1[i] == s2[j]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    int length = dp[m][n];
    cout << length << "\n";
    vector<char> s(length);
    // along to dp to trace back
    while(m >= 1 && n >= 1){
        if(s1[m] == s2[n]){
            s[length - 1] = s1[m];
            m--;
            n--;
            length--;
        }
        else {
            if(dp[m-1][n] > dp[m][n-1]){
                m--;
            }
            else n--;
        }
    }
    for(auto c : s){
        cout << c;
    }
}