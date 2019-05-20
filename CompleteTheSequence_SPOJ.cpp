#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits>
#include <random>

#define REP(i, a, b) for(int (i) = (a); (i) < (b); ++(i))
#define REPC(i, a, cond) for(int (i) = (a); (cond); ++(i))
#define assertf(C, M) if(!(C)) { cout << M << endl; assert(C); }

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w+", stdout);

    int t;
    cin >> t;

    REP(caseno, 0, t) {
        int s, c;
        cin >> s >> c;

        VI v(s);
        REP(i, 0, s) {
            cin >> v[i];
        }

        VVI diff;
        diff.push_back(v);
        int level = 0;
        while(true) {
            // check if done
            int el = diff[level][0];
            bool over = true;
            for (int i = 1; i < diff[level].size(); ++i) {
                if (diff[level][i] != el) {
                    over = false;
                    break;
                }
            }
            if (over) break;
            // create one more level
            diff.push_back(VI());
            REP(i, 1, diff[level].size()) {
                diff[level + 1].push_back(diff[level][i] - diff[level][i - 1]);
            }
            level += 1;
        }

        reverse(diff.begin(), diff.end());

        int ee = diff[0][0];
        REP(cc, 0, c) {
            diff[0].push_back(ee);
        }

        REP(level, 1, diff.size()) {
            int sz = diff[level].size();
            REP(cc, 0, c) {
                int e = diff[level - 1][sz - 1 + cc] + diff[level][sz - 1 + cc];
                diff[level].push_back(e);
            }
        }

        REP(i, 0, c) {
            int sz = diff.size();
            cout << diff[sz - 1][s + i] << " ";
        }
        cout << "\n";
    }
}

