void ternarySearch() {
    int lo = 0, hi = 10;
    while (lo <= hi) {
        int xl = lo + (hi - lo) / 3;
        int xr = hi - (hi - lo) / 3;
        int ansl = check(xl), ansr = check(xr);
        if (ansl < ansr) {
            lo = xl + 1;
        } else {
            hi = xr - 1;
        }
        // record ans and index
    }
}