#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
#define H_MAX 1001
#define G_MAX 1001
#define INF 1000000000

int debug = 0;
int H, G;
pair<int, int> h[H_MAX];
pair<int, int> g[G_MAX];
int dph[H_MAX][G_MAX];  // last visited H
int dpg[H_MAX][G_MAX];  // last visited G

int dist(pair<int,int> a, pair<int,int> b) {
    int ans =(a.first-b.first)*(a.first-b.first) + (a.second - b.second)*(a.second - b.second);
    //if (debug) cout <<a.first<<","<<a.second<<" "<<b.first<<","<<b.second<<"->"<<ans<<endl;
    return (ans);
}

void print_dp () {
    cout << "===========dph============"<<endl;
    for (int i=0;i<=H;i++) {
        for (int j=0;j<=G;j++) {
            if (dph[i][j]== INF)
                cout << "INF ";
            else
                cout << dph[i][j] << " ";
        }
        cout << endl;
    }
    cout << "===========dpg============"<<endl;
    for (int i=0;i<=H;i++) {
        for (int j=0;j<=G;j++) {
            if (dpg[i][j]== INF)
                cout << "INF ";
            else
                cout << dpg[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    cin >> H >> G;
    
    for (int i=1;i<=H;i++) {
        cin >> h[i].first >> h[i].second;
    }
    for (int i=1;i<=G;i++) {
        cin >> g[i].first >> g[i].second;
    }
    
    for (int i=0;i<=H;i++) {
        for (int j=0;j<=G;j++) {
            dpg[i][j]=INF;
            dph[i][j]=INF;
        }
    }
    
 
    dph[0][0]=0;
    dpg[0][0]=0;
    dph[1][0]=0;// dist({0,0}, h[1]);
    dpg[1][0]=INF;
    
    for (int i=1;i<=H;i++) {
        for (int j=0;j<=G;j++) {
            if ((i==1)&&(j==0)) continue;
            if (i>1) {
                // To H[i], either from <H[i-1],dph[i-1][j] or <G[j],dpg[i-1][j]>
                dph[i][j] = min(dph[i-1][j] + dist(h[i-1],h[i]), dpg[i-1][j] + dist(g[j],h[i]));
            }
            
            if (j>0) {
                // To G[j], either from <G[j-1],dpg[i][j-1] or <H[i-1],dph[i-1][j]>
                dpg[i][j] = min(dpg[i][j-1] + dist(g[j-1],g[j]), dph[i][j-1] + dist(h[i],g[j]));
            }
            
            if (debug) cout << endl << "i="<<i<<",j="<<j<<endl;
            if (debug) print_dp();
        }
    }
    cout << dph[H][G];
    
    return 0;
}
