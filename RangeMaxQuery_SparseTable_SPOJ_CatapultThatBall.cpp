#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#define REP(i, a, b) for(int (i) = (a); (i) < (b); ++(i))
#define REPC(i, a, cond) for(int (i) = (a); (cond); ++(i))

using namespace std;

typedef long long ll;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef vector<VL> VVL;

void precompute(VL& ar, VVL& st){
    int n = ar.size();
    int k = st.size();

    REP(i, 0, n) st[0][i] = ar[i];

    REP(j, 1, k + 1) {
        REPC(i, 0, i + (1 << j) <= n) {
            st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }
}

void computeLog(VI& m_log){
    int n = m_log.size();
    m_log[1] = 0;
    REP(i, 2, n) m_log[i] = m_log[i / 2] + 1;
}

ll computeQueries(int l, int r, VVL& st, VI& m_log){
    int range = r - l + 1;
    int j = m_log[range];
    int mr = r - (1 << j) + 1;
    return max(st[j][l], st[j][mr >= l ? mr : l]);
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w+", stdout);

    int n, q;
    cin >> n >> q;
    VL ar(n);
    REP(i, 0, n) cin >> ar[i];

    // precompute the sparse table
    int k = (int)log2(n) + 1;
    VVL st(k + 1, VL(n, 0));
    precompute(ar, st);

    VI m_log(n + 1, 0);
    computeLog(m_log);

    int res = 0;
    REP(i, 0, q) {
        int l, r;
        cin >> l >> r;
        if (l > r) swap(l, r);
        if (r - l < 2) { res++; continue; }
        ll mmax = computeQueries(l, r - 2, st, m_log);
        if(mmax <= ar[l - 1]){
            res++;
        }
    }
    cout << res << "\n";
}
