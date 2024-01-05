print(int(eval(input().replace('/','//'))))

t = int(input())
for _ in range(0,t):
    tmp = input().split(' ',1)
    n = int(tmp[0])
    arr = list(map(int,tmp[1].split(' ')))
    print(n)
    print(arr)
# 2
# 5 1 2 3 4 5
# 4 1 2 3 4
import sys # EOF
for line in sys.stdin:
    a = int(line)
    if a != 0:
        print(a)
# 1
# 2
# 3
