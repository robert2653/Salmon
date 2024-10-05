// 設 dp[i][j] 為將陣列前 i 個元素變為非嚴格遞增，並且所有 ai <= bj 所需要花的代價
#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i] -= i;
    }
    vector<int> discrete = v;
    sort(discrete.begin(), discrete.end());
    int m = unique(discrete.begin(), discrete.end()) - discrete.begin();
    vector<vector<int>> dp(2, vector<int>(m + 1));
    dp[0][0] = dp[1][0] = 2E18;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[1][j] = min(dp[1][j - 1], dp[0][j] + abs(v[i] - discrete[j - 1]));
        }
        swap(dp[0], dp[1]);
    }
    cout << *min_element(dp[0].begin(), dp[0].end());
}
// 當 dp 是凸函數且答案是極值時，可以用 slope trick 優化
// 要注意的是如果兩個相鄰段的斜率差異大於 1，那麼這個關鍵點是要存兩次的
// 例如這題假設在 i-1 時 f{i-1}(x) 是一個 Slope Trick 函數，
// 我們額外定義一個函數 g_i(x) 表示將前 i 個元素變為非嚴格遞增，且 a_i = x 的最小花費。
// 則 g_i(x) = f{i-1}(x) + |x-a_i| ，我們可以觀察到
// f_i(x) = min(g_i(y)), for y <= x，由於 |x-a_i| 是一個 Slope Trickable 函數，
// 因此 g_i(x) 和 f_i(x) 都是 Slope Trickable 函數，因為 |x-a_i|，
// 分段點是 a_i，且因為斜率一定大於 1，要 push 2 次
// 因為 g_i(x) 最右邊函數的斜率是 1，因此我們只需去除 g_i(x) 的最大斜率變化點得到 f_i(x)。
void solve() {
	priority_queue<int> q;
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
        x -= i + 1;
		q.push(x);
		q.push(x);
		ans += q.top() - x;
		q.pop();
	}
	cout << ans;
}