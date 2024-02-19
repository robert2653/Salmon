#include <bits/stdc++.h>
using namespace std;
struct BIT {
    int n;
    vector<int> bit;
    BIT(int n) {
        this->n = n;
        bit.resize(n + 1, 0);
    }
    BIT(vector<int> &init) {
        this->n = init.size();
        bit.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            modify(i + 1, init[i]);
        }
    }
    void modify(int i, int val) {
        for (; i <= n; i += i & -i) {
            bit[i] += val;
        }
    }
    int query(int r) {
	    int ans = 0;
	    for (; r; r -= r & -r) ans += bit[r];
	    return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
struct TwoDimensionBIT {
    int nx, ny;
    vector<vector<int>> bit;
    TwoDimensionBIT(int x, int y) {
        nx = x; ny = y;
        bit.resize(x + 1, vector<int>(y + 1, 0));
    }
    void modify(int x, int y, int mod){
        for(; x <= nx; x += x & -x){
            for(int tmp = y; tmp <= ny; tmp += tmp & -tmp){
                bit[x][tmp] += mod;
            }
        }
    }
    int query(int r1, int r2){
        int ans = 0;
        for(; r1; r1 -= r1 & -r1){
            for(int tmp = r2; tmp; tmp -= tmp & -tmp){
                ans += bit[r1][tmp];
            }
        }
        return ans;
    }
};