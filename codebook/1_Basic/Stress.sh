# 對拍
set -e
for f in a b gen; do g++ -O2 $f.cpp -o $f; done
for ((i=1;;i++)); do
	echo $i
	./gen $i > in
	./a < in > o1
	./b < in > o2
	cmp o1 o2 || break
done
# 多重解, checker: cin 讀測資, ifstream out(argv[1]), 用 assert
set -e
for f in a gen checker; do g++ -O2 $f.cpp -o $f; done
for ((i=1;;i++)); do
	echo $i
	./gen $i > in
	./a < in > o1
	./checker o1 < in || break
done
# 互動
set -e
for f in a interact; do g++ -O2 $f.cpp -o $f; done
rm -f p1 p2; mkfifo p1 p2
for ((i=1;;i++)); do
	echo $i
	./a < p1 > p2 & pid=$!
	(exec 3>p1 4<p2; ./interact $i <&4 >&3) || break
	wait $pid || break
done