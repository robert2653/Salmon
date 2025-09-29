// 有用到 pathApply 才需要 apply 有關的
// 需要 pathQuery 才需要 pathInfo 有關的
// 需要 subtreeQuery 才需要 info, subtreeInfo
const int Mod = 51061;
struct Tag {
    ll add = 0, mul = 1;
    void apply(const Tag &v) {
        mul = mul * v.mul % Mod;
        add = (add * v.mul % Mod + v.add) % Mod;
    }
};
struct Info {
    int siz = 0;
    ll val = 0, sum = 0;
    void apply(const Tag &v) {
        val = (val * v.mul % Mod + v.add) % Mod;
        sum = (sum * v.mul % Mod + v.add * siz % Mod) % Mod;
    }
    void pull(const Info &l, const Info &r) {
        siz = 1 + l.siz + r.siz;
        sum = (l.sum + r.sum + val) % Mod;
    }
    Info &operator+=(const Info &i) {
        siz += i.siz;
        sum = (sum + i.sum) % Mod;
        return *this;
    }
    Info &operator-=(const Info &i) {
        siz -= i.siz;
        sum = (sum - (i.sum % Mod) + Mod) % Mod;
        return *this;
    }
};
struct LinkCutTree { // 1-based
    vector<Info> info, pathInfo, subtreeInfo;
    vector<Tag> tag;
    vector<array<int, 2>> ch;
    vector<int> p, rev;
    LinkCutTree(int n) : info(n + 1), pathInfo(n + 1), subtreeInfo(n + 1), tag(n + 1), ch(n + 1), p(n + 1), rev(n + 1) {}
    bool isrt(int x) {
        return ch[p[x]][0] != x && ch[p[x]][1] != x;
    }
    int pos(int x) { // x 是其 par 的左/右
        return ch[p[x]][1] == x;
    }
    void applyRev(int x) {
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }
    void apply(int x, const Tag &v) {
        info[x].apply(v);
        pathInfo[x].apply(v);
        tag[x].apply(v);
    }
    void push(int x) {
        if (rev[x]) {
            if (ch[x][0]) applyRev(ch[x][0]);
            if (ch[x][1]) applyRev(ch[x][1]);
            rev[x] = 0;
        }
        if (ch[x][0]) apply(ch[x][0], tag[x]);
        if (ch[x][1]) apply(ch[x][1], tag[x]);
        tag[x] = Tag();
    }
    void pull(int x) {
        if (!x) return;
        pathInfo[x].pull(pathInfo[ch[x][0]], pathInfo[ch[x][1]]);
        info[x].pull(info[ch[x][0]], info[ch[x][1]]);
        info[x] += subtreeInfo[x];
    }
    void pushAll(int x) {
        if (!isrt(x)) pushAll(p[x]);
        push(x);
    }
    void rotate(int x) { // x 與其 par 交換位置
        int f = p[x], r = pos(x);
        ch[f][r] = ch[x][!r];
        if (ch[x][!r]) p[ch[x][!r]] = f;
        p[x] = p[f];
        if (!isrt(f)) ch[p[f]][pos(f)] = x;
        ch[x][!r] = f, p[f] = x;
        pull(f), pull(x);
    }
    void splay(int x) { // x 旋轉到當前的根
        pushAll(x);
        for (int f = p[x]; f = p[x], !isrt(x); rotate(x))
        if (!isrt(f)) rotate(pos(x) == pos(f) ? f : x);
    }
    // 第二次 access 可以回傳 LCA
    int access(int x) { // 根到 x 換成實鏈
        int c;
        for (c = 0; x; c = x, x = p[x]) {
            splay(x);
            subtreeInfo[x] += info[ch[x][1]];
            subtreeInfo[x] -= info[c];
            ch[x][1] = c;
            pull(x);
        }
        return c;
    }
    void makeRoot(int x) { // x 變成所在樹的根
        access(x), splay(x), applyRev(x);
    }
    int findRoot(int x) {
        access(x), splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x); return x;
    }
    void split(int rt, int x) {
        makeRoot(x), access(rt), splay(rt);
    }
    void link(int rt, int x) {
        makeRoot(rt);
        access(x), splay(x);
        p[rt] = x;
        subtreeInfo[x] += info[rt];
        pull(x);
    }
    void cut(int rt, int x) {
        split(rt, x);
        ch[rt][0] = p[x] = 0;
        pull(rt);
    }
    bool connected(int x, int y) {
        return findRoot(x) == findRoot(y);
    }
    bool neighbor(int x, int y) {
        if (!connected(x, y)) return false;
        split(x, y);
        return pathInfo[x].siz == 2;
    }
    void modify(int x, const Info &v) {
        splay(x);
        info[x] = pathInfo[x] = v, pull(x);
    }
    void pathApply(int x, int y, const Tag &v) {
        assert(connected(x, y));
        split(x, y), apply(x, v);
    }
    Info pathQuery(int x, int y) {
        assert(connected(x, y));
        split(x, y); return pathInfo[x];
    }
    Info subtreeQuery(int rt, int x) {
        assert(connected(rt, x));
        split(rt, x);
        auto res = subtreeInfo[x];
        return res += pathQuery(x, x);
    }
};