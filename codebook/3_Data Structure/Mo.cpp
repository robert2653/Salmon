struct query {
    int l, r, id;
};
void Mo(vector<query> &q) {
    int blk = sqrt(q.size());
    sort(q.begin(), q.end(), [&](const query &a, const query &b) {
        int x = a.l / blk, y = b.l / blk;
        return x == y ? a.r < b.r : x < y;
    });
}