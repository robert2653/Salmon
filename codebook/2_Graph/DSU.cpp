#include <bits/stdc++.h>
using namespace std;
struct DSU {
    vector<int> boss, siz;
    DSU(int n) {    // 1 based
        boss.resize(n + 1);
        iota(boss.begin(), boss.end(), 0);
        siz.assign(n + 1, 1);
    }
    int find_boss(int x) {
        if(boss[x] == x) return x;
        return boss[x] = find_boss(boss[x]);
    }
    bool same(int x, int y) {
        return find_boss(x) == find_boss(y);
    }
    bool merge(int x, int y) {
        x = find_boss(x);
        y = find_boss(y);
        if (x == y) {
            return false;
        }
        if(siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        boss[y] = x;
        return true;
    }
    int size(int x) {
        return siz[find_boss(x)];
    }
};