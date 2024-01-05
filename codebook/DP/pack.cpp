int main(){
    int n,m;
    cin >> n >> m;
    vector <ll> DP(m+1);
    for(int i = 0;i < n;i++){
        int w,v;
        cin >> w >> v;
        for(int j = m;j >= w;j--){
            DP[j] = max(DP[j],DP[j - w] + v);
        }
    }
    cout << DP[m] << '\n';

    return 0;
}