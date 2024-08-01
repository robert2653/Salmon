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

constexpr int Mod = 51061;
struct Tag {
    ll add = 0; ll mul = 1;
    void apply(const Tag& v) {
        mul = mul * v.mul % Mod;
        add = (add * v.mul % Mod + v.add) % Mod;
    }
};
struct Info {
    ll val = 0; ll sum = 0;
    void apply(int size, const Tag &v) {
        val = (val * v.mul % Mod + v.add) % Mod;
        sum = (sum * v.mul % Mod + v.add * size % Mod) % Mod;
    }
    void pull(const Info &l, const Info &r) {
        sum = (l.sum + r.sum + val) % Mod;
    }
};