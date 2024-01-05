// Bit_Mask_DP, Travel Exactly Once
int dp[(1 << 20) - 1][20];
vector<int> rev_adj[20];
int n, m;
const int mod = 1e9 + 7;
void solve(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        rev_adj[--v].push_back(--u);
    }
    dp[1][0] = 1;
    for(int road = 0; road < (1 << n); road++){
        // Not include 1
        if(road & 1 == 0) continue;
        // include n but not all walked
        if(road & (1 << (n - 1)) && road != ((1 << n) - 1)) continue;
        // DP
        for (int end = 0; end < n; end++) {
            // Not include end
			if ((road & (1 << end)) == 0) continue;
            // exclude end point is last road
			int pre_road = road - (1 << end);
			for (int pre_road_end : rev_adj[end]) {
                // pre_road_end is prev's end
				if ((road & (1 << pre_road_end))) {
					dp[road][end] += dp[pre_road][pre_road_end];
					dp[road][end] %= mod;
				}
			}
		}
    }
    cout << dp[(1 << n) - 1][n - 1];
    // elevator rides
    // for(int i = 1; i < 1 << n; i++){
    //     used[i] = dp[i] = inf;
    //     for(int j = 0; j < n; j++){
    //         if(i & (1 << j)){  // 有j
    //             int last = i ^ (1 << j);
    //             if(used[last] + s[j] <= x){
    //                 if(dp[last] < dp[i] || dp[last] == dp[i] && used[last] + s[j] < used[i]){
    //                     used[i] = used[last] + s[j];
    //                     dp[i] = dp[last];
    //                 }
    //             }
    //             else {
    //                 if(dp[last] + 1 < dp[i] || dp[last] + 1 == dp[i] && s[j] < used[i]){
    //                     used[i] = s[j];
    //                     dp[i] = dp[last] + 1;
    //                 }
    //             }
    //         }
    //     }
    // }
    // cout << dp[(1 << n) - 1];
}