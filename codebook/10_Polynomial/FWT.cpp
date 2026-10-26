template<class T> void fwt(vector<T> &a, bool inv = false) {
	// Or : [[1, 0], [1, 1]] <-> [[1, 0], [-1, 1]]
	// And: [[1, 1], [0, 1]] <-> [[1, -1], [0, 1]]
	// Xor: [[1, 1], [1, -1]] <-> [[0.5, 0.5], [0.5, -0.5]]
	// *inv_2 instead of /2 for Z
	int n = 1;
	while (n < a.size()) n *= 2;
	a.resize(n);
	for (int i = 1; i < n; i *= 2) {
		for (int j = 0; j < n; j += 2 * i) {
			for (int k = 0; k < i; k++) {
				T x = a[j + k];
				T y = a[i + j + k];
				if (!inv) {
					a[j + k] = x + y;
					a[i + j + k] = x - y;
				} else {
					a[j + k] = (x + y) / 2;
					a[i + j + k] = (x - y) / 2;
				}
			}
		}
	}
}