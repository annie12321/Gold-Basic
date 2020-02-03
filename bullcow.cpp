#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define N_MAX 1001

int debug = 0;
int dp[N_MAX][N_MAX];
int N, K;

void print_dp (int N) {
    cout <<"-------------dp-------------"<<endl;
    for (int j=0;j<=N;j++) {
        for (int i=0;i<=N;i++){
            cout << dp[i][j]<<" ";
        }
        cout << endl;
    }
}


int main(int argc, const char * argv[]) {
    cin >> N >> K;
    
    dp[1][0] = 1;   // "C"
    dp[1][1] = 1;   // "B"
    
    for (int i=2;i<=N;i++) {
        for (int j=0;j<=i;j++) {
            int a = (j>K+1)? dp[i-1][j-K+1] + dp[i-1][0]: dp[i-1][0];    // add B
            int b = dp[i-1][j];                     // add C
            dp[i][j] = (j==i) ? a + b : b;
            if (debug) cout <<"i="<<i<<",j="<<j<<",a="<<a<<",b="<<b<<endl;
        }
    }
    
    if (debug) print_dp(N);
    
    int sum=0;
    for (int j=0;j<=N;j++) {
        sum = sum+dp[N][j];
    }

    cout << sum<<endl;
    
    return 0;
}

