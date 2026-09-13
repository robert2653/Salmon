# ~/.bashrc
CXX="g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined"
run() {
    local b=./.$(hash $1).out
    [ -x $b ] || $CXX $1 -o $b && $b "${@:2}"
}
hash() {
    cpp $1 -dD -P -fpreprocessed | tr -d "[:space:]" | md5sum| cut -c -6
}