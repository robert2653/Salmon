struct Info {
	int siz = 0, vsiz = 0, psiz = 0; // 真實子樹大小, 虛子樹大小, 實鏈長度
	ll val = 0, sum = 0, vsum = 0, psum = 0;
	void apply(const Tag &t) {
		val = (val * t.mul % Mod + t.add) % Mod;
		sum = (sum - psum + Mod) % Mod;
		psum = (psum * t.mul % Mod + t.add * psiz % Mod) % Mod;
		sum = (sum + psum) % Mod;
	}
	void pull(const Info &l, const Info &r) {
		psiz = 1 + l.psiz + r.psiz;
		siz = 1 + l.siz + r.siz + vsiz;
		psum = (l.psum + r.psum + val) % Mod;
		sum = (l.sum + r.sum + val + vsum) % Mod;
	}
	void modify(const Info &i) { // 才不會蓋掉 vsum, vsiz
		val = i.val;
	} // 下面的 modify 也要改，不能直接 =
	void operator+=(const Info &i) { // 將實邊轉虛邊時加上資訊
		vsiz += i.siz;
		vsum = (vsum + i.sum) % Mod;
	}
	void operator-=(const Info &i) { // 將虛邊轉實邊時扣除資訊
		vsiz -= i.siz;
		vsum = (vsum - i.sum % Mod + Mod) % Mod;
	}
	Info asSubtree() const { // 當前節點作為 Virtual Subtree 根時的狀態
		Info res;
		res.siz = vsiz + 1;
		res.sum = (vsum + val) % Mod;
		return res;
	}
};
struct LinkCutTree { // 加在註解後面
	int access(int x) { // ...splay(x);
		if (ch[x][1]) info[x] += info[ch[x][1]]; // 原右子樹轉虛邊
		if (c) info[x] -= info[c];               // 虛邊轉新右子樹
	}
	void link(int rt, int x) { // ...p[rt] = x;
		info[x] += info[rt]; // rt 成為 x 的虛子樹
	}
	Info subtreeQuery(int rt, int x) { // 以 rt 當 root, x 的 subtree
		assert(connected(rt, x));
		makeRoot(rt);
		access(x), splay(x);
		return info[x].asSubtree();
	}
	Info componentQuery(int x) {
		makeRoot(x);
		return info[x];
	}
};