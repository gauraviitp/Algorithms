from math import log2
import sys

sys.stdin = open('input.txt')
sys.stdout = open('output.txt', 'w')

f = sys.stdin
o = sys.stdout

def preprocess(ar):
    n = len(ar)
    k = int(log2(n)) + 1
    st = [[0 for i in range(n)] for j in range(k + 1)]

    # case when length of range is 1
    for i in range(n):
        st[0][i] = ar[i]

    # cases when length of range is power of two
    for j in range(1, k + 1):
        i = 0
        while i + (1 << j) <= n:
            st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))])
            i += 1

    return st

def computeLog(n):
    mlog = [0] * (n + 1)
    mlog[1] = 0
    for i in range(2, n + 1):
        mlog[i] = mlog[i // 2] + 1
    return mlog

def computeQueries(l, r, st, mlog):
    mrange = (r - l + 1)
    j = mlog[mrange]
    return max(st[j][l], st[j][r - (1 << j) + 1])

def main():
    n, q = map(int, f.readline().split())
    ar = list(map(int, f.readline().split()))
    st = preprocess(ar)
    mlog = computeLog(n)

    res = 0
    for i in range(q):
        l, r = map(int, f.readline().split())
        mmax = computeQueries(l, r - 2, st, mlog)
        if (mmax <= ar[l - 1]):
            res += 1
    o.write(str(res) + '\n')


if __name__ == '__main__':
    main()
