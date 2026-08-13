const int N = 1E7; // 0 -> initial state
const int ALPHABET_SIZE = 26;
int tot = 0;
int trie[N][ALPHABET_SIZE], cnt[N];
void reset() {
	tot = 0, fill_n(trie[0], ALPHABET_SIZE, 0);
}
int newNode() {
	int x = ++tot;
	cnt[x] = 0, fill_n(trie[x], ALPHABET_SIZE, 0);
	return x;
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