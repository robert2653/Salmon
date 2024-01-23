// Construct VScode
// 1. instaint vscode & msys2, check desktop path of vscode
// 2. open mingw64, not ucrt64, "pacman -S --needed base-devel mingw-w64-x86_64-toolchain"
// 3. add C:\\msys64\\mingw64\\bin to environment path
// 4. (re)open vscode, instaint C/C++, run, choose g++
// 5. open settings -> compiler -> add compilerPath "C:\\msys64\\mingw64\\bin\\g++.exe"

// Make Codebook
// notebook-generator ./ --author "Salmon" --initials Salmon --columns 3 --output "CodeBook.pdf" --size 8

// Init
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
using pbds_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>
using pbds_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
struct cmp {    // 在有 template 的資結使用
    bool operator()(const int &a, const int &b){
        return a < b;
    } // sort, bound 不用 struct
};
struct edge {
    int from; int to;
    int weight;
};
struct node {
    int sum;
};
const int llinf = 4e18;
const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;
void solve(){

}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
}