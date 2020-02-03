#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct cow {
    int h;
    int v;
} ;

int main(int argc, const char * argv[]) {
    int n, debug = 0;
    cin >> n;
    int right[n], left[n];
    vector<cow> cows(n);
    for (int i = 0; i < n; i ++) {
        cin >> cows[i].h >> cows[i].v;
        right[i] = 0;
        left[i] = 0;
    }
    for (int i = 0; i < n; i ++) {
        int j = 1;
        if (debug) cout << endl << i << " right: ";
        while (cows[i].h > cows[i+j].h) {
            right[i] += cows[i+j].v;
            if (debug) cout << i + j << " ";
            j ++;
        }
    }
    for (int i = n; i > 0; i --) {
        int j = 1;
        if (debug) cout << endl << i << " left: ";
        while (cows[i].h > cows[i-j].h and i-j>=0) {
            left[i] += cows[i-j].v;
            if (debug) cout << i - j << " ";
            j ++;
        }
    }
    for (int i = 0; i < n; i ++) {
        right[i] += left[i];
    }
    sort (right, right + n);
    cout << right[n-1];
    return 0;
}
