#include <bits/stdc++.h>
using namespace std;
#define ll long long
typedef struct {
    int set_val, add, sum, val;
} node;
int n, q; node tree[100]; int nums[100]; int BIT[100];
#define lp 2*now
#define rp 2*now+1
#define mid (L+R)/2
// Pull
void pull(int now){  // update now with 2 children
    // use lc、rc to undate now
    // tree[now].sum = tree[lp].sum + tree[rp].sum;
    // tree[now].prefix = max(tree[lp].sum+tree[rp].prefix, tree[lp].prefix);
    // tree[now].suffix = max(tree[lp].suffix+tree[rp].sum, tree[rp].suffix);
    // tree[now].middle_max = max(max(tree[lp].middle_max, tree[rp].middle_max), tree[lp].suffix+tree[rp].prefix);
    // tree[now].middle_max = max(max(tree[now].middle_max, tree[now].prefix), tree[now].suffix);
}
// Lazy
void push(int now, int child){
    if(tree[now].set_val){
        tree[child].set_val = 1;
        tree[child].val = tree[now].val;
        tree[child].add = tree[now].add;
    }
    else {
        tree[child].add += tree[now].add;
    }
}
void apply_tag(int now, int L, int R){
    if(tree[now].set_val)
        tree[now].sum = (R-L+1)*tree[now].val;
    tree[now].sum += (R-L+1)*tree[now].add;
    if(L != R){ // can go lower
        push(now, lp);
        push(now, rp);
    }
    tree[now].add = tree[now].set_val = 0;  // Reset
}
// Build
void build(int L, int R, int now){
    if(L == R){
        // init tree[now];
        return;
    }
    int M = mid;
    build(L, M, lp);
    build(M + 1, R, rp);
    pull(now);
}
// modify
void modify(int l, int r, int L, int R, int now){
    if(R < l || r < L || L > n) // invalid range
        return;
    if(l <= L && R <= r){
        // modify tree[now];
        // tree[now].add += add;    // modify_add
        // tree[now].set_val = 1;   // modify_mod
		// tree[now].val = mod;
		// tree[now].add = 0;  // Set is more prior
        return;
    }
    int M = mid;
    apply_tag(now, L, R);
    modify(l, r, L, M, lp);
    modify(l, r, M+1, R, rp);
    apply_tag(lp, L, M);	// need
    apply_tag(rp, M+1, R);	// need
    pull(now);  // update now with 2 children
}
// query
ll query(int l, int r, int L, int R, int now){
    int M = mid;
    if(R < l || r < L || L > n){
        return 0;
    }
    // apply_tag(now, L, R);   // Lazy to uncomment
    if(l <= L && R <= r){
        return tree[now].sum;
    }
	return query(l, r, L, M, lp) + query(l, r, M+1, R, rp);
}
// pizza_queries
// Left(s < t): dis_l = (pizza[s] - s) + t;
// Right(t < s): dis_r = (pizza[s] + s) - t;

// List Removals
// Use seg_tree to maintain how many nums have been selected in the range
// Use binary_Search to find "mod" nums have been selected before ans
// if ans - mod == pos，nums[ans] is the answer，and we modify tree[pos]

// polynomial queries
// Lazy_seg，set under and distance