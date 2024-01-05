int main(){
    int l = 1, r = 10;
    // 1 to tar, find tar
    while(l <= r){
        int m = (l + r) / 2;
        if(check(m)) l = m + 1;
        else r = m - 1;
    }
    cout << r;
    // tar to end
    while(l <= r){
        int m = (l + r) / 2;
        if(check(m)) r = m - 1;
        else l = m + 1;
    }
    cout << l;
}