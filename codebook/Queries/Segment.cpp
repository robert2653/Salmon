#include <bits/stdc++.h>
using namespace std;
template <class Node>
struct Seg {
    int n;
    vector<Node> tree;
    Seg (vector<Node> init_) {
        n = init_.size() - 1;
        tree.resize(4 * n);
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
            return Node();
        }
        if (ql <= l && r <= qr) {
            return tree[now];
        }
	    return query(l, m, ql, qr, now << 1) + query(m + 1, r, ql, qr, (now << 1) + 1);
    }
    Node query(int l, int r) { return query(1, n, l, r, 1); }
    void pull(int now) {
        tree[now] = tree[now << 1] + tree[(now << 1) + 1];
    }
    void modify(int l, int r, int idx, int now, int add) {
        if (l == r) {
// ------------------------------how to modify ?-----------------------------------
            tree[now].sum = add;
// --------------------------------------------------------------------------------
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) {
            modify(l, m, idx, now << 1, add);
        }
        else {
            modify(m + 1, r, idx, (now << 1) + 1, add);
        }
        pull(now);
    }
    void modify(int idx, int add) { modify(1, n, idx, 1, add); }
};
// ------------------------define structure and info plus------------------------
struct Node {
    int sum;
    Node () {
        sum = 0;
    }
};
Node operator + (const Node &a, const Node &b) {
    Node c;
    c.sum = a.sum + b.sum;
    return c;
    // use lc、rc to undate now
    // tree[now].sum = tree[lc].sum + tree[rc].sum;
    // tree[now].prefix = max(tree[lc].sum+tree[rc].prefix, tree[lc].prefix);
    // tree[now].suffix = max(tree[lc].suffix+tree[rc].sum, tree[rc].suffix);
    // tree[now].middle_max = max(max(tree[lc].middle_max, tree[rc].middle_max), tree[lc].suffix+tree[rc].prefix);
    // tree[now].middle_max = max(max(tree[now].middle_max, tree[now].prefix), tree[now].suffix);
}
// ------------------------------------------------------------------------------

// pizza_queries
// 左邊的店(s < t): dis_l = (pizza[s] - s) + t;
// 右邊的店(t < s): dis_r = (pizza[s] + s) - t;
// 實作: 建左查詢線段樹跟右查詢線段樹，用最小值pull
// 答案是 min(left_query(1, s) + t, right_query(s, end) + t);

// List Removals
// 維護區間內有幾個數字被選過
// 用二分搜找右區間最小位，使得 ans - query == 1~ans 被選過的數量