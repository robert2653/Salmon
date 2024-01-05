#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
const int maxn = 2e5+5;
typedef struct {
    int u, v, w;
} project;
void compress(vector<int> &sorted, vector<project> &projects, vector<vector<pii>> &EndProjects){
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    for(int i = 0; i < projects.size(); i++){
        EndProjects[lower_bound(sorted.begin(), sorted.end(), projects[i].v) - sorted.begin() + 1]
        .push_back({lower_bound(sorted.begin(), sorted.end(), projects[i].u) - sorted.begin() + 1,
        projects[i].w});
    }
}
signed main(){
    int n; cin >> n;
    vector<project> projects(n);
    vector<vector<pii>> EndProjects(2 * n + 1);
    vector<int> nums;
    for(int i = 0; i < n; i++){
        cin >> projects[i].u >> projects[i].v >> projects[i].w;
        nums.push_back(projects[i].u);
        nums.push_back(projects[i].v);
    }
    compress(nums, projects, EndProjects);
    vector<int> dp(nums.size() + 1, 0);
    for(int end = 1; end <= nums.size(); end++){
        dp[end] = dp[end - 1];
        for(auto [from, gain] : EndProjects[end]){
            dp[end] = max(dp[end], dp[from - 1] + gain);
        }
    }
    cout << dp[nums.size()];
}
// Monotonic DP in campus contest, use monotonic stack
// first is lowest mountain, second is pref in stack