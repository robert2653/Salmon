ll dp[maxn][maxn];
void solve(){
    init(dp, 0);
    string s1, s2; cin >> s1 >> s2;
    int size1 = s1.sz, size2 = s2.sz;
    s1 = "0" + s1, s2 = "0" + s2;
    for(int i = 1; i <= size2; i++) dp[0][i] = i;  // s2 = {}, s1 = ...;
    for(int i = 1; i <= size1; i++) dp[i][0] = i;  // s1 = {}, s2 = ...;
    for(int i = 1; i <= size1; i++){
        for(int j = 1; j <= size2; j++){
            if(s1[i] == s2[j]){
                dp[i][j] = dp[i-1][j-1];
            }
            else {
                dp[i][j] = min(min(dp[i-1][j-1], dp[i-1][j]), dp[i][j-1]) + 1;
                                // modify    // s1 del / s2 add   // s1 add s2 del  
            }
        }
    }
    cout << dp[size1][size2];
}