#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, x1, y1, field[1002][1002], dis[1002][1002], debug = 0, done = 0;

struct bale {
    int x;
    int y;
} ;

struct point {
    int r;
    int c;
} ;

struct dir {
    int i;
    int j;
};

void print_point (char c, point p) {
     cout << c << ":(" << p.r << "," << p.c << ")" << endl;
}

void print_queue (char c, queue<point> q) {
    cout << "queue " << c << " contains (" << q.size() << " points) : "<<endl;
    int qsize = q.size();
    while (qsize != 0) {
        point p = q.front(); 
        print_point ('*', p);
        q.pop();
        q.push(p);
        qsize--;
    }
   cout << endl;
}

void print_dis () {
    cout << "dis[][]="<<endl;
    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            if (dis[i][j]<0) 
                cout << "- ";
            else
                cout << dis[i][j] << " ";
        }
        cout << endl;
    }    
}

int main(int argc, const char * argv[]) {
    
    cin >> n >> x1 >> y1;
    vector<bale> bales(n);
    for (int i = 0; i < 1002; i ++) {
        for (int j = 0; j < 1002; j ++) {
            field[i][j] = 0;
            dis[i][j] = -1;
        }
    }

    int xmax=0,ymax=0;
    for (int i = 0; i < n; i ++) {
        cin >> bales[i].x >> bales[i].y;
        field[bales[i].x][bales[i].y] = 1; 
        if (bales[i].x>xmax) xmax=bales[i].x;
        if (bales[i].y>ymax) ymax=bales[i].y;
    }

    if (debug) {
        for (int i = 0; i <= xmax+1; i ++) {
            for (int j = 0; j <= ymax+1; j ++) {
                cout << field[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    queue<point> q0,q1;
    point s, u, v;
    dir d;
    s = {x1, y1};
    dis[x1][y1] = 0;
    q0.push(s); 
    if (debug) print_queue('0', q0);
    int tmp=10000;
    while (!done && tmp>0) {
        if (debug) tmp--;
        if (q0.size()==0) {
            if (debug) cout << "Move elements from q1 to q0" << endl;
            while (q1.size()!=0) {
               point p = q1.front(); q1.pop();
               q0.push(p);
            }
        }
        if (debug) cout << "=========== in while loop ========: ";
        if (debug) cout << " q0 size =" << q0.size()<< ", q1 size = " << q1.size() << ", done=" << done<<endl;
        u = q0.front(); q0.pop();
        if (debug) print_point('u', u);
        if (debug) print_queue('0', q0);
        if (debug) print_queue('1', q1);
        
        for (int i=0;i<4;i++) {
            if (done) break;
            if (i==0) d = { 1,0};
            if (i==1) d = {-1,0};
            if (i==2) d = {0, 1};
            if (i==3) d = {0,-1};
            
            v.r = u.r+d.i; v.c = u.c+d.j;
            
            if (debug) {
                cout << "try i= " << i<<",";
                print_point('v',v);
            }
            
            if ((v.r==0) && (v.c==0)) done=1;
            
            if ((v.r>xmax+1) || (v.r<0) || (v.c>ymax+1) || (v.c<0 ) ) continue;
            
            if ((dis[v.r][v.c]<0) || (dis[v.r][v.c] > dis[u.r][u.c]+field[v.r][v.c])) // never visited OR find a smaller way 
                dis[v.r][v.c] = dis[u.r][u.c]+field[v.r][v.c];
            else
                continue;
                
            if (field[v.r][v.c]) {
                q1.push(v);
                if (debug) print_point('v',v);
            } else {
                q0.push(v);
                if (debug) print_point('v',v);
            }
            if (debug) print_queue('0', q0);             
            if (debug) print_queue('1', q1);
            if (debug) print_dis();
        }
    }
    if (debug) cout << "DONE!" << endl;
    cout << dis[0][0];
    return 0;
}
