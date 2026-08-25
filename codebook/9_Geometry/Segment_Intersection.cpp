// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
tuple<int, P, P> segmentIntersection(Line l1, Line l2) {
	if (parallel(l1, l2)) {
		if (dir(l1.a, l2) != 0) return {0, {}, {}};
		else {
			vector<P> res;
			if (btw(l1.a, l2)) res.push_back(l1.a);
			if (btw(l1.b, l2)) res.push_back(l1.b);
			if (btw(l2.a, l1)) res.push_back(l2.a);
			if (btw(l2.b, l1)) res.push_back(l2.b);
			if (res.empty()) return {0, {}, {}};
			sort(res.begin(), res.end());
			res.resize(unique(res.begin(), res.end()) - res.begin());
			if (res.size() == 1) return {3, res[0], res[0]};
			else return {2, res.front(), res.back()};
		}
	}
	auto cp1 = dir(l2.b, l1), cp2 = dir(l2.a, l1), cp3 = dir(l1.b, l2), cp4 = dir(l1.a, l2);
	if ((cp1 > 0 && cp2 > 0) ||
		(cp1 < 0 && cp2 < 0) ||
		(cp3 > 0 && cp4 > 0) ||
		(cp3 < 0 && cp4 < 0)) return {0, {}, {}};
	P p = lineIntersection(l1, l2);
	if (cp1 != 0 && cp2 != 0 && cp3 != 0 && cp4 != 0) return {1, p, p};
	else return {3, p, p};
}