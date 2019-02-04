from math import log2
import sys

sys.stdin = open('input.txt')
sys.stdout = open('output.txt', 'w')

f = sys.stdin
o = sys.stdout

def preprocess(ar):
    n = len(ar)
    k = int(log2(n)) + 1
    st = [[0 for j in range(k + 1)] for i in range(n)]

    # case when length of range is 1
    for i in range(n):
        st[i][0] = ar[i]

    # cases when length of range is power of two
    for j in range(1, k + 1):
        i = 0
        while i + (1 << j) <= n:
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1])
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
    return min(st[l][j], st[r - (1 << j) + 1][j])

def main():
    n = int(f.readline())
    ar = list(map(int, f.readline().split()))
    st = preprocess(ar)
    mlog = computeLog(n)

    q = int(f.readline())
    for i in range(q):
        l, r = map(int, f.readline().split())
        res = computeQueries(l, r, st, mlog)
        o.write(str(res) + '\n')


if __name__ == '__main__':
    main()
