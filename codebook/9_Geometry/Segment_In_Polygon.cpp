bool segmentInPolygon(Line l, const vector<P> &p) {
	int n = p.size();
	vector<P> a {l.a, l.b};
	for (int i = 0; i < n; i++) {
		auto [t, p1, p2] = segmentIntersection(l, {p[i], p[(i + 1) % n]});
		if (t == 1 || t == 3) a.push_back(p1);
		else if (t == 2) a.push_back(p1), a.push_back(p2);
	}
	sort(a.begin(), a.end());
	for (int i = 0; i + 1 < a.size(); i++) {
		if (sign(abs(a[i] - a[i + 1])) == 0) continue;
		if (!pointInPolygon((a[i] + a[i + 1]) / 2, p)) return false;
	}
	return true;
}