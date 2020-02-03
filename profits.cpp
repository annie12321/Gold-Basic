#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int single = -1000, n, sum = 0, maxx = 0;
    cin >> n;
    for (int i = 0; i < n; i ++) {
        int x;
        cin >> x;
        maxx = max (maxx, sum);
        single = max (single, x);
        if (x + sum < 0) sum = 0;
        else sum += x;
    }
    maxx = max (maxx, sum);
    if (maxx == 0) cout << single;
    else cout << maxx;
    return 0;
}
