#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

struct point {
    float x;
    float y;
} ;

float slopes[201][201];
vector<point> points(201);
set<float> s;

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i ++) {
        cin >> points[i].x >> points[i].y;
    }
    for (int i = 0; i < n; i ++) {
        for (int j = i; j < n; j ++) {
            if (points[i].y < points[j].y) {
                slopes[i][j] = ((points[j].y - points[i].y)/(points[j].x - points[i].x));
            }
            if (points[i].y > points[j].y) {
                slopes[i][j] = ((points[i].y - points[j].y)/(points[i].x - points[j].x));
            }
        }
    }
    for (int i = 0; i < n; i ++)
        for (int j = i + 1; j < n; j ++)
            s.insert(slopes[i][j]);
    cout << s.size();
    return 0;
}
