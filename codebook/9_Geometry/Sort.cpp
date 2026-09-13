// sort(ps.begin(), ps.end(), SweepCmp(l));
// set<P, SweepCmp> s {SweepCmp(l)};
struct SweepCmp { // 以 l 為掃描線, 點從最左邊排到最右邊 (dir: -1 -> 1)
	P d; // 同一條掃描線上的點, 依 l 的方向由起點排到終點
	SweepCmp(Line l) : d(l.b - l.a) {}
	bool operator()(P p, P q) const {
		int c = sign(cross(d, p - q));
		return c != 0 ? c > 0 : sign(dot(d, p - q)) < 0;
	}
}; // 17f9fd
struct PolarCmp { // 以 l.a 為中心, 從 l 的方向開始轉, 角度範圍 [0, 2 * PI)
	P o, d;
	int s;
	PolarCmp(Line l, int dir = 0) // dir = 0: CCW, 1: CW
		: o(l.a), d(l.b - l.a), s(dir ? -1 : 1) {}
	int half(P p) const { // 中心 -> 0, [0, PI) -> 1, [PI, 2 * PI) -> 2
		int c = sign(cross(d, p)) * s, t = sign(dot(d, p));
		return c == 0 && t == 0 ? 0 : c < 0 || (c == 0 && t < 0) ? 2 : 1;
	}
	bool operator()(P p, P q) const {
		p = p - o, q = q - o;
		if (half(p) != half(q)) return half(p) < half(q);
		int c = sign(cross(p, q)) * s;
		// 1: 同 set 視為相等, pbds_multiset >= (不管順序)
		return c > 0;
		// 2: 同點視為相等, 距離近的排前面, pbds_multiset <=
		return c != 0 ? c > 0 : abs2(p) < abs2(q);
	}
}; // 1: 77c30c, 2: 73c8dc