template<class T> struct CartesianTree {
    struct Node {
        int idx = 0, par = 0, ch[2] {};
        T val {};
    };
    vector<Node> tr;
    int build(const vector<T> &a) {
        int n = a.size();
        tr.assign(n + 1, Node());
        for (int i = 1; i <= n; i++) {
            tr[i].idx = i - 1;
            tr[i].val = a[i - 1];
        }
        for (int i = 1; i <= n; i++) {
            int k = i - 1;
            while (k && tr[k].val > tr[i].val) k = tr[k].par;
            // min-heap // same: [idx, ...]
            tr[i].ch[0] = tr[k].ch[1];
            tr[k].ch[1] = i;
            tr[i].par = k;
            if (tr[i].ch[0]) tr[tr[i].ch[0]].par = i;
        }
        return tr[0].ch[1];
    }
};