int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int x = 5328; // 00000000000000000001010011010000
    cout << __builtin_clz(x) << '\n'; //19 0 infront
    cout << __builtin_ctz(x) << '\n'; // 4 0 behind
    cout << __builtin_popcount(x) << '\n'; // how many 1
    x |= (1 << k) // k to 1
    x &= ~(1 << k); //k to 0

    for(int i = 31;i >= 0;i--){
        if(x & (1<<i))cout << '1';
        else cout << '0';
    }
    return 0;
}