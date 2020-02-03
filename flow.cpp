#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define N_MAX 60

int debug = 0;
int debug2 = 0; // in function
int debug3 = 0; // delete, min flow
int debug4 = 0; // merge, add flow
int debug5 = 0; // clean up node w/o next

vector<vector<pair<int,int>>> v(N_MAX); // next, pair <node, seg cost>
vector<vector<pair<int,int>>> p(N_MAX); // previous

int get_id (char c) {
    int id;
    if ((c >='A') && (c <= 'Z')) id = c - 'A';
    else id = c - 'a' + 26;
    if (debug2) cout << "get_id:" << c << "->" << id << endl;
    return id;
}

char get_name (int id) {
    char name;
    if (id < 26) name = 'A' + id;
    else name = 'a' + (id-26);
    if (debug2) cout << "get_name:" << id << "->" << name << endl;
    return name;
}

void print_p () {
    cout << "------------------------------"<<endl;
    cout << "p (previous):" << endl;
    for (int i=0;i<52;i++) {
        if (p[i].size()==0) continue;
        cout << "["<<get_name(i)<<"] = ";
        for (int j=0;j<p[i].size();j++)
            cout << "{" << get_name(p[i][j].first) << ","<<p[i][j].second << "}";
        cout << endl;
    }
    cout << "------------------------------"<<endl;
}
void print_v () {
    cout << "------------------------------"<<endl;
    cout << "v (next):" << endl;
    for (int i=0;i<52;i++) {
        if (v[i].size()==0) continue;
        cout << "["<<get_name(i)<<"] = ";
        for (int j=0;j<v[i].size();j++)
            cout << "{" << get_name(v[i][j].first) << ","<<v[i][j].second << "}";
        cout << endl;
    }
}

int main(int argc, const char * argv[]) {
    int k;  // k pipes
    cin >> k;
    
    for (int i=0;i<k;i++) {
        char a, b;
        int h;
        cin >> a >> b >> h;
        int aid = get_id(a);
        int bid = get_id(b);
        v[aid].push_back(make_pair(bid,h)); // next, pair {node, distance}
        p[bid].push_back(make_pair(aid,h)); // prev
    }
    if (debug) {cout << "After inputting all edges"<< endl; print_v(); print_p();}
    
    int tmp = 10;
    while (v[get_id('A')][0].first != get_id('Z') || v[0].size() != 1 ) {
        if (debug) {if (tmp-- == 0) {cout << "Timed out !!! "<< endl; break;}}
        
        for (int i=0;i<52;i++) {
            if (v[i].size()==0 && p[i].size()>0 && i!=get_id('Z')) {   // node with no next
                if (debug) cout << "Clean up node"<<get_name(i)<<endl;
                for (int j=0; j<p[i].size();j++) {
                    int prev_node = p[i][j].first;
                    p[i][j].second=0;
                    for (int k=0; k<v[prev_node].size();k++) {
                        if (v[prev_node][k].first==i)
                            v[prev_node][k].second = 0;
                    }
                }
            }
        }
        
        if (debug5) {cout << "After cleanning up all edges"<< endl; print_v(); print_p();}
        
        for (int i=0;i<52;i++) {
            // search for node with one prev and one next
            if ((v[i].size()==1) && (p[i].size()==1)) {
                if (debug) cout << "Delete node " << get_name(i)<< endl;
                
                // merge/delete this node (min flow)
                int prev_node = p[i].begin()->first;
                for (int j=0; j<v[prev_node].size(); j++)
                    if (v[prev_node][j].first == i) {
                        v[prev_node][j].first  = v[i].begin()->first;
                        v[prev_node][j].second = min(v[i].begin()->second, v[prev_node][j].second);
                    }
                
                int next_node = v[i].begin()->first;
                for (int j=0; j<p[next_node].size(); j++)
                    if (p[next_node][j].first == i) {
                        p[next_node][j].first  = p[i].begin()->first;
                        p[next_node][j].second = min(p[i].begin()->second,p[next_node][j].second);
                    }
                
                v[i].erase(v[i].begin());
                p[i].erase(p[i].begin());
                if (debug3) {cout << "After deleting nodes"<< endl; print_v(); print_p();}
            }
        }
        
        // merge parallel connection, add flow
        for (int i=0; i<52;i++) {
            if (v[i].size()>0) {
                for (int j=0; j<v[i].size();j++) {
                    if (v[i][j].second>0) {
                        for (int k=j+1; k<v[i].size();k++) {
                            if (v[i][k].first == v[i][j].first) {
                                if (debug) cout << "v["<<get_name(i)<<"]: merge "<<get_name(v[i][j].first)<< " ("<<v[i][j].second<< "+"<<v[i][k].second<<")"<<endl;
                                v[i][j].second = v[i][j].second + v[i][k].second;
                                v[i][k].second = 0;
                            }
                        }
                    }
                }
                for (int j=0; j<v[i].size();) {
                    if (v[i][j].second == 0) {
                        v[i].erase(v[i].begin()+j);
                        if (debug) cout << "v["<<get_name(i)<<"]: remove " <<get_name(v[i][j].first)<<endl;
                    } else {
                        j++;
                    }
                }
                if (debug4) print_v();
            }
        }
        for (int i=0; i<52;i++) {
            if (p[i].size()>0) {
                for (int j=0; j<p[i].size();j++) {
                    if (p[i][j].second>0) {
                        for (int k=j+1; k<p[i].size();k++) {
                            if (p[i][k].first == p[i][j].first) {
                                if (debug) cout << "p["<<get_name(i)<<"]: merge "<<get_name(p[i][j].first)<< " ("<<p[i][j].second<< "+"<<p[i][k].second<<")"<<endl;
                                p[i][j].second = p[i][j].second + p[i][k].second;
                                p[i][k].second = 0;
                            }
                        }
                    }
                }
                for (int j=0; j<p[i].size();) {
                    if (p[i][j].second == 0) {
                        if (debug) cout << "p["<<get_name(i)<<"]: remove " <<get_name(p[i][j].first)<<endl;
                        p[i].erase(p[i].begin()+j);
                    } else {
                        j++;
                    }
                }
                if (debug4) print_p();
            }
        }
        if (debug) {cout << "After merging"<< endl; print_v(); print_p();}
    }
    
    cout << v[0][0].second;
    
    return 0;
}

