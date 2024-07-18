int main() {
    int n; cin >> n;
    vector<P> P(n), U, L;
    for (int i = 0; i < n; i++) {
        cin >> P[i];
    }
    sort(P.begin(), P.end(), [](const Point<i64> &a, const Point<i64> &b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    for (int i = 0; i < n; i++) {
        while (L.size() >= 2 && cross(L.back() - L[L.size() - 2], P[i] - L[L.size() - 2]) <= 0LL) {
            L.pop_back();
        }
        while (U.size() >= 2 && cross(U.back() - U[U.size() - 2], P[i] - U[U.size() - 2]) >= 0LL){
            U.pop_back();
        }
        if (L.empty() || !(L.back() == P[i])) L.push_back(P[i]);
        if (U.empty() || !(U.back() == P[i])) U.push_back(P[i]);
    }
    if (L.size() <= 2 && U.size() <= 2) {
        // No Hull
    }
    cout << L.size() + U.size() - 2 << "\n";
    for (int i = 0; i < L.size() - 1; i++) {
        cout << L[i].x << " " << L[i].y << "\n";
    }
    for (int i = U.size() - 1; i > 0; i--) {
        cout << U[i].x << " " << U[i].y << "\n";
    }
}