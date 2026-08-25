vector<P> convexHull(vector<P> a) {
	sort(a.begin(), a.end());
	a.resize(unique(a.begin(), a.end()) - a.begin());
	if (a.size() <= 1) return a;
	vector<P> h(a.size() * 2);
	int s = 0, t = 0;
	for (int i = 0; i < 2; i++, s = --t) {
		for (P p : a) {
			while (t >= s + 2 && sign(cross(h[t - 1] - h[t - 2], p - h[t - 2])) <= 0) t--;
			h[t++] = p;
		}
		reverse(a.begin(), a.end());
	}
	return {h.begin(), h.begin() + t};
}