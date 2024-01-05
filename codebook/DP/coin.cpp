int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n,m;
    cin >> n >> m;
    vector<ll> coin(n);
    for(auto &x:coin)cin >> x;
    vector<ll> DP(m + 1);
    for(int i = 1;i < m+1;i++) DP[i] = 1e9;
    sort(coin.begin(),coin.end());
    reverse(coin.begin(),coin.end());
    for(int i = 0;i <= m;i++){
        for(auto x:coin){
            if(i+x<=m){
                DP[i+x] = min(DP[i+x],DP[i] + 1);
            }
        }
    }
    if(DP[m]==1e9)cout << "-1\n";
    else cout << DP[m] << '\n';
    return 0;
}