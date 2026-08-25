// 0 : strictly outside
// 1 : on boundary
// 2 : strictly inside
int pointInConvexPolygon(P a, const vector<P> &p) {
	int n = p.size();
	if (n == 0) return 0;
	else if (n <= 2) return btw(a, {p[0], p.back()});
	if (btw(a, {p[0], p[1]}) || btw(a, {p[0], p[n - 1]})) return 1;
	else if (dir(a, {p[0], p[1]}) < 0 || dir(a, {p[0], p[n - 1]}) < 0) return 0;
	int lo = 1, hi = n - 2;
	while (lo < hi) {
		int x = (lo + hi + 1) / 2;
		if (dir(a, {p[0], p[x]}) < 0) lo = x;
		else hi = x - 1;
	}
	if (dir(a, {p[lo], p[lo + 1]}) < 0) return 2;
	else return btw(a, {p[lo], p[lo + 1]});
}