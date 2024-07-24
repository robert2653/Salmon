// 應用: dp(i) = h(i) + max(A(j)), for l(i) ≤ j ≤ r(i)
// A(j) 可能包含 dp(j), h(i) 可 O(1)
void Bounded_Knapsack() {
    int n, k; // O(𝑛𝑘)
    vector<int> w(n), v(n), num(n); deque<int> q;
    // 於是我們將同餘的數分在同一組
    // 每次取出連續 𝑛𝑢𝑚[𝑖] 格中最大值
    // 𝑔_𝑥 = max(_{𝑘=0}^𝑛𝑢𝑚[𝑖] (𝑔'_{𝑥−𝑘} + 𝑣_𝑖*𝑘))
    // 𝐺_𝑥 = 𝑔'_{𝑥} - 𝑣_𝑖*𝑥
    // 𝑥 代 𝑥−𝑘 => 𝑣_𝑖*(𝑥−𝑘)
    // 𝑔_𝑥 = max(_{𝑘=0}^𝑛𝑢𝑚[𝑖] (𝐺_{𝑥−𝑘} + 𝑣_𝑖*𝑥))
    vector<vector<ll>> dp(2, vector<ll>(k + 1));
    for (int i = 0; i < n; i++) {
        for (int r = 0; r < w[i]; r++) { // 餘數
            q.clear(); // q 記錄在 x = i 時的 dp 有單調性
            for (int x = 0; x * w[i] + r <= k; x++) {
                while (!q.empty() && q.front() < x - num[i])
                    q.pop_front(); // 維護遞減
                ll nxt = dp[0][x * w[i] + r] - x * v[i];
                while (!q.empty() && dp[0][q.back() * w[i] + r] - q.back() * v[i] < nxt)
                    q.pop_back();
                q.push_back(x);
                dp[1][x * w[i] + r] = dp[0][q.front() * w[i] + r] - q.front() * v[i] + x * v[i];
            }
        }
        swap(dp[0], dp[1]);
    }
    cout << dp[0][k] << "\n";
}