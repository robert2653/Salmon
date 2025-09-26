CODE1="a"
CODE2="ac"
set -e
g++ $CODE1.cpp -o $CODE1
g++ $CODE2.cpp -o $CODE2
for ((i=0;;i++))
do
    echo "$i"
    g++ gen.cpp -o gen
    ./gen > input
    # python3 gen.py > input
    ./$CODE1 < input > $CODE1.out
    ./$CODE2 < input > $CODE2.out
    cmp $CODE1.out $CODE2.out || break
done