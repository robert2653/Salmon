// 如何安裝 vscode
// 1. 下載 vscode & msys2
// 2. 在跳出的 terminal 中 / 或打開 ucrt64，打上 "pacman -S --needed base-devel mingw-w64-x86_64-toolchain"
// 3. 環境變數加上 C:\\msys64\\ucrt64\\bin
// 4. 重開 vscode, 載 C/C++, 運行, 編譯器選擇 g++
// 5. 打開 settings -> compiler -> add compilerPath -> 在 "" 裡打上 C:\\msys64\\ucrt64\\bin\\g++.exe

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define endl "\n"
#define int long long
using namespace std;
using namespace __gnu_pbds;
template<typename T>
using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>
using pbds_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct cmp {    // 在有 template 的資結使用
    bool operator()(const int &a, const int &b) const {
        return a < b;
    }
    // sort, bound 不用 struct
    // priority queue 小到大是 > , set 是 <
    // set 不能 = , multiset 要 = 
    // 每個元素都要比到，不然會不見
    // pbds_multiset 的 upper_bound 跟 lower_bound 功能相反, 如果要 find, 插入 inf 後使用 upper_bound
    // 內建 multiset 可以跟 set 一樣正常使用, 自定義比較結構就比照以上
};

const int llinf = 4e18;
const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;

void solve() {

}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}