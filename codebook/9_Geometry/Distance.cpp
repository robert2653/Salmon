double distPL(P p, Line l) {
	return abs(cross(l.a - l.b, l.a - p)) / abs(l);
} // 501648
double distancePS(P p, Line l) {
	if (sign(dot(p - l.a, l.b - l.a)) < 0) return abs(p - l.a);
	if (sign(dot(p - l.b, l.a - l.b)) < 0) return abs(p - l.b);
	return distPL(p, l);
} // ffe672
double distanceSS(Line l1, Line l2) {
	if (get<0>(segmentIntersection(l1, l2)) != 0) return 0.0;
	return min({distancePS(l1.a, l2), distancePS(l1.b, l2), distancePS(l2.a, l1), distancePS(l2.b, l1)});
} // fa7723