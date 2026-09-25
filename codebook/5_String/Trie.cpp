const int N = 1E7; // 0 -> initial state
const int ALPHABET_SIZE = 26;
int tot = 0;
int trie[N][ALPHABET_SIZE], cnt[N];
int newNode() {
	tot++;
	fill_n(trie[tot], ALPHABET_SIZE, 0);
	cnt[tot] = 0;
	return tot;
}
void reset() {
	tot = -1;
	newNode();
}
void add(const string &s, int i = 0, int p = 0) {
	if (i == s.size()) {
		cnt[p]++;
		return;
	}
	int &q = trie[p][s[i] - 'a'];
	if (!q) q = newNode();
	add(s, i + 1, q);
}
int find(const string &s, int i = 0, int p = 0) {
	if (i == s.size()) return cnt[p];
	int q = trie[p][s[i] - 'a'];
	if (!q) return 0;
	return find(s, i + 1, q);
}