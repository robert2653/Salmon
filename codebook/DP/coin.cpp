#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
void coin_combination_II(){
    // 有 n 種錢幣，求組合為 x 的組數，順序不可顛倒
    // 可顛倒的話只要一維，先 x 迴圈，再 coin[i] 去加
    int n, x; cin >> n >> x;
    vector<int> coin(n + 1);
    // dp[i][j] 為考慮前 i 個硬幣，組合為 i 的組數
    vector<vector<int>> dp(2, vector<int>(x + 1, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) cin >> coin[i];
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= x; j++){
            // 壓到 2 * n
            dp[i & 1][j] = dp[!(i & 1)][j];
            if(j >= coin[i]){
                (dp[i & 1][j] += dp[i & 1][j - coin[i]]) %= mod;
            }
        }
    }   
    cout << dp[n & 1][x];
}
void minimize_coins_nums(){
    // 有 n 種錢幣，求組合為 x 的最小硬幣數
    int n, x; cin >> n >> x;
    vector<int> coin(n);
    for(int i = 0; i < n; i++) cin >> coin[i];
    // dp[i] 是組合為 i 的最小硬幣數
    vector<int> dp(x + 1, 0);
    for(int i = 1; i <= x; i++){
        dp[i] = 2e9;
        for(auto &j : coin){
            if(j <= i){
                dp[i] = min(dp[i], dp[i - j] + 1);
            }
        }
    }
    cout << (dp[x] == 2e9 ? -1 : dp[x]);
}
int main(){
    coin_combination_II();
    minimize_coins_nums();
}