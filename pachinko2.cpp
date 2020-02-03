#include <iostream>
#include <algorithm>
using namespace std;

int chart[100+1][100+1], val[100+1][100+1];

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    for ( int i = 1; i <= n; i ++) {
        for (int j = 1; j <= i; j ++) {
            cin >> chart[i][j];
        }
    }
    for ( int i = 1; i <= n; i ++) {
        for (int j = 1; j <= i; j ++) {
            if (i == 1) val[i][j] = chart[i][j];
            else if (j == 1) val[i][j] = chart[i][j] + val[i-1][j];
            else val[i][j] = chart[i][j] + max (val[i-1][j], val[i-1][j-1]);
        }
    }
    int x = 0;
    for (int i = 1; i <= n; i ++) {
        x = max (x, val[n][i]);
    }
    cout << x;
    return 0;
}
