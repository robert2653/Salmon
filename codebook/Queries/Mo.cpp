#include <bits/stdc++.h>
using namespace std;
struct query {
    int l, r, id;
} typedef query;
void MO(int n, vector<query> &queries){
    int block = sqrt(n);
    function <bool(query, query)> cmp = [&](query a, query b) {
        int block_a = a.l / block;
        int block_b = b.l / block;
        if(block_a != block_b) return block_a < block_b;
        return a.r < b.r;
    };
    sort(queries.begin(), queries.end(), cmp);
}
void compress(vector<int> &nums){
    vector<int> sorted = nums;
    sort(sorted.begin(), sorted.end());
    nums.erase(unique(sorted.begin(), sorted.end()), nums.end());
    for(int i = 0; i < nums.size(); i++){
        nums[i] = lower_bound(sorted.begin(), sorted.end(), nums[i]) - sorted.begin() + 1;
    }
}