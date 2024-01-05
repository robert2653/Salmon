vector<int>a,tmp;
int ans;//ans = 0 change time
void msort(int s,int t) { //start end
	if(s==t) return ;
	int mid=(s+t)>>1;
	msort(s,mid),msort(mid+1,t);
	
	int i=s,j=mid+1,k=s;
	while(i<=mid && j<=t) {
		if(a[i]<=a[j]) tmp[k]=a[i],k++,i++;
		else tmp[k]=a[j],k++,j++,ans+=mid-i+1;
	}
	while(i<=mid) tmp[k]=a[i],k++,i++;
	while(j<=t) tmp[k]=a[j],k++,j++;
	for(int i=s;i<=t;i++) a[i]=tmp[i];
	return ;
}
int main(){
    int t;
    cin >> t;
    while (t--)
    {
        ans = 0;
        int n,tmp2;
        cin >> n;
        a.clear();
        tmp.clear();
        for(int i = 0;i < n;i++){
            cin >> tmp2;
            a.push_back(tmp2);
            tmp.push_back(tmp2);
        }
        msort(0,n-1);
        cout << ans << '\n';
    }
    return 0;
}