#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

#define REP(i, a, b) for(int (i) = (a); (i) < (b); ++(i))
#define REPC(i, a, cond) for(int (i) = (a); (cond); ++(i))

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef vector<VL> VVL;
typedef unordered_map<ll, VI> MLI;

void precompute(VL& ar, VVL& stmax, VVL& stmin){
    int n = ar.size();
    int k = stmax.size();

    REP(i, 0, n) {
        stmax[0][i] = ar[i];
        stmin[0][i] = ar[i];
    }

    REP(j, 1, k + 1) {
        REPC(i, 0, i + (1 << j) <= n) {
            stmax[j][i] = max(stmax[j - 1][i], stmax[j - 1][i + (1 << (j - 1))]);
            stmin[j][i] = min(stmin[j - 1][i], stmin[j - 1][i + (1 << (j - 1))]);
        }
    }
}

void computeLog(VI& m_log){
    int n = m_log.size();
    m_log[1] = 0;
    REP(i, 2, n) m_log[i] = m_log[i / 2] + 1;
}

int binarySearch(VI& ar, int k, bool isLow){
    int low = 0, high = ar.size() - 1;
    while(low < high){
        int mid = (low + high) / 2;
        if(ar[mid] == k){
            return mid;
        }

        if(ar[mid] < k){
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    if (isLow) {
        if (ar[low] > k && low > 0) return low - 1;
        else return low;
    }
    else {
        if (ar[high] < k && high < ar.size() - 1) return high + 1;
        else return high;
    }
}

int testerSolution(VL& ar, MLI& mll){
    int n = ar.size();

    // precompute the sparse table
    int k = (int) log2(n) + 1;
    VVL stmax(k + 1, VL(n, 0));
    VVL stmin(k + 1, VL(n, 0));
    precompute(ar, stmax, stmin);

    VI m_log(n + 1, 0);
    computeLog(m_log);

    int res = 0;
    queue<pii> q ({make_pair(0, n - 1)});
    while(!q.empty()) {

        pii& lh = q.front(); q.pop();

        int l = lh.first, r = lh.second;

        int range = r - l + 1;
        int j = m_log[range];
        int mr = r - (1 << j) + 1;
        ll minVal = min(stmin[j][l], stmin[j][mr >= l ? mr : l]);
        ll maxVal = max(stmax[j][l], stmax[j][mr >= l ? mr : l]);

        if(minVal == maxVal){
            res++;
            continue;
        }

        res++;

        VI minPos;

        VI& tminPos = mll[minVal];

        int lo = binarySearch(tminPos, l, true);
        int hi = binarySearch(tminPos, r, false);

        for (int i = lo; i <= hi; ++i) {
            if (ar[tminPos[i]] == minVal &&
                tminPos[i] >= l &&
                tminPos[i] <= r)
                minPos.push_back(tminPos[i]);
        }

        int low = l;
        for (int i = 0; i < minPos.size(); ++i) {
            int high = minPos[i] - 1;

            if (high >= low) {
                q.push(make_pair(low, high));
            }

            low = minPos[i] + 1;
        }
        if (r >= low) {
            q.push(make_pair(low, r));
        }
    }

    return res;
}

int main(){
    try {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w+", stdout);

        int n;
        cin >> n;
        MLI mll;
        VL ar(n);
        REP(i, 0, n) {
            ll d;
            cin >> d >> ar[i];
            if (mll.find(ar[i]) == mll.end()) {
                mll[ar[i]] = VI({i});
            } else {
                mll[ar[i]].push_back(i);
            }
        }

        int tres = testerSolution(ar, mll);

        cout << tres << "\n";
    }
    catch(...){
        cout << "Error." << endl;
    }
}
