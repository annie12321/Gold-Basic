#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct see {
    int a;
    int b;
} ;

bool comp (const see &x, const see &y) ;

int main(int argc, const char * argv[]) {
    int n, in, h, r, debug = 0;
    cin >> n >> in >> h >> r;
    int cow[n];
    vector<see> sees(r);
    for (int i = 0; i < n; i ++) {
        cow[i] = h;
    }
    for (int i = 0; i < r; i ++) {
        cin >> sees[i].a >> sees[i].b;
        if (sees[i].a > sees[i].b) {
            int temp = sees[i].a;
            sees[i].a = sees[i].b;
            sees[i].b = temp;
        }
    }
    sort (sees.begin(), sees.end(), comp);
    for (int i = 0; i < r; i ++) {
        if (sees[i].a == sees[i+1].a and sees[i].b == sees[i+1].b) sees[i].a = sees[i].b;
    }
    for (int i = 0; i < r; i ++) {
        if (debug) cout << sees[i].a << " " << sees[i].b << endl;
    }
    for (int i = 0; i < r; i ++) {
        for (int j = sees[i].a + 1; j < sees[i].b; j ++) {
            if (debug) cout << j << " ";
            cow[j - 1]--;
        }
        if (debug) cout << endl;
    }
    for (int i = 0; i < n; i ++) {
        cout << cow[i] << endl;
    }
    return 0;
}

bool comp (const see &x, const see &y) {
    return (x.a > y.a);
}
