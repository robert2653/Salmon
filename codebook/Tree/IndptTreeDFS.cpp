int yes[1002];
int no[1002];
vector <int> child[1002];
void ini(){
    memset(yes, 0, sizeof(yes));
    memset(no, 0, sizeof(no));
    for (int i=0; i<1002; i++) child[i].clear();
}
void DFS(int a){
    for (auto i:child[a]){
        DFS(i);
        yes[a]+=no[i];
        no[a]+=max(yes[i], no[i]);
    }
}
int main(){
    int T, a, b, c;
    cin >> T;
    while(T--){
        ini();
        cin >> a >> b;
        yes[1]=b;
        for (int i=2; i<=a; i++){
            cin >> c >> b;
            yes[i]=b;
            child[c].push_back(i);
        }
        DFS(1);
        cout << max(yes[1], no[1]) << '\n';
    }
}