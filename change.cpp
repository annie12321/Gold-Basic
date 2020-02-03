#include <iostream>
#include <algorithm>
using namespace std;

bool comp (int a, int b);

int main(int argc, const char * argv[]) {
    int t, n, cnt = 0;
    cin >> t >> n;
    int c[n+1];
    for (int i = 0; i < n; i ++) {
        cin >> c[i];
    }
    sort (c, c+n, comp);
    for (int i = 0; i < n; i ++) {
        cnt += t / c[i];
        t = t % c[i];
        if (t == 0) {
            cout << cnt;
            return 0;
        }
    }
    return 0;
}

bool comp (int a, int b) {
    return (a > b);
}
