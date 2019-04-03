#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define REP(i, a, b) for (int i = (a); i < (b); ++i)

// represents a point
struct pt {
    double x, y;
};

// compares in such a way that bottom left element is the first element
// and up right element is the last.
bool cmp(pt& a, pt& b){
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

double cross_product(pt& a, pt& b, pt& c){
    // vector ab is:
    // x component - (b.x - a.x)
    // y component - (b.y - a.y)
    // cross product should be negative
    // and cross product is given by: x1 * y2 - x2 * y1.
    return (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
}

// returns true if vector ab x bc is clockwise
// apply right hand thumb rule
bool cw(pt& a, pt& b, pt& c){
    return  cross_product(a, b, c) < 0;
}

bool ccw(pt& a, pt& b, pt& c){
    return cross_product(a, b, c) > 0;
}

// for a given array a, finds the convex hull and
// returns the result in the array a itself.
void convex_hull(vector<pt>& a){
    // if size of a = 1, then return a
    if (a.size() == 1) return;

    // sort the points
    sort(a.begin(), a.end(), cmp);

    vector<pt> up = {a[0]};
    vector<pt> down = {a[0]};

    pt &pt1 = a[0], &pt2 = a.back();

    REP(i, 0, a.size()){
        if(i == a.size() - 1 || cw(pt1, a[i], pt2)){
            while(up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], a[i])){
                up.pop_back();
            }
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(pt1, a[i], pt2)){
            while(down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i])){
                down.pop_back();
            }
            down.push_back(a[i]);
        }
    }


    a.clear();
    REP(i, 0, up.size() - 1){
        a.push_back(up[i]);
    }

    for(int i = down.size() - 1; i > 0; --i){
        a.push_back(down[i]);
    }
}

int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w+", stdout);

    vector<pt> a = {{0, 5}, {1, 4}, {2, 6}, {1, 2}};

    convex_hull(a);

    REP(i, 0, a.size()){
        cout << a[i].x << " " << a[i].y << "\n";
    }
    cout << endl;
}
