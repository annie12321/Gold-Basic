#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
using namespace std;
#define N_MAX 101
#define K_MAX 10001

map <string, pair<int,int>> mymap;

int debug = 0;
int debug1 = 0;

char q[8];

// 'A': exchange the top and bottom row,
// 'B': single right circular shifting of the rectangle,
// 'C': single clockwise rotation of the middle four squares.
//
// Input
// 1 2 3 4
// 8 7 6 5
//
// A:         B:         C:
// 8 7 6 5	   4 1 2 3    1 7 2 4
// 1 2 3 4	   5 8 7 6    8 6 3 5
string A (string in) {
    char out[8];
    out[0] = in[7];
    out[1] = in[6];
    out[2] = in[5];
    out[3] = in[4];
    out[4] = in[3];
    out[5] = in[2];
    out[6] = in[1];
    out[7] = in[0];
    return  out;
}

// A:         B:         C:
// 8 7 6 5	   4 1 2 3    1 7 2 4
// 1 2 3 4	   5 8 7 6    8 6 3 5
string B (string in) {
    char out[8];
    out[0] = in[3];
    out[1] = in[0];
    out[2] = in[1];
    out[3] = in[2];
    out[4] = in[5];
    out[5] = in[6];
    out[6] = in[7];
    out[7] = in[4];
    return out;
}

// A:         B:         C:
// 8 7 6 5	   4 1 2 3    1 7 2 4
// 1 2 3 4	   5 8 7 6    8 6 3 5
string C(string in) {
    char out[8];
    out[0] = in[0];
    out[1] = in[6];
    out[2] = in[1];
    out[3] = in[3];
    out[4] = in[4];
    out[5] = in[2];
    out[6] = in[5];
    out[7] = in[7];
    return out;
}

void print (string x) {
    for (int i=0;i<4;i++) {
        cout << x[i] << " ";
    }
    cout << endl;
    for (int i=7;i>=4;i--) {
        cout << x[i] << " ";
    }
    cout << endl;
}

void print_map () {
    // show content:
    for (map<string,pair<int,int>>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
        std::cout << it->first << " => {" << it->second.first <<","<< it->second.second<< "}\n";
}
void bfs (string q) {
    string s = "12345678";
    string x;
    if (debug1) {
        x = A(q); print(x);
        x = B(q); print(x);
        x = C(q); print(x);
    }
    int done = 0;
    
    queue<string> Q;
    Q.push(s); mymap[s] = {0,0};
    string u, v;
    
    int tmp = 10000;
    
    while (!Q.empty() && !done && tmp >0) {
        if (debug) tmp--;
        u = Q.front(); Q.pop();
        if (u==q) {done=1; v = u; break;}
        if (debug) cout <<"u="<<u<<endl;
        if (debug) print(u);
        
        for (int i = 0; i<3; i++) {
            if (i==0) v = A(u);
            if (i==1) v = B(u);
            if (i==2) v = C(u);
            v.resize(8);
            if (debug) cout <<"i="<<i<<",v="<<v<<endl;
            if (debug) print(v);
            if (v==q) {done = 1; mymap[v] = {mymap[u].first+1, i}; break;}
            if (mymap.find(v) != mymap.end()) {
                if (debug) cout << "Continue" << endl;
                continue;
            } else {
                Q.push(v);
                mymap[v] = {mymap[u].first+1, i};
                if (debug)
                    cout<< "Add mymap[" << v << "]={"<< mymap[v].first<<","<<mymap[v].second<<"}"<<endl;
                if (debug1) print_map();
            }
        }
    }
    cout << mymap[v].first << endl;
    
    if (debug) print_map();
    
    // trace back
    done = 0;
    stack<int> traceback;
    tmp = 10;
    while (!done && tmp>0) {
        if (v==s) {done = 1;break;}
        if (debug) tmp--;
        if (debug) cout << "mymap["<<v<<"]={"<<mymap[v].first<<","<<mymap[v].second<<"}"<<endl;
        int d = mymap[v].second;
        traceback.push(d);
        if (d == 0) {if (debug) print(v); u=A(v);u.resize(8);if (debug) print(u);}
        if (d == 1) {if (debug) print(v); u=B(v);u.resize(8);v=u;u=B(v);u.resize(8);v=u;u=B(v);u.resize(8);if (debug) print(u);}
        if (d == 2) {if (debug) print(v); u=C(v);u.resize(8);v=u;u=C(v);u.resize(8);v=u;u=C(v);u.resize(8);if (debug) print(u);}
        v=u;
    }
    
    while (!traceback.empty()){
        int a = traceback.top(); traceback.pop();
        if (a==0) cout << "A";
        if (a==1) cout << "B";
        if (a==2) cout << "C";
    }
 }

int main(int argc, const char * argv[]) {
    
    for (int i=0;i<8;i++) {
        cin >> q[i];
    }

    cout << "Result: "<<endl;
    bfs(q);
    cout << endl;

    
    return 0;
    
}
