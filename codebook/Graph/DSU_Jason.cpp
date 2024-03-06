#include <bits/stdc++.h>
using namespace std;
typedef long long int llt;

struct DSU {
    vector<llt> boss, siz; //boss 是 1-index 的
    DSU (llt n){
        boss.resize(n + 1);
        iota(boss.begin(), boss.end(), 0);
        siz.assign(n + 1, 1);
    }
    llt find_boss(llt x){ // 尋找點 x 的 parent
        if(boss[x] == x) return x;
        return boss[x] = find_boss(boss[x]);
    }
    bool same(llt x, llt y) { // 判斷兩個點 x, y 是否處於同一個集合中
        return find_boss(x) == find_boss(y);
    }
    bool merge(llt x, llt y){ // 將兩個點 x, y 所在的集合合併
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
    llt size(llt x){ // 取得點 x 所在集合的元素個數
        return siz[find_boss(x)];
    }
};
