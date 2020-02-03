#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define M_MAX 501
#define N_MAX 501

int debug = 0;
int debug1 = 0;// print dfs
int debug_q = 0;

int v[M_MAX][N_MAX];

int e[M_MAX][N_MAX][2];   // cost - dir up/down
int z[M_MAX][N_MAX][2];   // visited - dir up/down

stack<pair<pair<int,int>,int>> q;

int M, N;
int si=0,sj=0;
int fi=0,fj=0;
/*
 void print_q () {
    long int cnt = q.size();
    cout  << "------------queue (size "<<cnt<<")---------------"<<endl;
    while (cnt>0) {
        int i = q.front().first;
        int j = q.front().second;
        cout << "{"<<i<<","<<j<<"} ";
        q.pop();
        q.push({i,j});
        cnt--;
    }
    cout << endl;
    cout << "---------------------------------------"<<endl;
}
*/

void print_ez (int m, int n) {
    cout << "---------------e0-----------------"<<endl;
    for (int i=1;i<=M;i++) {
        for (int j=1;j<=N;j++) {
            if (e[i][j][0]==1e9)
                cout << "X ";
            else
                cout << e[i][j][0] <<" ";
        }
        cout << endl;
    }
    cout << endl;
/*
    cout << "---------------z0-----------------"<<endl;
    for (int i=1;i<=M;i++) {
        for (int j=1;j<=N;j++) {
            cout << z[i][j][0] <<" ";
        }
        cout << endl;
    }
    cout << endl;
*/
    cout << "---------------e1-----------------"<<endl;
    for (int i=1;i<=M;i++) {
        for (int j=1;j<=N;j++) {
            if (e[i][j][1]==1e9)
                cout << "X ";
            else
                cout << e[i][j][1]<<" ";
        }
        cout << endl;
    }
    cout << endl;
/*
    cout << "---------------z1-----------------"<<endl;
    for (int i=1;i<=M;i++) {
        for (int j=1;j<=N;j++) {
            cout << z[i][j][1] <<" ";
        }
        cout << endl;
    }
    cout << endl;
*/
}

void dfs (int si, int sj, int dir) {
    int done = 0;
    q.push({{si,sj},dir});
    
    int tmp=1000;
    while (!q.empty() && !done && tmp > 0) {
        if (debug) tmp--;
        // a is the first node stack
        int ai = q.top().first.first;
        int aj = q.top().first.second;
        int ad = q.top().second;
        q.pop();
        
        if (debug1) cout << "Pop {"<<ai<<","<<aj<<"} with dir="<<ad<<" from stack"<<endl;
        
        int bi, bj, bd;
        
        // go in the same direction until hitting '#' (v[][]=1)
        bi = ai+(2*ad-1); bj=aj; bd=ad;
        if (bi==fi && bj==fj) {e[bi][bj][bd] = e[ai][aj][ad]; done = 0; continue;}
        if (bi<1|| bi>M || bj<1 || bj>N) {
            if (debug1) cout <<"Out of bound"<<endl;
            continue;  // out of bound
        }
        if (!v[bi][bj]) {   // not '#'
            int new_cost = e[ai][aj][ad];
            if (e[bi][bj][bd]>new_cost) {
                if (debug1) cout <<"Push {"<<bi<<","<<bj<<"} with dir="<<bd<<" to stack"<<endl;
                q.push({{bi,bj},bd});
                e[bi][bj][bd] = new_cost;
            }
        } else {            // is '#', try right/left/flip
            if (debug1) cout<< "Hit #, try right/left/flip"<<endl;
            for (int i=0;i<3;i++) {
                if (i==0) {bi=ai; bj=aj+1; bd=ad; if (debug1) cout <<"right"<<endl;}        // right
                if (i==1) {bi=ai; bj=aj-1; bd=ad; if (debug1) cout <<"left"<<endl;}         // left
                if (i==2) {bi=ai; bj=aj; bd=(ad==0)?1:0;if (debug1) cout <<"flip"<<endl;}   // flip
                
                if (bi==fi && bj==fj) {e[bi][bj][bd] = e[ai][aj][ad]; done=0; continue;}
                if (bi<1|| bi>M || bj<1 || bj>N) {
                    if (debug1) cout <<"Out of bound"<<endl;
                    continue;  // out of bound
                }

                if (!v[bi][bj]) {
                    int new_cost = e[ai][aj][ad] + (i==2);
                    if (e[bi][bj][bd]>new_cost) {
                        if (debug1) cout <<"Push {"<<bi<<","<<bj<<"} with dir="<<bd<<" to stack"<<endl;
                        q.push({{bi,bj},bd});
                        e[bi][bj][bd] = new_cost;
                    }
                }

            }
        }
        
        if (debug1) print_ez(M,N);
        //if (debug1 && debug_q) print_q();
    }
}

int main(int argc, const char * argv[]) {

    
    // inputs
    cin >> M >> N;
    for (int i=1;i<=M;i++) {
        for (int j=1;j<=N;j++) {
            char c;
            cin >> c;
            if (c == 'C') {si=i;sj=j;}  // start
            if (c == 'D') {fi=i;fj=j;}  // finish
            v[i][j] = c == '#';         // blocked
        }
    }
    
    
    // initialization
    for (int i=0;i<=M;i++) {
        for (int j=0;j<=N;j++) {
            e[i][j][0] = 1e9; // cost up
            e[i][j][1] = 1e9; // cost down
            z[i][j][0] = 0;   // visited up
            z[i][j][1] = 0;   // visited down
        }
    }
    e[si][sj][1] = 0;
    if (debug1) print_ez(M,N);
    
    
    dfs(si,sj,1);
    
    //cout << "Result: "<<endl;
    int result =min(e[fi][fj][0], e[fi][fj][1]);
    if (result==1e9)
        cout << "-1" <<endl;
    else
        cout << result<<endl;

    
    return 0;
}

