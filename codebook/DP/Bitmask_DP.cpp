#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
void travel_exactly_once(){
    // [走過的路][終點]
    vector<vector<int>> dp(1 << 20, vector<int> (20, 0));
    vector<int> rev_adj[20];
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        rev_adj[--v].push_back(--u);
    }
    dp[1][0] = 1;
    for(int road = 0; road < (1 << n); road++){
        // 沒經過起點，不用走
        if(road & 1 == 0) continue;
        // 有終點但沒全部走過
        if(road & (1 << (n - 1)) && road != ((1 << n) - 1)) continue;
        // DP，隨便選定一個當前路徑的終點
        for (int end = 0; end < n; end++) {
            // 路徑沒包含假定的 end
			if ((road & (1 << end)) == 0) continue;
            // 去除終點，得到 pre_road
			int pre_road = road - (1 << end);
            // 從 rev_adj 找 pre_road 的終點
			for (int pre_road_end : rev_adj[end]) {
				if ((road & (1 << pre_road_end))) {
					dp[road][end] += dp[pre_road][pre_road_end];
					dp[road][end] %= mod;
				}
			}
		}
    }
    cout << dp[(1 << n) - 1][n - 1];
}
void elevator_rides(){
    int n, k; cin >> n >> k;
    vector<int> passenger(n);
    for(int i = 0; i < n; i++) cin >> passenger[i];
    vector<int> used(1 << n, 0);    // 最後載完人的電梯用了多少空間
    vector<int> dp(1 << n, 1);  // bitset
    for(int i = 1; i < 1 << n; i++){
        used[i] = dp[i] = 2e9;
        for(int j = 0; j < n; j++){
            if(i & (1 << j)){  // 有 j
                int pre = i ^ (1 << j);
                // 最後的電梯還能載 j
                if(used[pre] + passenger[j] <= k){  
                    // 電梯數先比，再來比用掉的空間
                    if(dp[pre] < dp[i] || (dp[pre] == dp[i] && used[pre] + passenger[j] < used[i])){
                        used[i] = used[pre] + passenger[j];
                        dp[i] = dp[pre];
                    }
                }
                // 搭新的電梯
                else {
                    if(dp[pre] + 1 < dp[i] || (dp[pre] + 1 == dp[i] && passenger[j] < used[i])){
                        used[i] = passenger[j];
                        dp[i] = dp[pre] + 1;
                    }
                }
            }
        }
    }
    cout << dp[(1 << n) - 1];
}
int main(){
    travel_exactly_once();
    elevator_rides();
}