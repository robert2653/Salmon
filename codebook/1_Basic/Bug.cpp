#ifdef LOCAL
template<class T> ostream &operator<<(ostream &o, vector<T> v) {
	for (T x : v) o << x << " ";
	return o;
}
template<class... T> void bug_(T... x) {
	cerr << "\e[36m";
	((cerr << x << " "), ...);
	cerr << "\e[0m\n";
}
#define bug(x...) bug_(__LINE__, "[" #x "]", x)
#else
#define bug(x...)
#endif