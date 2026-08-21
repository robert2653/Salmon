// ak = sum_{d|k} a[d] (zeta, a \ast 1)
// ck = sum_{d|k} mu[d] * a[k/d] (inv zeta, a \ast mu)
template<class T> vector<T> zeta(vector<T> a, bool inv = false) {
	int n = a.size() - 1;
	for (int p : primes)
		if (inv) for (int i = n / p; i >= 1; i--) a[i * p] -= a[i];
		else for (int i = 1; i <= n / p; i++) a[i * p] += a[i];
	return a;
	// less implementation
	if (inv) for (int i = 1; i <= n; i++)
		for (int j = 2 * i; j <= n; j += i) a[j] -= a[i];
	else for (int i = n; i >= 1; i--)
		for (int j = 2 * i; j <= n; j += i) a[j] += a[i];
}
// ck = sum_{lcm(i,j)=k} a[i] * b[j]
template<class T> vector<T> conv(vector<T> a, vector<T> b) {
	a = zeta(a), b = zeta(b);
	for (int i = 1; i < a.size(); i++) a[i] *= b[i];
	return zeta(a, true);
}