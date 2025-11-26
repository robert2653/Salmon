// 使用情況: 跟 bit 與(被)包含有關, 且 x 在 1E6 左右
// 題目: 一數組, 問有多少所有數 & 起來為 0 的集合數
// dp[x] 代表包含 x 的 y 個數(比 x 大且 bit 1 全包含 x 的有幾個)
// 答案應該包含在 dp[0] 内，但是有重複元素，所以考慮容斥
// => ans = \sum _{i=0}^{n} (-1)^{pop_count(i)} 2^{dp[i]-1}
// => 全部為 0 的個數 − 至少一個為 1 的個數 + 至少兩個為 1 的個數
void solve(int n, vector<int> a) {
    int m = __lg(*max_element(a.begin(), a.end())) + 1;
    // 定義 dp[mask] 為 mask 被包含於 a[i] 的 i 個數
    vector<Z> dp(1 << m);
    for (int i = 0; i < n; i++) dp[a[i]] += 1;
    for (int i = 0; i < m; i++) {
        for (int mask = 0; mask < 1 << m; mask++) {
            if (mask >> i & 1) {
                int pre = mask ^ (1 << i);
                dp[pre] += dp[mask];
            }
        }
    }
    for (int i = 0; i < 1 << m; i++) {
        dp[i] = power(Z(2), int(dp[i])) - 1;
    }
    // 排容，dp[i]: & 起來為 i 的集合數
    for (int i = 0; i < m; i++) {
        for (int mask = 0; mask < 1 << m; mask++) {
            if (mask >> i & 1) {
                int pre = mask ^ (1 << i);
                dp[pre] -= dp[mask];
            }
        }
    }
}
// x | y = x, 代表包含於 x 的 y 個數, 定義為 dp[x][0]
// x & y = x, 代表包含 x 的 y 個數, 定義為 dp[x][1]
// x & y != 0, 代表至少有一個位元都為 1 的 y 個數, = n - dp[~x][0]
void solve(int n, vector<int> a) {
    int m = __lg(*max_element(a.begin(), a.end())) + 1;
    vector<array<ll, 2>> dp(1 << m);
    for (int i = 0; i < n; i++) dp[a[i]][0]++, dp[a[i]][1]++;
    for (int i = 0; i < m; i++) {
        for (int mask = 0; mask < 1 << m; mask++) {
            if (mask >> i & 1) {
                int pre = mask ^ (1 << i);
                dp[mask][0] += dp[pre][0];
                dp[pre][1] += dp[mask][1];
            }
        }
    }
}