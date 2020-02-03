#include <iostream>
using namespace std;

int n, last, len, slope, reps = 1, maxx;

int main(int argc, const char * argv[]) {
    cin >> n >> last;
    for (int i = 1; i < n; i ++) {
        int x;
        cin >> x;
        if (last == x) {
            slope = 0;
            reps ++;
            len ++;
            if (i == n - 1) len ++;
        }
        else if (last > x) {
            slope = -1;
            len ++;
            reps = 1;
            if (i == n - 1) len ++;
        }
        else {
            if (slope == -1 or slope == 0) {
                len ++;
                maxx = max (len, maxx);
                len = reps;
            }
            else {
                len ++;
                if (i == n - 1) len ++;
            }
            slope = 1;
            reps = 1;
        }
        last = x;
    }
    maxx = max (maxx, len);
    cout << maxx;
    return 0;
}
