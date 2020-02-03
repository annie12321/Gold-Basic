#include <iostream>
#include <vector>
using namespace std;

vector<long long int> pos(100000);

int main(int argc, const char * argv[]) {
    long int n, t;
    cin >> n >> t;
    int cnt = n;
    for (int i = 0; i < n; i ++) {
        int x, s;
        cin >> x >> s;
        pos[i] = x + s * t;
    }
    for (int i = n - 1; i > 0; i --) {
        if (pos[i] <= pos[i-1]) {
            cnt --;
            pos[i-1] = pos[i];
        }
    }
    cout << cnt;
    return 0;
}
