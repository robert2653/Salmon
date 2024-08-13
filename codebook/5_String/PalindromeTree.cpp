struct PAM {
    static constexpr int ALPHABET_SIZE = 26;
    struct Node {
        int len;
        int fail;
        int cnt;
        array<int, ALPHABET_SIZE> next;
        Node() : len{}, fail{}, next{} {}
    };
    // 0 -> even root, 1 -> odd root
    vector<Node> t;
    PAM(const vector<int> &s) { init(s); }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    void init(const vector<int> &s) {
        t.assign(2, Node());
        t[0].len = 0;
        t[1].len = -1;
        t[0].fail = 1;
        int p = 1;
        for (int i = 0; i < s.size(); i++) {
            while (s[i - t[p].len - 1] != s[i]) {
                p = t[p].fail;
            }
            if (!t[p].next[s[i]]) {
                int idx = newNode();
                t[idx].len = t[p].len + 2;
                int now = t[p].fail;
                while (s[i - t[now].len - 1] != s[i]) {
                    now = t[now].fail;
                }
                t[idx].fail = t[now].next[s[i]];
                t[p].next[s[i]] = idx;
            }
            p = t[p].next[s[i]];
            t[p].cnt++;
        }
    }
    void build_cnt() {
        for (int i = t.size() - 1; i > 1; i--) {
            t[t[i].fail].cnt += t[i].cnt;
        }
    }
};