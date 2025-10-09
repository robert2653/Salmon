struct AC {
    static constexpr int ALPHABET_SIZE = 26;
    struct Node {
        int fail; // 指向最長後綴
        int cnt; // 有多少模式字串是自己的後綴
        array<int, ALPHABET_SIZE> ch, next;
        // next 是補全後的轉移
    };
    vector<Node> t;
    AC() : t(1) {}
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int insert(const string &s) {
        int u = 0;
        for (char c : s) {
            if (!t[u].ch[c - 'a'])
                t[u].ch[c - 'a'] = newNode();
            u = t[u].ch[c - 'a'];
        }
        t[u].cnt++;
        return u;
    }
    void build() {
        queue<int> q;
        for (int c = 0; c < ALPHABET_SIZE; c++) {
            if (t[0].ch[c]) {
                q.push(t[0].ch[c]);
                t[0].next[c] = t[0].ch[c];
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int c = 0; c < ALPHABET_SIZE; c++) {
                if (t[u].ch[c]) {
                    int v = t[u].ch[c], f = t[u].fail;
                    while (f && !t[f].ch[c]) f = t[f].fail;
                    if (t[f].ch[c]) f = t[f].ch[c];
                    t[v].fail = f;
                    t[v].cnt += t[f].cnt;
                    t[u].next[c] = v;
                    q.push(v);
                } else {
                    t[u].next[c] = t[t[u].fail].next[c];
                }
            }
        }
    }
};