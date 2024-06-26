int main() {
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int dp[n]; vector<int> mono;
    mono.push_back(v[0]);
    dp[0] = 1;  int L = 1;
    for (int i = 1; i < n; i++) {
        if (v[i] > mono.back()) {
            mono.push_back(v[i]);
            dp[i] = ++L;
        }
        else {
            auto it = lower_bound(mono.begin(), mono.end(), v[i]);
            *it = v[i];
            dp[i] = it - mono.begin() + 1;
        }
    }
    vector<int> ans;
    cout << L << "\n";
    for (int i = n - 1; i >= 0; i--) {
        if (dp[i] == L) {
            ans.push_back(v[i]);
            L--;
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto i : ans) {
        cout << i << " ";
    }
}