#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int debug = 0;
int main(int argc, const char * argv[]) {
    int n, k;
    cin >> n >> k;
    
    vector<set<int>> groups(k);
    for(int i=0;i<k;i++) {
        int g_size;
        cin >> g_size;
        for (int j=0; j<g_size; j++) {
            int cow;
            cin >> cow;
            groups[i].insert(cow);
        }
    }
    if (debug) {
        for(int i=0;i<k;i++) {
            cout << groups[i].size() << " ";
        }
        cout << endl;
    }
    
    int inv_cnt = 1;
    int done = 0;
    for (int i=0; i<k;i++){
        groups[i].erase(1);
    }
    if (debug) {
        for(int i=0;i<k;i++) {
            cout << groups[i].size() << " ";
        }
        cout << endl;
    }
    int tmp=10;
    while (done==0 && tmp>0) {
        if (debug) tmp--;
        int cow=-1;
        done = 1;
        for (int i=0;i<k;i++) {
            if (groups[i].size()==1) {
                set<int>::iterator it = groups[i].begin();
                cow = *it;
                done = 0;
                inv_cnt++;
                break;
            }
        }

        for (int i=0;i<k;i++){
            groups[i].erase(cow);
        }
        if (debug) {
            for(int i=0;i<k;i++) {
                cout << groups[i].size() << " ";
            }
            cout << endl;
        }
        
        if (debug) cout << "done="<<done<<",cow="<< cow<<endl;
    }
    cout << inv_cnt;
    return 0;
}

