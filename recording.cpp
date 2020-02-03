#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int debug = 0;

#define N_MAX 151
#define INF -1

struct component {
    int x;
    int y;
};

vector<component> C(N_MAX);

bool cmp (component a, component b) {
    return (a.y < b.y);
}

int L, N, B;

int dp[N_MAX][N_MAX];

void print_dp () {
    cout << "===========dp============"<<endl;
    for (int i=0;i<=N;i++) {
        for (int j=0;j<=N;j++) {
            if (dp[i][j]== INF)
                cout << "-1 ";
            else
                cout << dp[i][j] << "  ";
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    
    for (int i=0;i<N;i++) {
        cin >> C[i].x >> C[i].y;
    }
    
    sort(C.begin(), C.begin()+N, &cmp);
    
    // last two: i-1, i
    for (int i=0;i<=N;i++) {
        for (int j=0;j<=N;j++) {
            if (i==0) dp[i][j] = 1;
            else if (i==1 && j>1) dp[i][j] = 2;
            else dp[i][j]= INF;
        }
    }
    
    for (int i=1;i<=N;i++) {
        for (int j=1;j<=N;j++) {
            if (debug) cout<<endl<<"i="<<i<<",j="<<j<<endl;
            if (dp[i][j]==INF) continue;
            for (int k=1;k<=N;k++) {
                if (k==i || k==j) continue;
                if (C[k-1].x>=C[i-1].y) {
                    if (C[k-1].y < C[j-1].y)
                        dp[k][j]=max(dp[k][j], dp[i][j]+1);
                    else
                        dp[j][k]=max(dp[j][k], dp[i][j]+1);
                }
            }
            if (debug) print_dp();
        }
    }
    
    int ans=0;
    for (int i=1;i<=N;i++)
        for (int j=1;j<=N;j++)
            ans=max(ans,dp[i][j]);
    cout << "Results:"<<ans<<endl;
    
    return 0;
}
