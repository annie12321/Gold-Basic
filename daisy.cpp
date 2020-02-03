#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int n, c, debug = 0, cnt = 0;
    cin >> n >> c;
    int cows[n+1];
    for (int i =1; i <= n; i ++) {
        cows[i] = i;
    }
    for (int i = 0; i < c; i ++) {
        int a, b;
        cin >> a >> b;
        int temp = cows[a];
        for (int i = 1; i <= n; i ++) {
            if (cows[i] == temp) cows[i] = cows[b];
            if (debug) cout << i << ": " << cows[i] << endl;
        }
        if (debug) cout << endl;
    }
    for (int i = 1; i <= n; i ++) {
        if (cows[i] != cows[1]) {
            cout << i << endl;
            cnt ++;
        }
    }
    if (cnt == 0) cout << "0";
    return 0;
}
