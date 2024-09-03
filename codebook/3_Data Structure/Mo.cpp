struct query {
    int l, r, id;
};
void Mo(vector<query> &q) {
    int block = sqrt(q.size());
    sort(q.begin(), q.end(), [&](const query &a, const query &b) {
        int x = a.l / block;
        int y = b.l / block;
        if (x != y) return x < y;
        return a.r < b.r;
    });
}