#include <bits/stdc++.h>

using namespace std;
using ll = long long;

namespace rgs = ranges;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T> bool chmin(T &a, const T &b) { return a > b && (a = b, true); }
template<class T> bool chmax(T &a, const T &b) { return a < b && (a = b, true); }

#ifdef CPH
template<class T> ostream &operator<<(ostream &o, vector<T> v) {
	for (T x : v) o << x << " ";
	return o;
}
template<class... T> void bug_(T... x) {
	((cerr << x << " "), ...);
	cerr << "\n";
}
#define bug(x...) bug_(__LINE__, "[" #x "]", x)
#else
#define bug(x...)
#endif

void solve() {
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
	
	return 0;
}