template<class Info, class Tag>
struct LinkCutTree { // 1-based
    struct Node {
        Info info = Info();
        Tag tag = Tag();
        int siz = 0, ch[2], p = 0, rev = 0;
    };
    vector<Node> nd;
    LinkCutTree(int n) : nd(n + 1) {}
    bool isrt(int t) {
        return nd[nd[t].p].ch[0] != t && nd[nd[t].p].ch[1] != t;
    }
    int pos(int t) { // t 是其 par 的左/右
        return nd[nd[t].p].ch[1] == t;
    }
    void applyRev(int t) {
        swap(nd[t].ch[0], nd[t].ch[1]);
        nd[t].rev ^= 1;
    }
    void apply(int t, const Tag &v) {
        nd[t].info.apply(nd[t].siz, v);
        nd[t].tag.apply(v);
    }
    void push(int t) {
        if (nd[t].rev) {
            if (nd[t].ch[0]) applyRev(nd[t].ch[0]);
            if (nd[t].ch[1]) applyRev(nd[t].ch[1]);
            nd[t].rev = 0;
        }
        if (nd[t].ch[0]) apply(nd[t].ch[0], nd[t].tag);
        if (nd[t].ch[1]) apply(nd[t].ch[1], nd[t].tag);
        nd[t].tag = Tag();
    }
    void pull(int t) {
        nd[t].siz = 1 + nd[nd[t].ch[0]].siz + nd[nd[t].ch[1]].siz;
        nd[t].info.pull(nd[nd[t].ch[0]].info, nd[nd[t].ch[1]].info);
    }
    void pushAll(int t) {
        if (!isrt(t)) pushAll(nd[t].p);
        push(t);
    }
    void rotate(int x) { // x 與其 par 交換位置
        int f = nd[x].p, r = pos(x);
        nd[f].ch[r] = nd[x].ch[!r];
        if (nd[x].ch[!r]) nd[nd[x].ch[!r]].p = f;
        nd[x].p = nd[f].p;
        if (!isrt(f)) nd[nd[f].p].ch[pos(f)] = x;
        nd[x].ch[!r] = f, nd[f].p = x;
        pull(f), pull(x);
    }
    void splay(int x) {
        pushAll(x);
        for (int f = nd[x].p; f = nd[x].p, !isrt(x); rotate(x))
        if (!isrt(f)) rotate(pos(x) == pos(f) ? f : x);
    }
    void access(int x) {
        for (int f = 0; x; f = x, x = nd[x].p)
            splay(x), nd[x].ch[1] = f, pull(x);
    }
    void makeRoot(int p) {
        access(p), splay(p), applyRev(p);
    }
    int findRoot(int x) {
        access(x), splay(x);
        while (nd[x].ch[0]) x = nd[x].ch[0];
        splay(x); return x;
    }
    void split(int x, int y) { // y 為根
        makeRoot(x), access(y), splay(y);
    }
    void link(int rt, int p) {
        makeRoot(rt), nd[rt].p = p;
    }
    void cut(int x, int y) {
        makeRoot(x), access(y), splay(y);
        nd[y].ch[0] = nd[nd[y].ch[0]].p = 0;
        pull(y);
    }
    bool neighbor(int x, int y) {
        makeRoot(x), access(y);
        if (nd[y].ch[0] != x || nd[x].ch[1]) return false;
        return true;
    }
    bool connected(int x, int y) {
        return findRoot(x) == findRoot(y);
    }
    void modify(int x, const Info &v) {
        access(x), nd[x].info = v;
    }
    void pathApply(int x, int y, const Tag &v) {
        assert(connected(x, y));
        split(x, y), apply(y, v);
    }
    Info pathQuery(int x, int y) {
        assert(connected(x, y));
        split(x, y); return nd[y].info;
    }
};
const int Mod = 51061;
struct Tag {
    ll add = 0, mul = 1;
    void apply(const Tag &v) {
        mul = mul * v.mul % Mod;
        add = (add * v.mul % Mod + v.add) % Mod;
    }
};
struct Info {
    ll val = 0, sum = 0;
    void apply(int siz, const Tag &v) {
        val = (val * v.mul % Mod + v.add) % Mod;
        sum = (sum * v.mul % Mod + v.add * siz % Mod) % Mod;
    }
    void pull(const Info &l, const Info &r) {
        sum = (l.sum + r.sum + val) % Mod;
    }
};