struct Treap {
    Treap *lc, *rc, *par;
    int pri, siz;
    bool rev_valid;
    int val; int min;
    Treap(int val) : val(val) {
        min = val;
        pri = rand();
        lc = rc = par = nullptr;
        siz = 1, rev_valid = false;
    }
    void pull() {
        siz = 1;
        min = val;
        if (lc) {
            siz += lc->siz, lc->par = this;
            min = std::min(min, lc->min);
        }
        if (rc) {
            siz += rc->siz, rc->par = this;
            min = std::min(min, rc->min);
        }
    }
    void push() {
        if (rev_valid) {
            swap(lc, rc);
            if (lc) lc->rev_valid ^= 1, lc->par = this;
            if (rc) rc->rev_valid ^= 1, rc->par = this;
        }
        rev_valid = false;
    }
};
int size(Treap *t) { return t ? t->siz : 0; }
Treap *merge(Treap *a, Treap *b) {
    if (!a || !b) return a ? a : b;
    a->push(); b->push();
    if (a->pri > b->pri) {
        a->rc = merge(a->rc, b);
        a->pull();
        return a;
    } else {
        b->lc = merge(a, b->lc);
        b->pull();
        return b;
    }
}
pair<Treap*, Treap*> split(Treap *t, int k) {
    // 分割前 k 個在 first，剩下的在 second
    if (t == nullptr) return {nullptr, nullptr};
    t->push();
    if (size(t->lc) < k) {
        auto [a, b] = split(t->rc, k - size(t->lc) - 1);
        t->rc = a;
        if (a) a->par = t;
        if (b) b->par = nullptr;
        t->pull();
        return {t, b};
    } else {
        auto [a, b] = split(t->lc, k);
        t->lc = b;
        if (b) b->par = t;
        if (a) a->par = nullptr;
        t->pull();
        return {a, t};
    }
}
int findK(Treap *t, int k) { // pos of k, minimum in the treap
    t->push();
    int ls = (t->lc ? t->lc->siz : 0) + 1;
    if (t->val == k) return ls;
    if (t->lc && t->lc->min == k) return findK(t->lc, k);
    else return findK(t->rc, k) + ls;
}
int getPos(Treap *rt, Treap *t) { // get t's index in array
    int pos = (t->lc ? t->lc->siz : 0) + 1;
    while (t != rt) {
        Treap *par = t->par;
        if (par->rc == t) {
            pos += (par->lc ? par->lc->siz : 0) + 1;
        }
        t = par;
    }
    return pos;
}
void printArray(ostream &os, Treap *t) {
    if (!t) return;
    t->push();
    printArray(os, t->lc);
    os << t->val << " ";
    printArray(os, t->rc);
}