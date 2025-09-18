from decimal import * # 無誤差浮點數
from fractions import * # 分數
from random import *
from math import *
# set decimal prec if it could overflow in precision
setcontext(Context(prec=10, Emax=MAX_EMAX, rounding=ROUND_FLOOR))
# read and print
x = int(input())
a, b, c = list(map(Fraction, input().split()))
arr = list(map(Decimal, input().split()))
print(*arr)
# set
st = set(); st.add((a, b)); st.remove((a, b))
if not (a, b) in st:
# dict
d = dict(); d[(a, b)] = 1; del d[(a, b)]
for (a, b) in d.items():
# random
arr = [randint(l, r) for i in range(size)]
choice([8, 6, 4, 1]) # random pick one
shuffle(arr)