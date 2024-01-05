
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> pi;

int main(){
    int num;
    vector<int> a;
    int N;
    cin >> N;
    for(int i =  0;i < N;i++){
        ll tmp = nxt();
        a.push_back(tmp);
    }
    int dp[N+1];
    vector<int> v;
    dp[0] = 1;
    v.push_back(a[0]);
    int L = 1; //LIS length
    for (int i=1; i<N; i++){
        if (a[i] > v.back()){
            v.push_back(a[i]);
            L++;
            dp[i] = L;
        } else {
            auto it = lower_bound(v.begin(), v.end(), a[i]);
            *it = a[i];
            dp[i] = (int) (it - v.begin() + 1);
        }
    }
    cout << L << '\n';
    vector<int> ans;
    for (int i=N-1; i>=0; i--){
        if (dp[i] == L){
            ans.push_back(a[i]);
            L--;
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto i: ans){
        cout << i << ' ';
    }
    cout << '\n';
    return 0;
}