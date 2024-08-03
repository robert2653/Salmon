#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// Minimum Difference Spanning Tree
template<class Info, class Tag>
struct Node {
    Node *ch[2], *p;
    bool rev = false; int size = 1;
    Info info = Info(); Tag tag = Tag();
    Node() : ch{nullptr, nullptr}, p(nullptr) {}
    bool isrt() {
        return !p || (p->ch[0] != this && p->ch[1] != this);
    }
    void make_rev() {
        swap(ch[0], ch[1]);
        rev ^= true;
    }
    void apply(const Tag &v) {
        info.apply(size, v);
        tag.apply(v);
    }
    void push() {
        if (rev) {
            if (ch[0]) ch[0]->make_rev();
            if (ch[1]) ch[1]->make_rev();
            rev = false;
        }
        if (ch[0]) ch[0]->apply(tag);
        if (ch[1]) ch[1]->apply(tag);
        tag = Tag();
    }
    void pull() {
        size = 1 + (ch[0] ? ch[0]->size : 0) + (ch[1] ? ch[1]->size : 0);
        info.pull(ch[0] ? ch[0]->info : Info(), ch[1] ? ch[1]->info : Info());
    }
    int pos() {
        return p->ch[1] == this;
    }
    void pushAll() {
        if (!isrt()) {
            p->pushAll();
        }
        push();
    }
    void rotate() {
        Node *q = p;
        int x = !pos();
        q->ch[!x] = ch[x];
        if (ch[x]) ch[x]->p = q;
        p = q->p;
        if (!q->isrt()) q->p->ch[q->pos()] = this;
        ch[x] = q;
        q->p = this;
        q->pull();
    }
    void splay() {
        pushAll();
        while (!isrt()) {
            if (!p->isrt()) {
                if (pos() == p->pos()) {
                    p->rotate();
                } else {
                    rotate();
                }
            }
            rotate();
        }
        pull();
    }
    void access() { // access 後自動 splay
        for (Node *i = this, *q = nullptr; i; q = i, i = i->p) {
            i->splay();
            i->ch[1] = q;
            i->pull();
        }
        splay();
    }
    void makeRoot() {
        access();
        make_rev();
    }
    Node* findRoot() {
        access();
        Node *t = this;
        while (t->ch[0]) {
            t->push();
            t = t->ch[0];
        }
        t->access();
        return t;
    }
};
template<class Info, class Tag>
bool connected(Node<Info, Tag> *x, Node<Info, Tag> *y) {
    return x->findRoot() == y->findRoot();
}
template<class Info, class Tag>
bool neighber(Node<Info, Tag> *x, Node<Info, Tag> *y) {
    x->makeRoot();
    y->access();
    if (y->ch[0] != x || x->ch[1]) return false;
    return true;
}
template<class Info, class Tag>
void split(Node<Info, Tag> *rt, Node<Info, Tag> *y) {
    y->makeRoot();
    rt->access();
}
template<class Info, class Tag>
void link(Node<Info, Tag> *t, Node<Info, Tag> *p) {
    t->makeRoot();
    if (p->findRoot() != t) {
        t->p = p;
    }
}
template<class Info, class Tag>
bool cut(Node<Info, Tag> *x, Node<Info, Tag> *y) {
    x->makeRoot();
    y->access();
    if (y->ch[0] != x || x->ch[1]) return false;
    y->ch[0] = y->ch[0]->p = nullptr;
    x->pull();
    y->pull();
    return true;
}
template<class Info, class Tag>
void modify(Node<Info, Tag> *x, const Info &v) {
    x->access();
    x->info = v;
}
template<class Info, class Tag>
void path_apply(Node<Info, Tag> *x, Node<Info, Tag> *y, const Tag &v) {
    assert(connected(x, y));
    split(x, y);
    x->apply(v);
}
template<class Info, class Tag>
Info path_query(Node<Info, Tag> *x, Node<Info, Tag> *y) {
    assert(connected(x, y));
    split(x, y);
    return x->info;
}

struct Tag {
    void apply(const Tag& v) {}
};
constexpr int inf = 1e5;
struct Info {
    int val = inf;
    int id = -1;
    int mn = inf;
    int mnId = -1;
    void apply(int size, const Tag &v) {}
    void pull(const Info &l, const Info &r) {
        mn = val;
        mnId = id;
        if (mn > l.mn) {
            mn = l.mn;
            mnId = l.mnId;
        }
        if (mn > r.mn) {
            mn = r.mn;
            mnId = r.mnId;
        }
    }
};
using lct = Node<Info, Tag>;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<lct*> nd(n);
    for (auto &x : nd) x = new lct();
    vector<lct*> e(m);
    for (auto &x : e) x = new lct();

    vector<array<int, 3>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        edges[i][0]--;
        edges[i][1]--;
    }
    sort(edges.begin(), edges.end(), [](array<int, 3> &a, array<int, 3> &b) {
        return a[2] < b[2];
    });

    int ans = inf;
    multiset<int> usedW;
    for (int i = 0; i < m; i++) {
        auto [u, v, w] = edges[i];
        if (u == v) continue;
        e[i]->info.mn = e[i]->info.val = w;
        e[i]->info.id = e[i]->info.mnId = i;
        if (!connected(nd[u], nd[v])) {
            link(nd[u], e[i]);
            link(nd[v], e[i]);
            usedW.insert(w);
        } else {
            Info res = path_query(nd[u], nd[v]);
            if (res.mn < w) {
                int id = res.mnId;
                usedW.erase(usedW.find(res.mn));
                assert(cut(nd[edges[id][0]], e[id]));
                assert(cut(nd[edges[id][1]], e[id]));
                link(nd[u], e[i]);
                link(nd[v], e[i]);
                usedW.insert(w);
            }
        }
        if (usedW.size() == n - 1) {
            ans = min(ans, *usedW.rbegin() - *usedW.begin());
        }
    }
    cout << (ans == inf ? 0 : ans) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}