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

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    llt n=4;
    vector<pair<llt, llt>> m={{1, 2}, {3, 4}};

    DSU dsu(n); // 宣告一個 dsu 物件，大小為 n (1~n)

    dsu.merge(1, 2); // 合併點 1 所在的集合與點 2 所在的集合
    dsu.merge(3, 4); // 合併點 3 所在的集合與點 4 所在的集合

    cout<<dsu.find_boss(1)<<endl; //輸出點 1 的 parent 是誰 (輸出: 1)

    cout<<dsu.same(1, 3)<<endl; // 確認點 1 與 點 3 的 parent 是否相同 (輸出: 0)

    cout<<dsu.size(1)<<endl; // 取得點 1所在的集合大小 (輸出: 2)

    for(auto x: dsu.boss) cout<<x<<" "; //直接存取 boss 陣列，(輸出: 0 1 1 3 3)
    cout<<endl;

    return 0;
}
