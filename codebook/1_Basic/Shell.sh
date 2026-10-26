# ~/.bashrc
CXX="g++ -std=c++23 -Wall -g -DLOCAL -fsanitize=address,undefined"
run() {
	local b=./.$(hsh $1).out
	[ -x $b ] || $CXX $1 -o $b && $b "${@:2}"
}
hsh() {
	cpp $1 -dD -P -fpreprocessed 2>/dev/null | tr -d "[:space:]" | md5sum| cut -c -6
}