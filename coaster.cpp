#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int debug = 0;

#define L_MAX 1001
#define B_MAX 1001
#define N_MAX 10001
#define INF -1

struct component {
    int x;
    int w;
    int f;
    int c;
};

vector<component> C(N_MAX);

bool cmp (component a, component b) {
    return (a.x < b.x);
}

int L, N, B;

int dp[B_MAX][L_MAX];

void print_dp () {
    cout << "===========dp============"<<endl;
    for (int i=0;i<=L;i++) {
        for (int j=0;j<=B;j++) {
            if (dp[i][j]== INF)
                cout << "-1 ";
            else
                cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    cin >> L >> N >> B;
    
    for (int i=1;i<=N;i++) {
        cin >> C[i].x >> C[i].w >> C[i].f >> C[i].c;
    }
    
    sort(C.begin(), C.begin()+N, &cmp);
    
    for (int i=0;i<=L;i++) {
        for (int j=0;j<=B;j++) {
            dp[i][j]=INF;
        }
    }
    
    // L B
    dp[0][0]=0;
    
    int k = 1;
    int k_save = 1;
    
    for (int i=0;i<=L;i++) {
        for (int j=0;j<=B;j++) {
            if (j==0) {
                k=0;
                while (C[k].x<i && k<=N) k++;
                if (C[k].x==i) k_save = k; else continue;
            } else
                k = k_save;
            
            if (debug) cout<<endl<<"i="<<i<<",j="<<j<<endl;
            if (debug) cout<<"k_save="<<k_save<<endl;
            if (dp[i][j]<0) continue;
            while (C[k].x==i && k<=N) {
                if (j+C[k].c<=B && i+C[k].w<=L) {
                    dp[i+C[k].w][j+C[k].c] = max(dp[i+C[k].w][j+C[k].c], dp[i][j] + C[k].f);
                    if (debug)
                        cout << "k="<<k<<"{"<<C[k].x<<","<<C[k].w<<","<<C[k].f<<","<<C[k].c<<"}"<<endl;
                    if (debug)
                        cout << "dp["<<i+C[k].w<<"]["<< j+C[k].c << "]= "<< dp[i][j] + C[k].f<<","<<dp[i+C[k].w][j+C[k].c]<<endl;
                    if (debug) print_dp();
                }
                if (debug) cout<<"k="<<k<<endl;
                
                k++;
            }
            if (debug) print_dp();
        }
    }
    
    int ans=0;
    for (int i=1;i<=B;i++) ans=max(ans,dp[L][i]);
    
    cout <<"Results:";
    if (ans==0) cout << "-1"; else cout << ans;
    
    return 0;
}
