#include <bits/stdc++.h>
using namespace std;
template <class Node, class Lazy>
struct LazySeg {
    int n;
    vector<Node> tree;
    vector<Lazy> lazy;
    template <typename T>
    LazySeg (vector<T> init_) {  // 必須是 1-based
        n = init_.size() - 1;
        tree.resize(4 * n);
        lazy.resize(4 * n);
        function <void(int, int, int)> build = [&](int now, int l, int r) {
            if (l == r) {
                tree[now] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(now << 1, l, m);
            build((now << 1) + 1, m + 1, r);
            pull(now);
        };
        build(1, 1, n);
    }
    Node query(int l, int r, int ql, int qr, int now) {
        int m = (l + r) >> 1;
        if (qr < l || ql > r) {
// -----------------------out of range, return what--------------------------------
            return Node();
// --------------------------------------------------------------------------------
        }
        push(now, l, r);
        if (ql <= l && r <= qr) {
            return tree[now];
        }
	    return query(l, m, ql, qr, now << 1) + query(m + 1, r, ql, qr, (now << 1) + 1);
    }
    Node query(int l, int r) { return query(1, n, l, r, 1); }
    void pull(int now) {
        tree[now] = tree[now << 1] + tree[(now << 1) + 1];
    }
    void modify_add(int l, int r, int ql, int qr, int now, int add) {
        int m = (l + r) >> 1;
        if (qr < l || ql > r) {
            return;
        }
        if (ql <= l && r <= qr) {
// ------------------------------how to modify ?-----------------------------------
            lazy[now].add += add;
// --------------------------------------------------------------------------------
            return;
        }
        push(now, l, r);
        modify_add(l, m, ql, qr, now << 1, add);
        modify_add(m + 1, r, ql, qr, (now << 1) + 1, add);
        push(now << 1, l, m);
        push((now << 1) + 1, m + 1, r);
        pull(now);
    }
    void modify_add(int l, int r, int add) { modify_add(1, n, l, r, 1, add); }
    void modify_set(int l, int r, int ql, int qr, int now, int val) {
        int m = (l + r) >> 1;
        if (qr < l || ql > r) {
            return;
        }
        if (ql <= l && r <= qr) {
// ------------------------------how to modify ?-----------------------------------
            lazy[now].set_val = val;
            lazy[now].add = 0;
// --------------------------------------------------------------------------------
            return;
        }
        push(now, l, r);
        modify_set(l, m, ql, qr, now << 1, val);
        modify_set(m + 1, r, ql, qr, (now << 1) + 1, val);
        push(now << 1, l, m);
        push((now << 1) + 1, m + 1, r);
        pull(now);
    }
    void modify_set(int l, int r, int val) { modify_set(1, n, l, r, 1, val); }
    void push(int now, int l, int r) {
        apply(now, l, r);
// -----------------------how to push down ?---------------------------------------
        if (l != r) {
            if (lazy[now].set_val) {
                lazy[now << 1].set_val = lazy[now].set_val;
                lazy[(now << 1) + 1].set_val = lazy[now].set_val;
                lazy[now << 1].add = lazy[now].add;
                lazy[(now << 1) + 1].add = lazy[now].add;
            }
            else {
                lazy[now << 1].add += lazy[now].add;
                lazy[(now << 1) + 1].add += lazy[now].add;
            }
        }
// --------------------------------------------------------------------------------
        lazy[now] = Lazy();
    }
    void apply(int now, int l, int r) {
        if (lazy[now].set_val) {
            tree[now].sum = (r - l + 1) * lazy[now].set_val;
        }
        tree[now].sum += (r - l + 1) * lazy[now].add;
    }
};
// ------------------------define structure and info plus------------------------
struct Node {
    int sum;
};
struct Lazy {
    int set_val; int add;
};
Node operator+(const Node &a, const Node &b) {
    return {{a.sum + b.sum}};
}
// ------------------------------------------------------------------------------

// polynomial queries
// 設置梯形的底跟加了幾次，apply_tag時底為l的合，d為加給次，所以sum += (底*2 + 次*區間) * 區間 / 2;