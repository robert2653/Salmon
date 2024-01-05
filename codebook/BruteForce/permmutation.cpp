int n;
vi subset;
void search(int k){
    if(k == n + 1){
        for(auto x:subset){
        cout << x << ' ';
        }
        cout << '\n';
    }
    else{
        subset.push_back(k);
        search(k + 1);
        subset.pop_back();
        search(k + 1);
    }
}

vi permutation;
bool chosen[10];
void search2(){
    if(permutation.size() == n){
        for(auto x:permutation){
        cout << x << ' ';
        }
        cout << '\n';
    }
    else{
        for(int i = 0;i < n;i++){
            if(chosen[i]) continue;
            chosen[i] = true;
            permutation.push_back(i);
            search2();
            chosen[i] = false;
            permutation.pop_back();
        }
    }
}

int main(){
    cin >> n;
    for(int i = 0;i < n;i++){
        permutation.push_back(i);
    }
    do{
        for(auto x:permutation){
        cout << x << ' ';
        }
        cout << '\n';
    }while(next_permutation(permutation.begin(), permutation.end()));
    // search2();
    return 0;
}