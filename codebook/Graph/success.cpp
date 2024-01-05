ll succ(ll n,ll k){
    if(k == 1)return succ(n);
    return succ(succ(x,k/2),k/2);
}

ll a = v[i];
ll b = v[v[i]];
while(a != b){
    a = v[a];
    b = v[v[b]];
}

a = i;
while(a != b){
    a = v[a];
    b = v[b];
}
ll first = a; // cycle first

b = v[a];
ll length = 1; // cycle
while(a != b){
    b = v[b];
    length++;
}