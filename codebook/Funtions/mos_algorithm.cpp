#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; i++)
#define lrep(i, j, k) for(int i = j; i < k; i++)
#define all(x) x.begin(), x.end()
using namespace std;
typedef struct {
    int l, r, ind;
} query;
query queries[100];
int n, block, nums[100];
bool cmp(query a, query b){
    int block_a = a.l / block;
    int block_b = b.l / block;
    if(block_a != block_b) return block_a < block_b;
    return a.r < b.r;
}
void Mo(){
    // sort
    int cl = 1, cr = 0;
    for(auto i : queries){
        while(cl < i.l){}   // remove
        while(cr > i.r){}   // remove
        while(cl > i.l){}   // add
        while(cr < i.r){}   // add
    }
}
// Compress too big nums，gives new nums to them
void compress(){
    vector<pair<int, int>> compress(n);
    rep(i, 1, n){
        cin >> nums[i];
        compress[i-1] = {nums[i], i};
    }
    sort(all(compress));
    int pre = compress[0].first, new_num = 0;
    nums[compress[0].second] = 0;
    for(auto it = compress.begin() + 1, end = compress.end(); it != end; it++){
        if((*it).first != pre){
            pre = (*it).first;
            new_num++;
        }
        nums[(*it).second] = new_num;
    }
}