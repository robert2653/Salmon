void binarySearch() {
    // 二分找上界
    while (lo < hi) {
        int x = (lo + hi + 1) / 2;
        if (check(x)) lo = x;
        else hi = x - 1;
    }
    cout << lo; // 保證有解
    
    while (lo <= hi) {
        int x = (lo + hi) / 2;
        if (check(x)) lo = x + 1;
        else hi = x - 1;
    }
    cout << hi; // 範圍外代表無解

    // 二分找下界
    while (lo < hi) {
        int x = (lo + hi) / 2;
        if (check(m)) hi = x;
        else lo = x + 1;
    }
    cout << lo; // 保證有解

    while (lo <= hi) {
        int x = (lo + hi) / 2;
        if (check(m)) hi = x - 1;
        else lo = x + 1;
    }
    cout << lo; // 範圍外代表無解
}