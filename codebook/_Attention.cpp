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
using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define int long long
typedef pair<int, int> pii;
typedef struct {
    int from; int to;
    int weight;
} edge;
typedef struct {
    int sum;
} Node;
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