#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct b {
    long x;
    int s;
    int h;
} ;

bool comp (const b &y, const b &z);

int main(int argc, const char * argv[]) {
    int n, debug = 0;
    unsigned long long product = 0;
    cin >> n;
    vector<b> build(n*2);
    for (int i = 0; i < 2*n; i +=2) {
        cin >> build[i].x >> build[i+1].x >> build[i].h;
        build[i+1].h = build[i].h;
        build[i].s = 1;
        build[i+1].s = 0;
    }
    sort (build.begin(), build.end(), comp);
    for (int i = 0; i < 2*n; i ++) {
        if (debug) cout << build[i].x << " " << build[i].s << " "<< build[i].h << endl;
    }
    multiset<int> heights;
    for (int i = 0; i < 2*n; i ++) {
        if (build[i].s) {
            heights.insert(-1*build[i].h);
            if (debug) cout << "in: " << build[i].h << endl;
        }
        else {
            multiset<int> :: iterator ot = heights.find(-1*build[i].h);
            heights.erase(ot);
            if (debug) cout << "out: " << build[i].h << endl;
        }
        multiset<int> :: iterator it = heights.begin();
        if (heights.size() != 0) product += -1*(*it)*(build[i+1].x - build[i].x);
    }
    cout << product;
    return 0;
}

bool comp (const b &y, const b &z) {
    return (y.x < z.x);
}
