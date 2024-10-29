struct SAM {
    // 1 -> initial state
    static constexpr int ALPHABET_SIZE = 26;
    // node -> strings with the same endpos set
    // link -> longest suffix with different endpos set
    // len  -> state's longest suffix
    // fpos -> first endpos
    // range-> [len(link) + 1, len]
    struct Node {
        int len, link, fpos;
        array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, fpos{}, next{} {}
    };
    vector<Node> t;
    SAM() { init(); }
    void init() {
        t.assign(2, Node());
        t[0].len = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        if (!p) t[p].next[c] = 1;
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r] = t[q];
            t[r].len = t[p].len + 1;
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        t[cur].fpos = t[p].len;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        // distinct substr += t[cur].len - t[t[cur].link].len;
        return cur;
    }
};
void solve() {  // Substring Order II: build
    string s; cin >> s;
    int n = s.length();
    vector<int> last(n + 1); // s[i - 1] 的後綴終點位置
    last[0] = 1;
    SAM sam;
    for (int i = 0; i < n; i++)
        last[i + 1] = sam.extend(last[i], s[i] - 'a');

    int sz = sam.t.size();
    // without this part for distinct substr
    vector<int> cnt(sz);
    // endpos size: substr occurence
    for (int i = 1; i <= n; i++)
        cnt[last[i]]++;
    vector<vector<int>> g(sz);
    for (int i = 1; i < sz; i++)
        g[sam.t[i].len].push_back(i);
    for (int i = n; i > 0; i--)
        for (int u : g[i])
            cnt[sam.t[u].link] += cnt[u];

    vector<ll> dp(sz, -1);
    auto rec = [&](auto self, int u) -> ll {
        if (dp[u] != -1) return dp[u];
        dp[u] = cnt[u]; // = 1 for distinct
        for (int c = 0; c < SAM::ALPHABET_SIZE; c++) {
            int v = sam.t[u].next[c];
            if (v) dp[u] += self(self, v);
        }
        return dp[u];
    };
    rec(rec, 1);

    int k, p = 1; cin >> k;
    string ans;
    while (k > 0) {
        for (int c = 0; c < SAM::ALPHABET_SIZE; c++) {
            int v = sam.t[p].next[c];
            if (v) {
                if (k >= dp[v]) {
                    k -= dp[v];
                } else {
                    ans.push_back('a' + c);
                    k--, p = v;
                    break;
                }
            }
        }
    }
}