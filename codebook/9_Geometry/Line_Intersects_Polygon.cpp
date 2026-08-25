bool lineIntersectsPolygon(Line l, const vector<P> &p) {
	int n = p.size();
	for (int i = 0; i < n; i++) {
		P a = p[i], b = p[(i + 1) % n];
		if (dir(a, l) == 0 || dir(b, l) == 0) return true;
		if ((dir(a, l) < 0) ^ (dir(b, l) < 0)) return true;
	}
	return false;
}