#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define W_MAX 38
#define H_MAX 100
#define N_MAX (W_MAX+1)*(H_MAX+1)

int debug = 0;
int debug1 = 0;// print v
int debug2 = 0;// print ezf

vector<vector<pair<int,int>>> v(N_MAX); // adjacency list
int e[N_MAX];   // distance
int z[N_MAX];   // visited
int f[N_MAX];   // from which node

int W, H, N;

int get_id (int I, int J) {
    int id;
    if (I==0 || J==0 || I==H+1 || J==W+1)
        id = 0;
    else
        id = I * W + J;
    //if (debug) cout <<"get_id:"<<I<<","<<J<<"->"<<id<<endl;
    return id;
}

void connect(int a, int b) {
    if (debug) cout << "connect "<< a << "<->" << b <<endl;
    v[a].push_back({b,1});
    v[b].push_back({a,1});
}

void print_v () {
    cout << "------------------------------"<<endl;
    cout << "v :" << endl;
    for (int i=0;i<(W+1)*(H+1);i++) {
        if (v[i].size()==0) continue;
        cout << "["<<i<<"] = ";
        for (int j=0;j<v[i].size();j++)
            cout << v[i][j].first << " ";
        cout << endl;
    }
}

void print_ezf (int n) {
    cout << "-------------------------------"<<endl;
    cout << "e: ";
    for (int i=1;i<n;i++)
        if (e[i]==1e9)
            cout << "-1 ";
        else
            cout << e[i] <<" ";
    cout << endl;
    
    cout << "z: ";
    for (int i=1;i<n;i++) cout << z[i] <<" ";
    cout << endl;
    
    cout << "f: ";
    for (int i=1;i<n;i++) cout << f[i] <<" ";
    cout << endl;
    
    cout << "-------------------------------"<<endl;
}

void shortest_path (vector<vector<pair<int,int>>> v, int n, int s) {
    // Dijkstra shortest path from node s, pair {distance, node}
    priority_queue<pair<int,int>> q;
    
    // initialization
    for (int i=1;i<n;i++) {e[i] = 1e9; z[i] = 0; f[n] = -1;}
    e[s] = 0;
    
    q.push({0,s});
    while (!q.empty()) {
        // a is the first/best node in priority queue
        int a = q.top().second; q.pop();
        if (z[a]) continue;
        z[a] = 1;
        
        if (debug2) cout << "get "<<a<<" from priority queue"<<endl;
        
        // go through node a's adj list, b <node, cost>
        for (auto b : v[a]) {
            
            if (debug2) cout << "b = "<<b.first<<","<<b.second<<endl;
            
            // update/relax for newly added node a
            // update distance array if s->a->b is better than s->b, push b into queue
            if ((e[a]+b.second) < e[b.first]) {
                e[b.first] = e[a] + b.second;
                f[b.first] = a;
                q.push({-e[b.first],b.first});
            }
        }
        
        if (debug2) print_ezf(n);
    }
}

int main(int argc, const char * argv[]) {

    cin >> W >> H;
    N = (W+1)*(H+1);
    
    for (int i=0;i<2*H+1;i++) {
        for (int j=0;j<2*W+1;j++) {
            char c;
            scanf("%c", &c);
            while (c!='|' && c!='-' && c!=' ' && c!='+') scanf("%c", &c);
            if (debug) cout << "\ni,j="<<i<<","<<j<<", c="<<c<<endl;
            if ((i%2==0 && j%2==0) || (i%2==1 && j%2==1)) continue;

            if (c=='-' || c=='|') continue;

            if (i%2==0 && j%2==1){
                int I = i/2+1; int J = (j+1)/2;
                connect(get_id(I-1,J), get_id(I,J));
            }
            if (i%2==1 && j%2==0){
                int I = (i+1)/2; int J = j/2+1;
                connect(get_id(I,J-1), get_id(I,J));
            }
            if (debug1) print_v();
        }
    }
    if (debug) {cout << "After inputting all edges"<< endl; print_v(); }
    
    shortest_path(v, N, 0);
    if (debug) print_ezf(N);
    
    int e_max=0;
    for (int i=0;i<N;i++)
        if (e[i]!=1e9 && e[i]>e_max) e_max=e[i];
    
    cout << e_max<<endl;
    return 0;
}

