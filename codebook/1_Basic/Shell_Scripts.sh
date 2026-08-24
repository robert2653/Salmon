# ~/.bashrc
CXX="g++ -std=c++17 -Wall -Wextra"
DBG="-g -fsanitize=address,undefined -D_GLIBCXX_DEBUG"
test() { $CXX $DBG $1 && ./a.out "${@:2}"; }
run() { $CXX -O2 $1 && time ./a.out "${@:2}"; }
# ~/.vimrc
se nu ai et ru ic is sc cul re=1 ts=4 sts=4 sw=4 ls=2 mouse=a