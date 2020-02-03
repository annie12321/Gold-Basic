#include <iostream>
using namespace std;

int cows[1001];

int main(int argc, const char * argv[]) {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i ++) {
        cows[i] = i;
    }
    for (int i = 0; i < m; i ++) {
        int x, y, temp;
        cin >> x >> y;
        temp = cows[x];
        for (int j = 1; j <= n; j ++) {
            if (cows[j] == temp) cows[j] = cows[y];
        }
    }
    for (int i = 0; i < q; i ++) {
        int x, y;
        cin >> x >> y;
        if (cows[x] == cows[y]) cout << "Y" << endl;
        else cout << "N" << endl;
    }
    return 0;
}



