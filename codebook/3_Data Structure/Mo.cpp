struct Query { int id, l, r; };
void mo(vector<Query> &q) {
    int blk = sqrt(q.size());
    sort(q.begin(), q.end(), [&](const Query &a, const Query &b) {
        int x = a.l / blk, y = b.l / blk;
        return x == y ? a.r < b.r : x < y;
    });
}
int nl = 0, nr = -1;
for (auto [id, l, r] : qry) {
    while (nr < r) nr++, addR();
    while (l < nl) nl--, addL();
    while (r < nr) delR(), nr--;
    while (nl < l) delL(), nl++;
}