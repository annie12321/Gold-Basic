#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct area {
    int s;
    int e;
} ;

bool comp (const area &a, const area &b);

int main(int argc, const char * argv[]) {
    int n, end = 0, cnt = 0;
    cin >> n;
    vector<area> graze(n);
    for (int i = 0; i < n; i ++) {
        cin >> graze[i].s >> graze[i].e;
    }
    sort (graze.begin(), graze.end(), comp);
    for (int i = 0; i < n; i ++) {
        if (graze[i].s >= end) {
            cnt ++;
            end = graze[i].e;
        }
    }
    cout << cnt;
    return 0;
}

bool comp (const area &a, const area &b) {
    return (a.e < b.e);
}
