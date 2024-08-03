int dct(int x, vector<int> &a) { // val to id
    return lower_bound(a.begin(), a.end(), x) - a.begin();
}
struct kth_info {
    int sum = 0;
};
kth_info operator+(const kth_info &a, const kth_info &b) {
    return { a.sum + b.sum };
}
struct kthPST : PST<kth_info> {
    using PST::PST;
    int kth_element(Node *rta, Node *rtb, int l, int r, int k) {
        if (r - l == 1) {
            return l;
        }
        int x = rtb->lc->info.sum - rta->lc->info.sum;
        int m = (l + r) / 2;
        if (x >= k) {
            return kth_element(rta->lc, rtb->lc, l, m, k);
        } else {
            return kth_element(rta->rc, rtb->rc, m, r, k - x);
        }
    }
    int kth_element(int a, int b, int k) { // 0-base, 0-based, 1-based
        return kth_element(roots[a], roots[b], 0, n, k);
    }
};