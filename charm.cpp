#include <iostream>
#include <algorithm>
//#include <set>
#include <vector>
//#include <queue>
//#include <stack>
using namespace std;
#define N_MAX 3402+1
#define M_MAX 12880+1

int debug = 0;
int N, M;
pair<int,int> points[N_MAX];   // w, d
int dp[2][M_MAX];

void print_dp () {
    cout << "==============dp==============="<<endl;
    for (int i=0;i<=1;i++) {
        for (int j=0;j<=M;j++) {
            cout << dp[i][j]<<" ";
        }
        cout << endl;
    }
    cout <<endl;
    
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    
    for (int i=1;i<=N;i++) {
        int w, d;
        cin >> w >> d;
        points[i] = {w,d};
    }
    
    for (int i=1;i<=N;i++) {
        for (int j=1;j<=M;j++) {
            int i_m1 = (i-1)%2;
            int i_m0 = i%2;
            int a = (j<points[i].first) ? 0 : dp[i_m1][j-points[i].first]+points[i].second;
            int b = dp[i_m1][j];
            dp[i_m0][j] = max(a, b);
            if (debug) cout <<"i="<<i<<",j="<<j<<",i_m1="<<i_m1<<endl;
            if (debug) print_dp();
        }
    }
    cout <<"Result:";
    cout << dp[N%2][M] << endl;
    
    return 0;
}
