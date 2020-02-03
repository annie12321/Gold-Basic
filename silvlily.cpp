#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define M_MAX 30
#define N_MAX 30

int debug = 1;
int debug1 = 0;// print bfs
int debug2 = 0;// print bfs2
int debug_q = 0;

int dir[8][2] = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};

int v[M_MAX][N_MAX];

int e[M_MAX][N_MAX];    // cost
int u[M_MAX][N_MAX];    // jumps
long long int p[M_MAX][N_MAX];    // no of paths
int z[M_MAX][N_MAX];    // visited

queue<pair<int,int>> q;

int M, N;

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

void print_ez (int m, int n) {
    cout << "---------------e-----------------"<<endl;
    for (int i=0;i<M;i++) {
        for (int j=0;j<N;j++) {
            if (e[i][j]==1e9)
                cout << "X ";
            else
                cout << e[i][j] <<" ";
        }
        cout << endl;
    }
    cout << endl;
    
    cout << "---------------u-----------------"<<endl;
    for (int i=0;i<M;i++) {
        for (int j=0;j<N;j++) {
            if (u[i][j]==1e9)
                cout << "X ";
            else
                cout << u[i][j] <<" ";
        }
        cout << endl;
    }
    cout << endl;
    
    cout << "---------------p-----------------"<<endl;
    for (int i=0;i<M;i++) {
        for (int j=0;j<N;j++) {
            cout << p[i][j] <<" ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "-------------------------------"<<endl;
}

void bfs (int si, int sj) {
    // initialization
    for (int i=0;i<M;i++) {
        for (int j=0;j<N;j++) {
            e[i][j] = 1e9;  // cost
            u[i][j] = 1e9;  // jumps
            //p[i][j] = 0;    // no of paths
        }
    }
    e[si][sj] = 0;
    u[si][sj] = 0;
    //p[si][sj] = 1;
    if (debug1) print_ez(M,N);
    
    q.push({si,sj});
    while (!q.empty()) {
        // a is the first node in priority queue
        int ai = q.front().first;
        int aj = q.front().second;
        q.pop();
        
        if (debug1) cout << "get "<<ai<<","<<aj<<" from queue"<<endl;
        
        // go through node a's adj list, b <node, cost>
        for (int d=0;d<8;d++) {
            
            int bi = ai+dir[d][0];
            int bj = aj+dir[d][1];
            
            if (debug1) cout << "b = "<<bi<<","<<bj;
            
            int cost   = (v[bi][bj]==0);  // need add lilipad
            int rock   = (v[bi][bj]==2);
            int finish = (v[bi][bj]==4);
            
            if (bi<0|| bi>=M || bj<0 || bj>=N) {
                if (debug1) cout << " -- out of bound, skip"<<endl;
                continue;
            }
            
            if (rock) {
                if (debug1) cout << " -- rock, skip"<<endl;
                continue;
            }
            
            // less cost
            if (e[ai][aj]+cost < e[bi][bj]) {
                e[bi][bj] = e[ai][aj]+cost;
                u[bi][bj] = u[ai][aj]+1;
                //p[bi][bj] = p[ai][aj];
                if (!finish) {
                    q.push({bi,bj});
                    if (debug1) cout << " -- less cost, push to queue";
                }
                // same cost
            } else if (e[ai][aj]+cost == e[bi][bj]) {
                // less jumps
                if (u[bi][bj] > u[ai][aj]+1) {
                    u[bi][bj] = u[ai][aj]+1;
                    //p[bi][bj] = p[ai][aj];
                    if (!finish) {
                        q.push({bi,bj});
                        if (debug1) cout << " -- same cost, less jumps, push to queue";
                    }
                }
            }
            
            if (debug1) cout << endl;
        }
        
        if (debug1) print_ez(M,N);
        if (debug1 && debug_q) print_q();
    }
}


// after getting minimun cost/jumps to each nodes, try to get number of paths with minimun cost/jumpps
// need to use visited z[][] to avoid double count
void bfs2 (int si, int sj) {
    // initialization
    for (int i=0;i<M;i++) {
        for (int j=0;j<N;j++) {
            p[i][j] = 0;    // no of paths
            z[i][j] = 0;    // visited
        }
    }
    p[si][sj] = 1;
    if (debug2) print_ez(M,N);
    
    q.push({si,sj});
    while (!q.empty()) {
        // a is the first node in priority queue
        int ai = q.front().first;
        int aj = q.front().second;
        q.pop();
        
        if (debug2) cout << "get "<<ai<<","<<aj<<" from queue"<<endl;
        
        // go through node a's adj list, b <node, cost>
        for (int d=0;d<8;d++) {
            
            int bi = ai+dir[d][0];
            int bj = aj+dir[d][1];
            
            if (debug2) cout << "b = "<<bi<<","<<bj;
            
            int cost   = (v[bi][bj]==0);  // need add lilipad
            int rock   = (v[bi][bj]==2);
            int finish = (v[bi][bj]==4);
            
            if (bi<0|| bi>=M || bj<0 || bj>=N) {
                if (debug2) cout << " -- out of bound, skip"<<endl;
                continue;
            }
            
            if (rock) {
                if (debug2) cout << " -- rock, skip"<<endl;
                continue;
            }
            
            // same cost, same jumps,
            if (e[ai][aj]+cost==e[bi][bj] && u[ai][aj]+1==u[bi][bj]) {
                p[bi][bj] = p[bi][bj] + p[ai][aj];
                if (!finish && !z[bi][bj]) {
                    q.push({bi,bj});
                    z[bi][bj]=1;
                }
            }
            
            if (debug2) cout << endl;
        }
        
        if (debug2) print_ez(M,N);
        if (debug2 && debug_q) print_q();
    }
}

int main(int argc, const char * argv[]) {
    int si=0,sj=0;
    int fi=0,fj=0;
    
    cin >> M >> N;
    //cout << endl<<"M="<<M << " N=" << N <<endl;
    
    for (int i=0;i<M;i++) {
        for (int j=0;j<N;j++) {
            cin >> v[i][j];
            if (v[i][j]==3) {si=i;sj=j;}  // start
            if (v[i][j]==4) {fi=i;fj=j;}  // finish
            //cout << "j="<<j<<endl;
        }
        //cout << "i="<<i<<endl;
    }
    
    bfs(si,sj);
    bfs2(si,sj);
    
    cout << "Result: "<<endl;
    if (e[fi][fj]<1e9) {
        cout << e[fi][fj] <<endl;
        cout << u[fi][fj] <<endl;
        cout << p[fi][fj] <<endl;
    } else
        cout << "-1"<<endl;
    
    return 0;
}

