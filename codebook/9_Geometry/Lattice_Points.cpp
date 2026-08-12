// (interior, boundary)
pair<ll, ll> latticePoints(int n, vector<P> p, ll area2) {
    ll bnd = 0;
    p.push_back(p[0]);
    for (int i = 0; i < n; i++)
        bnd += gcd(abs(p[i + 1].x - p[i].x), abs(p[i + 1].y - p[i].y));
    return {(area2 - bnd) / 2 + 1, bnd};
}