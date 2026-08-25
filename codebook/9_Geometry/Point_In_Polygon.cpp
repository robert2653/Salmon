bool pointInPolygon(P a, const vector<P> &p) {
	int n = p.size(), t = 0;
	for (int i = 0; i < n; i++)
		if (btw(a, {p[i], p[(i + 1) % n]})) return true;
	for (int i = 0; i < n; i++) {
		P u = p[i], v = p[(i + 1) % n];
		if (u.x < a.x && v.x >= a.x && dir(a, {v, u}) < 0) t ^= 1;
		if (u.x >= a.x && v.x < a.x && dir(a, {u, v}) < 0) t ^= 1;
	}
	return t == 1;
}