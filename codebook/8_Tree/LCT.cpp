#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr i64 Mod = 51061;

struct Tag {
    i64 add = 0;
    i64 mul = 1;
    void apply(const Tag& v) {
        mul = mul * v.mul % Mod;
        add = (add * v.mul % Mod + v.add) % Mod;
    }
};
struct Info {
    i64 val = 1;
    i64 sum = 1;
    void apply(int size, const Tag &v) {
        val = (val * v.mul % Mod + v.add) % Mod;
        sum = (sum * v.mul % Mod + v.add * size % Mod) % Mod;
    }
};

struct Node {
    Node *ch[2], *p;
    int rev = 0;
    int size = 1;
    void make_rev() {
        swap(ch[0], ch[1]);
        rev ^= 1;
    }
    Node() : ch {nullptr, nullptr}, p(nullptr) {}

    Info info = Info();
    Tag tag = Tag();
    
    void apply(const Tag &v) {
        info.apply(size, v);
        tag.apply(v);
    }

    void push_tag() {
        if (rev) {
            if (ch[0]) ch[0]->make_rev();
            if (ch[1]) ch[1]->make_rev();
            rev = 0;
        }
        if (ch[0]) {
            ch[0]->apply(tag);
        }
        if (ch[1]) {
            ch[1]->apply(tag);
        }
        tag = Tag();
    }
    void pull_info() {
        size = (ch[0] ? ch[0]->size : 0) + (ch[1] ? ch[1]->size : 0) + 1;
        info.sum = ((ch[0] ? ch[0]->info.sum : 0) + (ch[1] ? ch[1]->info.sum : 0) + info.val) % Mod;
    }
};

bool isroot(Node *t) {
    return t->p == nullptr || (t->p->ch[0] != t && t->p->ch[1] != t);
}
int pos(Node *t) { // 回傳 1 代表是右子節點
    return t->p->ch[1] == t;
}
void rotate(Node *t) {
    Node *q = t->p;
    int x = !pos(t);
    q->ch[!x] = t->ch[x];
    if (t->ch[x]) {
        t->ch[x]->p = q;
    }
    t->p = q->p;
    if (!isroot(q)) {
        q->p->ch[pos(q)] = t;
    }
    t->ch[x] = q;
    q->p = t;
    q->pull_info();
}
void splay(Node *t) { // 單點修改前必須呼叫
    // 把 t 旋轉到目前 splay 的根
    while (!isroot(t)) {
        Node *p = t->p;
        p->push_tag();
        t->push_tag();
        rotate(t);
    }
    t->push_tag();
    t->pull_info();
}
void access(Node *t) {
    // 把從根到 t 的所有點都放在一條實鏈裡，使根
    // 到 t 成為一條實路徑，並且在同一棵 splay 裡
    for (Node *i = t, *q = nullptr; i; q = i, i = i->p) {
        splay(i);
        i->ch[1] = q;
    }
    splay(t);
}
void makeRoot(Node *t) { // 使 t 點成為其所在樹的根
    access(t);
    swap(t->ch[0], t->ch[1]);
    t->rev ^= 1;
}
Node* findRoot(Node *t) { // 找到 t 的 root
    access(t);
    splay(t);
    t->push_tag();
    while (t->ch[0]) {
        t = t->ch[0];
        t->push_tag();
    }
    splay(t);
    return t;
}
void link(Node *t, Node *p) {
    makeRoot(t);
    if (findRoot(p) != t) {
        makeRoot(p);
        t->p = p;
        p->pull_info();
    }
}
bool cut(Node *x, Node *y) { // 不存在邊，回傳 false
	makeRoot(x);
    access(y);
    if (y->ch[0] != x || x->ch[1]) return false;
    y->ch[0]->p = nullptr;
    y->ch[0] = nullptr;
    y->pull_info();
    return true;
}
void split(Node *x, Node *y) { // 以 y 做根, 區間修改用, apply 在 y 上
    makeRoot(x);
    access(y);
    splay(y);
}
bool isconnected(Node *x, Node *y) { // 查詢有沒有連通
	makeRoot(x);
    access(y);
    return findRoot(x) == findRoot(y);
}

int main() {
    int n; cin >> n;
    vector<Node *> nodes(n);
    int q; cin >> q;
    for (int i = 0; i < n; i++) {
        nodes[i] = new Node();
        nodes[i]->info.val = nodes[i]->info.sum = 1LL;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        link(nodes[u], nodes[v]);
    }
    for (int i = 0; i < q; i++) {
        char op; cin >> op;
        if (op == '+') {
            int u, v; cin >> u >> v;
            u--; v--;
            split(nodes[u], nodes[v]);
            Tag tag;
            cin >> tag.add;
            tag.add % Mod;
            nodes[v]->apply(tag);
        }
        else if (op == '-') {
            int u1, v1; cin >> u1 >> v1;
            int u2, v2; cin >> u2 >> v2;
            u1--; v1--; u2--; v2--;
            cut(nodes[u1], nodes[v1]);
            link(nodes[u2], nodes[v2]);
        }
        else if (op == '*') {
            int u, v; cin >> u >> v;
            u--; v--;
            split(nodes[u], nodes[v]);
            Tag tag;
            cin >> tag.mul;
            tag.mul % Mod;
            nodes[v]->apply(tag);
        }
        else {
            int u, v; cin >> u >> v;
            u--; v--;
            split(nodes[u], nodes[v]);
            cout << nodes[v]->info.sum << "\n";
        }
    }
    
    return 0;
}