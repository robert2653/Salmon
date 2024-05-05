const int maxn = 2e5+5;
int n, q;
int nums[maxn], prefix[maxn], ans[maxn], BIT[maxn], contrib[maxn];
vector<pair<int, int>> queries[maxn];
void update(int pos, int val) {
	for (; pos <= n; pos += pos & -pos) BIT[pos] += val;
}
int query(int a, int b) {
	int ans = 0;
	for (; b; b -= b&-b) ans += BIT[b];
	for (a--; a; a -= a&-a) ans -= BIT[a];
	return ans;
}
void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        prefix[i] = prefix[i-1] + nums[i];
    }
    nums[n + 1] = 1e9;
    prefix[n + 1] = 2e18;
    for (int i = 1; i <= q; i++) {
        int a, b; cin >> a >> b;
        queries[a].push_back({b, i});
    }
    deque<int> mono; mono.push_front(n+1);
    for (int i = n; i > 0; i--) { // question from start at n to start at 1
        while (nums[i] >= nums[mono.front()]) {
		    update(mono.front(), -contrib[mono.front()]);   // mono.front's contrib become 0
		    mono.pop_front();
	    }
	    contrib[i] = (mono.front() - 1 - i) * nums[i] - (prefix[mono.front() - 1] - prefix[i]);
	    update(i, contrib[i]);
	    mono.push_front(i);
        for (auto j : queries[i]) {  // pos is the index in mono <= end's
			int pos = upper_bound(mono.begin(), mono.end(), j.first) - mono.begin() - 1;
			ans[j.second] = (pos ? query(i, mono[pos - 1]) : 0)   // smainter than y's mono
                            // mono to y caculate directly
			              + (j.first - mono[pos]) * nums[mono[pos]]
                          - (prefix[j.first] - prefix[mono[pos]]);
		}
	}
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << endl;
    }
}