#include <bits/stdc++.h>
using namespace std;
int dp[1005][100005];   // 考慮前 i 個，預算有 j 塊錢的最多 page
vector<int> Page(1005, 0);
vector<int> Price(1005, 0);
int main(){
    int n, bud;
    cin >> n >> bud;
    for(int i = 1; i <= n; i++){
        int tmp; cin >> tmp;
        Price[i] = tmp;
    }
    for(int i = 1; i <= n; i++){
        int tmp; cin >> tmp;
        Page[i] = tmp;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= bud; j++){
            if(j >= Price[i]){  // 買得起
                // 不買或買
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - Price[i]] + Page[i]);
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << dp[n][bud] << "\n";
}