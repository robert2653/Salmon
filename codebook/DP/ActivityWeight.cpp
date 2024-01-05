#define start first.second
#define endd first.first
#define weight second
vector<pair<pair<ll,ll>,ll> > v1;
int bi_se(ll s, ll t,ll goal){
    if(s==t){//need rest
        if(goal <= v1[s].endd) return s-1; // or <
        else return s;
    }
    ll mid = (s+t)/2;
    if(goal <= v1[mid].endd) return bi_se(s,mid,goal);
    else return bi_se(mid + 1,t,goal);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;//activities
    ll s,t,w;
    v1.push_back({{0,0},0});
    for(ll i = 0;i < n;i++){
        cin >> s >> t >> w;
        v1.push_back(make_pair(make_pair(t,s),w));
    }
    vector<ll> dp;
    dp.push_back(0);
    sort(v1.begin(),v1.end());
    for(ll i = 1;i <= n;i++){
        ll tmp = bi_se(0,i - 1,v1[i].start);
        ll ch = dp[tmp] + v1[i].weight;
        dp.push_back(max(ch,dp[i-1]));
    }
    cout << dp[n] << "\n";
    return 0;
}
