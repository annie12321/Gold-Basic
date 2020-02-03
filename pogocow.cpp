#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
#define N_MAX 1001

int debug = 0;
int N;
vector<pair<int,int>> points;
int dp[N_MAX][N_MAX];


vector<pair<int,int>> points2;
int dp2[N_MAX][N_MAX];

int dist (int i, int j) {
    if (i==0)
        return 0;
    else
        return abs(points[j-1].first-points[i-1].first);
}

int dist2 (int i, int j) {
    if (i==0)
        return 0;
    else
        return abs(points2[j-1].first-points2[i-1].first);
}

void print_dp () {
    cout << "==============dp==============="<<endl;
    for (int i=0;i<N;i++) {
        for (int j=0;j<=N;j++) {
            cout << dp[i][j]<<" ";
        }
        cout << endl;
    }
    cout <<endl;
    
}

void print_dp2 () {
    cout << "==============dp2==============="<<endl;
    for (int i=0;i<N;i++) {
        for (int j=0;j<=N;j++) {
            cout << dp2[i][j]<<" ";
        }
        cout << endl;
    }
    cout <<endl;
    
}
int main(int argc, const char * argv[]) {
    cin >> N;
    
    for (int i=0;i<N;i++) {
        int x, p;
        cin >> x >> p;
        points.push_back({x,p});
        points2.push_back({-x,p});
    }
    
    //-----------round 1
    sort(points.begin(), points.begin()+N);
    
    for (int i=0;i<N;i++) {
        for (int j=i+1;j<=N;j++) {
            if (i==0)
                dp[i][j] = points[j-1].second;
            else {
                for (int k=0;k<i;k++) {
                    if (debug) cout <<"k="<<k<<":"<<dist(k,i)<<","<<dist(i,j)<<",dp[k][i]="<<dp[k][i]<<endl;
                    if (dist(k,i)<=dist(i,j))
                        dp[i][j]=max(dp[i][j],dp[k][i]+points[j-1].second);
                }
            }
            if (debug) cout <<"i="<<i<<",j="<<j<<endl;
            if (debug) print_dp();
        }
    }
    
    int m = 0;
    for (int i=0;i<N;i++) {
        for (int j=i+1;j<=N;j++) {
            m = max(m,dp[i][j]);
        }
    }

    //-----------round 2
    sort(points2.begin(), points2.begin()+N);
    
    for (int i=0;i<N;i++) {
        for (int j=i+1;j<=N;j++) {
            if (i==0)
                dp2[i][j] = points2[j-1].second;
            else {
                for (int k=0;k<i;k++) {
                    if (debug) cout <<"k="<<k<<":"<<dist2(k,i)<<","<<dist2(i,j)<<",dp2[k][i]="<<dp2[k][i]<<endl;
                    if (dist2(k,i)<=dist2(i,j))
                        dp2[i][j]=max(dp2[i][j],dp2[k][i]+points2[j-1].second);
                }
            }
            if (debug) cout <<"i="<<i<<",j="<<j<<endl;
            if (debug) print_dp2();
        }
    }

    int m2 = 0;
    for (int i=0;i<N;i++) {
        for (int j=i+1;j<=N;j++) {
            m2 = max(m2,dp2[i][j]);
        }
    }

    cout << max(m,m2) << endl;
    
    return 0;
}
