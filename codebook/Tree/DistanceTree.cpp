int main(){
    int t;
    cin >> t;
    queue<ll> q1;
    ll arr[5010][4]; // 0 parent 1 length 2 ch 3 ch n
    while(t--){
        ll x,y;
        ll n;
        ll ans = 0;
        cin >> n;
        for(int i = 1;i <= n;i++){
            arr[i][2] = 0;
            arr[i][3] = 1;
        }
        for(int i = 2;i <= n;i++){
            cin >> arr[i][0];
            arr[arr[i][0]][2] ++;
        }
        for(int i = 2;i <= n;i++){
            cin >> arr[i][1];
        }
        for(int i = 2;i <= n;i++){
            if(arr[i][2] == 0)q1.push(i);
        }
        while(!q1.empty()){
            x = q1.front();
            q1.pop();
            y = arr[x][0];
            ans += (n-arr[x][3]) * arr[x][3] * 2 * arr[x][1];
            arr[y][3] += arr[x][3];
            arr[y][2] --;
            if(y == 1) continue;
            if(arr[y][2]==0)q1.push(y);
        }
        cout << ans << "\n";
    }
	return 0;
}
