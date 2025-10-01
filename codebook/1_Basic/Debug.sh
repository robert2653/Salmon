# 對拍
CODE1="a"
CODE2="ac"
set -e
g++ $CODE1.cpp -o $CODE1
g++ $CODE2.cpp -o $CODE2
g++ gen.cpp -o gen
for ((i=1;;i++))
do
    echo "--- Testing: Case #$i ---"
    ./gen > input
    # python3 gen.py > input
    ./$CODE1 < input > $CODE1.out
    ./$CODE2 < input > $CODE2.out
    cmp $CODE1.out $CODE2.out || break
done
# 多重解, ifstream in(argv[1]);
CODE="a"
set -e
g++ $CODE.cpp -o $CODE
g++ gen.cpp -o gen
g++ checker.cpp -o checker
for ((i=1;;i++))
do
    ./gen > input
    ./$CODE < input > $CODE.out
    ./checker $CODE.out < input || break
# 互動
CODE="a"
set -e
g++ $CODE.cpp -o $CODE
g++ checker.cpp -o checker
PIPE_IN="in"
PIPE_OUT="out"
trap 'rm -f $PIPE_IN $PIPE_OUT' EXIT
mkfifo $PIPE_IN $PIPE_OUT
for ((i=1;;i++))
do
    echo "--- Testing: Case #$i ---"
    ./$CODE < $PIPE_IN > $PIPE_OUT &
    (exec 3>$PIPE_IN 4<$PIPE_OUT; ./checker <&4 >&3) || break
done
# 參考 checker
ll AC(int n) { return ans; }
void WA(string log = "") { cerr << log << endl; exit(1); }
void checkAC(string log = "") {
    string trash;
    if (cin >> trash) WA("redundant output\n" + log);
}
int main() {
    int n = uniform_int_distribution<int>(1, 10)(rng);
    ll sol = AC(n);
    stringstream log;
    cout << n << endl;
    log << n << endl;
    log << "judge: " << endl;
    log << "team: " << endl;
    WA(log.str());
    checkAC();
    return 0;
}