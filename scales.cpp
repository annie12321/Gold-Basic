#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
#define N_MAX 1000

int N, C;
int w[N_MAX];
int v[N_MAX];

int my_max=0;

void dfs(int acc) {
    int done = 1;
    for (int i=0;i<N;i++) {
        if (!v[i] && acc+w[i]<=C) {
            done = 0;
            v[i] = 1;
            dfs(acc+w[i]);
            v[i] = 0;
        }
    }
    if (done && acc > my_max) my_max = acc;
}

int main(int argc, const char * argv[]) {
    cin >> N >> C;
    
    for (int i=0;i<N;i++){
        cin >> w[i];
    }
    
    dfs (0);
    cout << my_max;
    return 0;
}
