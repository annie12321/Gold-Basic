#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
#define N_MAX 101
#define K_MAX 10001


int debug = 0;

int N, K;
int q[K_MAX];

int main(int argc, const char * argv[]) {
    cin >> N >> K;
    
    for (int i=0;i<K;i++) {
        cin >> q[i];
    }
    sort(q, q+K);
    
    // find biggest gap
    int biggest_gap=0;
    for (int i=0;i<K-1;i++) {
        if (debug) cout << "q["<<i<<"]="<<q[i]<<endl;
        if (q[i+1]-q[i]>biggest_gap) {
            biggest_gap = q[i+1]-q[i];
            if (debug) cout << biggest_gap << " ";
        }
    }
    
    cout << "Result: ";
    cout << (int) biggest_gap/2<<endl;
    
    return 0;
    
}
