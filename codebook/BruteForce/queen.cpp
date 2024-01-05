int n = 4;
int cnt;
bool col[5],diag1[5],diag2[5];
void search(int y){
    if(y == n){
        cnt ++;
    }
    else{
        REP(x,0,n-1){
            if(col[x] || diag1[y+x] || diag2[x-y+n-1])continue;
            col[x] = diag1[y+x] = diag2[x-y+n-1] = 1;
            search(y+1);
            col[x] = diag1[y+x] = diag2[x-y+n-1] = 0;
        }
    }
}

int main(){
    cin >> n;
    search(0);
    cout << cnt << '\n';
}