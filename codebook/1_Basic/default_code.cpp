#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

void solve() {

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto s = chrono::high_resolution_clock::now();

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    auto e = chrono::high_resolution_clock::now();
    cerr << chrono::duration_cast<chrono::milliseconds>(e - s).count() << " ms\n";
    
    return 0;
}