#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct range {
    int x;
    int s;
} ;

bool comp (const range &a, const range &b) ;

vector<range> graze(100000);

int main(int argc, const char * argv[]) {
    int n, max = 0, cnt = 0;
    cin >> n;
    for (int i = 0; i < n; i ++) {
        int a, b;
        cin >> a >> b;
        graze[n+i].x = a; graze[n+i].s = 1;
        graze[i].x = b; graze[i].s = 0;
    }
    sort (graze.begin(), graze.begin()+2*n, comp);
    for (int i = 0; i <2*n; i ++) {
        //cout << graze[i].x << " " << graze[i].s << endl;
    }
    for (int i = 0; i < 2*n; i ++) {
        if (graze[i].s == 1) cnt ++;
        else cnt --;
        if (cnt > max) max = cnt;
    }
    cout << max;
    return 0;
}

bool comp (const range &a, const range &b) {
    if (a.x == b.x) {
        return a.s > b.s;
    }
    return (a.x < b.x);
}
