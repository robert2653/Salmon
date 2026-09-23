template<class T> struct ZKW {
	int n;
	vector<T> a;
	ZKW(int n) : n(n), a(2 * n) {}
	ZKW(const vector<T> &v) : n(v.size()), a(2 * n) {
		for (int i = 0; i < n; i++) a[i + n] = v[i];
		for (int i = n - 1; i > 0; i--) a[i] = a[2 * i] + a[2 * i + 1];
	}
	void modify(int p, const T &i) {
		a[p += n] = i;
		for (p /= 2; p > 0; p /= 2) a[p] = a[2 * p] + a[2 * p + 1];
	}
	T query(int l, int r) {
		T x{}, y{};
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l & 1) x = x + a[l++];
			if (r & 1) y = a[--r] + y;
		}
		return x + y;
	}
};