#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
#define N_MAX 100001
#define K_MAX 21
#define INF -1

int debug = 0;
int N, K;
char a[N_MAX];
int p[K_MAX][N_MAX];
int h[K_MAX][N_MAX];
int s[K_MAX][N_MAX];

// compare bessie against FJ
int cmp(char b, char f) {
    if ((b == 'H') && (f == 'S')) return 1;
    if ((b == 'S') && (f == 'P')) return 1;
    if ((b == 'P') && (f == 'H')) return 1;
    return 0;
}

void print_dp () {
    cout << "===========p============"<<endl;
    for (int i=0;i<=K;i++) {
        for (int j=0;j<=N;j++) {
            if (p[i][j]== INF)
                cout << "INF ";
            else
                cout << p[i][j] << " ";
        }
        cout << endl;
    }
    cout << "===========h============"<<endl;
    for (int i=0;i<=K;i++) {
        for (int j=0;j<=N;j++) {
            if (h[i][j]== INF)
                cout << "INF ";
            else
                cout << h[i][j] << " ";
        }
        cout << endl;
    }
    cout << "===========s============"<<endl;
    for (int i=0;i<=K;i++) {
        for (int j=0;j<=N;j++) {
            if (s[i][j]== INF)
                cout << "INF ";
            else
                cout << s[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> K;
    
    for (int i=1;i<=N;i++) {
        cin >> a[i];
    }
    
    for (int i=0;i<=K;i++) {
        for (int j=0;j<=N;j++) {
            p[i][j]=INF;
            h[i][j]=INF;
            s[i][j]=INF;
        }
    }
    
    // K, N
    p[0][1]=cmp('P',a[1]);
    h[0][1]=cmp('H',a[1]);
    s[0][1]=cmp('S',a[1]);
    
    int curr, from_p, from_h, from_s;
    for (int i=0;i<=K;i++) {
        for (int j=1;j<=N;j++) {
            if (debug) cout << endl << "i="<<i<<",j="<<j<<endl;
            if ((j==1)&&(i==0)) continue;
            // Update P: from P, same i; or from H/S with i-1,
            curr = cmp('P',a[j]);
            from_p = p[i][j-1]   + curr;
            from_h = (i>1) ? h[i-1][j-1] + curr : -1;
            from_s = (i>1) ? s[i-1][j-1] + curr : -1;
            p[i][j] = max(max(from_p, from_h), from_s);
            // Update H: from H, same i; or from P/S with i-1,
            curr = cmp('H',a[j]);
            from_p = (i>0) ? p[i-1][j-1] + curr : -1;
            from_h = h[i][j-1]   + curr;
            from_s = (i>0) ? s[i-1][j-1] + curr : -1;
            h[i][j] = max(max(from_p, from_h), from_s);
            // Update S: from H, same i; or from P/H with i-1,
            curr = cmp('S',a[j]);
            from_p = (i>0) ? p[i-1][j-1] + curr : -1;
            from_h = (i>0) ? h[i-1][j-1] + curr : -1;
            from_s = s[i][j-1]   + curr;
            s[i][j] = max(max(from_p, from_h), from_s);
            if (debug) print_dp();
        }
    }
    cout << max(max(p[K][N], h[K][N]), s[K][N]);
    
    return 0;
}
