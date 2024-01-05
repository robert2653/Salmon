const int N = 100000010;
bool not_prime[N];
vector<int>prime;
void linear_sieve(){
    int i;
    prime.push_back(2);
    for (i = 3; i*i<=N; i+=2){
        if (!not_prime[i]) prime.push_back(i);
        for(int j = i*i,k=i+i;j <= N;j += k){
            not_prime[j] = true;
        }
    }
    for(;i <= N;i+=2){
        if(!not_prime[i]){
            prime.push_back(i);
        }
    }
}
void Divisors(){
    vi p(1000010);
    for(int i = 2;i < N;i++){
        if(!p[i]){
            for(int j = i;j < N;j+= i){
                p[j] = i;
            }
        }
    }
}

// sum of factors
// pi^(ai+1)-1/(pi-1)

// product of factors
// n ^ (numbers of factors)
// pi = pi-1^(ki+1) * xi ^ (ki*(ki+1)/2) ^ Ci-1
int main(){
    linear_sieve();
    for(auto x:prime) cout << x <<' ';
    return 0;
}