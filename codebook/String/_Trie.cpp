#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define int long long
typedef pair<int, int> pii;
const int llinf = 4e18;
const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;

struct Trie {
    struct trie_node {
        bool is_word;
        vector<trie_node *> children;
        trie_node() {
            is_word = false;
            children.resize(26, NULL);
        }
    };
    trie_node *root = new trie_node();
    void insert(string &s) {
        trie_node *cur = root;
        for (int i = 0; i < s.size(); i++) {
            int idx = s[i] - 'a';
            if (cur->children[idx] == NULL) {
                cur->children[idx] = new trie_node();
            }
            cur = cur->children[idx];
        }
        cur->is_word = true;
    }
    bool is_in_trie(string &s) {
        trie_node *cur = root;
        for (int i = 0; i < s.size(); i++) {
            if (cur->children[s[i] - 'a'] == nullptr) return false;
            cur = cur->children[s[i] - 'a'];
        }
        return true;
    }
    int search_i_start(string &s, int i, vector<int> &dp) {
        trie_node *cur = root;
        int sz = s.size(), ans = 0;
        for (int j = i; j < sz; j++) {
            if (cur->children[s[j] - 'a'] == nullptr) return ans;
            cur = cur->children[s[j] - 'a'];
            if (cur->is_word) 
                (ans += dp[j + 1]) %= mod;
        }
        return ans;
    }
};
void solve() {
    // 找到 sub 集合裡，可以重複用，組成 s 的組數
    Trie trie;
    string s; cin >> s;
    int sz = s.size();
    // dp 代表 i 開頭到最後的配對總數
    // 找到有結尾為 stop 的 dp[i] += dp[j + 1]
    int n; cin >> n;
    vector<int> dp(sz + 1, 0);
    for (int i = 0; i < n; i++) {
        string sub; cin >> sub;
        trie.insert(sub);
    }
    dp[sz] = 1;
    for (int i = sz - 1; i >= 0; i--) {
        dp[i] = trie.search_i_start(s, i, dp);
    }
    cout << dp[0] << endl;
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}