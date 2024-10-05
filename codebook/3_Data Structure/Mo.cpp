struct Query {
    int l, r, id;
};
void Mo(vector<Query> &q) {
    int blk = sqrt(q.size());
    sort(q.begin(), q.end(), [&](const Query &a, const Query &b) {
        int x = a.l / blk, y = b.l / blk;
        return x == y ? a.r < b.r : x < y;
    });
}