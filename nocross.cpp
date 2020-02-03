#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
#define N_MAX 1000

int debug = 0;
int N;
int A[N_MAX];
int B[N_MAX];
int dp[N_MAX][N_MAX];

void print_dp (int N) {
    cout <<"-------------dp-------------"<<endl;
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            cout <<dp[i][j]<<" ";
        }
        cout << endl;
    }
    cout << endl;
}
int check (int a, int b) {
    return (abs(a-b) <= 4);
}
int main(int argc, const char * argv[]) {
    cin >> N;
    
    for (int i=0;i<N;i++) {
        cin >> A[i];
    }
    for (int i=0;i<N;i++) {
        cin >> B[i];
    }
    
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            int a = (j>0) ? dp[i][j-1] : 0;
            int b = (i>0) ? dp[i-1][j] : 0;
            int c = (i>0 && j>0) ? dp[i-1][j-1] + check(A[i],B[j]) : check(A[i],B[j]);
            dp[i][j] = max(c, max(a,b));
            if (debug) cout << "i="<<i<<",j="<<j<<endl;
            if (debug) print_dp(N);
        }
    }

    cout << dp[N-1][N-1];
    
    return 0;
}

