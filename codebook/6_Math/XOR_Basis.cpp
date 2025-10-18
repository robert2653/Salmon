vector<int> basis;
auto add = [&](vector<int> &basis, int x) {
    for (auto i : basis) {
        x = min(x, x ^ i);
    }
    if (x) basis.push_back(x);
};
for (int i = 0; i < n; i++) {
    add(basis, a[i]);
}
sort(basis.begin(), basis.end()); // 最簡化列梯
for (auto i = basis.begin(); i != basis.end(); i++) {
    for (auto j = next(i); j != basis.end(); j++) {
        *j = min(*j, *j ^ *i);
    }
}