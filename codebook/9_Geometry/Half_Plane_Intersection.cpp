// non-strict -> >= 都改 >, assert 拿掉, 在外面特判直線(area == 0)
vector<P> hp(vector<Line> lines) {
	auto sgn = [](P p) { return p.y > 0 || (p.y == 0 && p.x > 0) ? 1 : -1; };
	sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
		auto d1 = l1.b - l1.a;
		auto d2 = l2.b - l2.a;
		if (sgn(d1) != sgn(d2)) return sgn(d1) == 1;
		return cross(d1, d2) > 0;
	});
	deque<Line> ls;
	deque<P> ps;
	for (auto l : lines) {
		if (ls.empty()) {
			ls.push_back(l);
			continue;
		}
		while (!ps.empty() && dir(ps.back(), l) >= 0) ps.pop_back(), ls.pop_back();
		while (!ps.empty() && dir(ps[0], l) >= 0) ps.pop_front(), ls.pop_front();
		if (sign(cross(l.b - l.a, ls.back().b - ls.back().a)) == 0) { // 平行
			if (sign(dot(l.b - l.a, ls.back().b - ls.back().a)) > 0) { // 同向
				if (dir(ls.back().a, l) >= 0) { // l 在內側
					assert(ls.size() == 1);
					ls[0] = l;
				}
				continue;
			}
			return {};
		}
		ps.push_back(lineIntersection(ls.back(), l));
		ls.push_back(l);
	}
	while (!ps.empty() && dir(ps.back(), ls[0]) >= 0)
		ps.pop_back(), ls.pop_back();
	if (ls.size() <= 2) return {};
	ps.push_back(lineIntersection(ls[0], ls.back()));
	return vector(ps.begin(), ps.end());
}