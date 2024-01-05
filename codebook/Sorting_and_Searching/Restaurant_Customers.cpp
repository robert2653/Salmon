int main(){
    vector<pair<int, int>> times;
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        int u, v; cin >> u >> v;
        times.push_back({u, 1});
        times.push_back({v, -1});
    }
    sort(times.begin(), times.end());
    int now_people = 0, ans = 0;
    for(auto [t, x] : times){
        ans = max(ans, (now_people += x));
    }
    cout << ans;
}