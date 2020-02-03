#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;

int debug = 0;
int debug2 = 0;

#define N_MAX 1000001
#define M_MAX 1001
#define R_MAX 1000001
#define INF -1

struct component {
    int start;
    int finish;
    int milk;
};

bool my_cmp (component a, component b) {
    return (a.finish < b.finish);
}

vector<component> C(M_MAX);

int N, M, R;

int dp[M_MAX];

void print_dp () {
    cout << "===========dp============"<<endl;
    for (int i=0;i<M;i++) {
        if (dp[i]== INF)
            cout << "-1 ";
        else
            cout << dp[i] << " ";
    }
    cout << endl;
}

int solve (int a) {
    
    int ans=0;
    for (int i=0;i<M;i++) {
        dp[i] = (C[i].finish<=N) ? C[i].milk : 0;
        for (int j=0;j<i;j++) {
            if (C[j].finish+R<=C[i].start)
                dp[i] = max(dp[i], dp[j]+C[i].milk);
        }
        if (dp[i]>ans) ans =dp[i];
        if (debug2) print_dp();
    }
    
    return ans;
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> R;
    
    for (int i=0;i<M;i++) {
        cin >> C[i].start >> C[i].finish >> C[i].milk;
    }
    sort(C.begin(), C.begin()+M, my_cmp);
    
    if (debug) cout <<C[M-1].start<<" " << C[M-1].finish<<endl;
    
    memset(dp, -1, sizeof(dp));
    
    int ans = solve(M);
    
    cout << "Results:" << ans<< endl;;
    
    return 0;
}
