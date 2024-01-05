void nimGame(){// removes the last stick wins the game
    int n;
    cin >> n;
    ll x = 0;
    for(int i = 0;i < n;i++){
        ll tmp;
        cin >> tmp;
        x ^= tmp;
    }
    if(x) cout << "first\n";
    else cout << "second\n";
}

void nimGame2(){// removes 1, 2, or 3 sticks
    int n;
    cin >> n;
    ll x = 0;
    for(int i = 0;i < n;i++){
        ll tmp;
        cin >> tmp;
        x ^= (tmp % 4);
    }
    if(x) cout << "first\n";
    else cout << "second\n";
} 

int main(){
    int t;
    cin >> t;
    while(t--){
        nimGame2();
    }
    return 0;
}