// CCW needed, O(n + m)
double convexPolyDist(vector<P> a, vector<P> b) {
    int n = a.size(), m = b.size();
    int sa = 0, sb = 0;
    for (int i = 1; i < n; i++) if (a[i].y < a[sa].y) sa = i;
    for (int i = 1; i < m; i++) if (b[i].y > b[sb].y) sb = i;
    double ans = 1E18;
    for (int i = 0; i < n; i++) {
        P na = a[sa], nb = a[(sa + 1) % n];
        P eA = nb - na;
        while (sign(cross(eA, b[(sb + 1) % m] - b[sb])) > 0)
            sb = (sb + 1) % m;
        chmin(ans, distanceSS({na, nb}, {b[sb], b[(sb + 1) % m]}));
        sa = (sa + 1) % n;
    }
    return ans;
}