RMQ<int> rmq(sa.lc);
auto lcp = [&](int i, int j) { // [i, j]
    i = sa.rk[i];
    j = sa.rk[j];
    if (i > j) {
        swap(i, j);
    }
    assert(i != j);
    return rmq(i, j);
};