pair<double, P> minCircleCover(int n, vector<P> a) {
	shuffle(a.begin(), a.end(), rng);
	P c = a[0]; double r = 0;
	for (int i = 1; i < n; i++) if (sign(abs(c - a[i]) - r) > 0) {
		c = a[i], r = 0;
		for (int j = 0; j < i; j++) if (sign(abs(c - a[j]) - r) > 0) {
			c = (a[i] + a[j]) / 2.0;
			r = abs(c - a[i]);
			for (int k = 0; k < j; k++) if (sign(abs(c - a[k]) - r) > 0) {
				P p = (a[j] + a[i]) / 2;
				P q = (a[j] + a[k]) / 2;
				if (parallel({a[i], a[j]}, {a[j], a[k]})) continue;
				c = lineIntersection({p, p + rot(a[j] - a[i])}, {q, q + rot(a[k] - a[j])});
				r = abs(c - a[i]);
			}
		}
	}
	return {r, c};
}