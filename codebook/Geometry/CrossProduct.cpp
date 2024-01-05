const double EPS = 1e-9;
struct point{
    double x, y;
    point operator * (ll a){return {a * x, a * y};}
    point operator + (point b){return {x + b.x, y + b.y};}
    point operator - (point b){return {x - b.x, y - b.y};}
    double operator * (point b){return x * b.x + y * b.y;}
    double operator ^ (point b){return x * b.y - y * b.x;}
    bool operator < (point b){return x == b.x ? y < b.y : x < b.x;}
};
// len
double abs(point a){return sqrt(a.x * a.x + a.y * a.y);}
int sign(double a){
    if(abs(a) < EPS)
        return 0;
    else
        return (a > 0 ? 1 : -1);
}
//cross product
int ori(point a,point b,point c){
    return sign((b - a) ^ (c - a));
}
bool colinear(point a,point b,point c){
    return sign((b - a) ^ (c - a)) == 0;
}
bool between(point a,point b,point c){ // c between a and b
    if(!colinear(a,b,c))
        return false;
    return sign((a - c) * (b - c)) <= 0;
}
bool intersect(point a,point b,point c,point d){ // line(a,b) line(c,d)
    int abc = ori(a,b,c);
    int abd = ori(a,b,d);
    int cda = ori(c,d,a);
    int cdb = ori(c,d,b);
    if(abc == 0 || abd == 0)
        return between(a,b,c) || between(a,b,d) || between(c,d,a) || between(c,d,b);
    return abc * abd <= 0 && cda * cdb <= 0;
}
int main(){
    int n;
    cin >> n;
    point p[1010];
    cin >> p[0].x >> p[0].y;
    ll ans  = 0;
    for(int i = 1;i < n;i++){
        cin >> p[i].x >> p[i].y;
        ans += (p[i] ^ p[i - 1]);
    }
    ans += (p[0] ^ p[n - 1]);
    cout << abs(ans) << '\n';

    return 0;
}