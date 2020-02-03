#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int debug = 0;

#define N_MAX 50001
#define B_MAX 25001
#define INF 1e9

vector<vector<pair<int,int>>> G(N_MAX);
vector<pair<int,int>> Q(B_MAX);

int N, M, B;
int dp[N_MAX];

void print_dp () {
    cout << "===========dp============"<<endl;
    for (int i=1;i<=N;i++) {
        if (dp[i]== INF)
            cout << "-1 ";
        else
            cout << dp[i] << "  ";
    }
    cout << endl;
}

void shortest_path(pair<int,int> s) {
    priority_queue<pair<int,int>> q;  // {distance, node}
    q.push(s);
    if (debug) cout << "Push start node {"<<s.first <<","<<s.second<<"} into queue"<<endl;
    
    while (q.size()>0) {
        pair<int,int> u = q.top(); q.pop();
        int dist = u.first;
        int node = u.second;
        if (debug) cout << "Get node {"<<u.first<<","<<u.second<<"} from queue"<<endl;

        for (int i=0;i<G[node].size();i++) {
            if (debug) cout <<i<<endl;
            pair<int,int> v = G[node][i];
            if (dp[v.first] > dp[node] + v.second) {
                dp[v.first] = dp[node] + v.second;
                q.push({-dp[v.first], v.first});
                if (debug) cout << "Push {"<<dp[v.first] << "," << v.first<<"} into queue"<<endl;
                if (debug) print_dp();
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> B;
    
    for (int i=0;i<M;i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].push_back({b,c});
        G[b].push_back({a,c});
    }
    
    for (int i=0;i<B;i++) {
        int a, b;
        cin >> a >> b;
        Q[i] = {a,b};
    }
    
    for (int i=1;i<=N;i++) {
        dp[i]=INF;
    }
    
    dp[1] = 0;
    
    shortest_path({0,1});
    
    if (debug) print_dp();

    
    for (int i=0;i<B;i++) {
        cout << dp[Q[i].first] + dp[Q[i].second]<<endl;
    }
    cout << "Results:"<<endl;
    
    return 0;
}
