/*
ID: adisund1
TASK: fence4
LANG: C++
*/
#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n;
pair<double,int> ang[200];
set<pair<int,int>> edges_seen;
bool isPoly = true;

struct Point {
    ll x_val, y_val;
    Point operator+(Point &P) {
        return {x_val + P.x_val, y_val + P.y_val};
    }
    Point operator-(Point &P) {
        return {x_val - P.x_val, y_val - P.y_val};
    }
    double norm() {
        return sqrt((double)x_val * x_val + (double)y_val * y_val);
    }
    ll inner(const Point &P) {
        return x_val * P.x_val + y_val * P.y_val;
    }
    ll cross(const Point &P) {
        return x_val * P.y_val - y_val * P.x_val;
    }
    int turn(const Point &P) {
        if(x_val * P.y_val > y_val * P.x_val) {
            return 1;
        } else if(x_val * P.y_val == y_val * P.x_val) {
            return 0;
        } else {
            return -1;
        }
    }
} vertices[300], observer;

struct LineSegment {
    Point P1, P2;
    bool intersects(LineSegment &L) {
        bool s1 = (L.P1 - P1).turn(P2 - L.P1) != (L.P2 - P1).turn(P2 - L.P2);
        bool s2 = (P1 - L.P1).turn(L.P2 - P1) != (P2 - L.P1).turn(L.P2 - P2);
        if((L.P1 - P1).turn(P2 - L.P1) == 0 && (P1 - L.P1).turn(L.P2 - P1) == 0) {
            int x11 = min(P1.x_val,P2.x_val);
            int x12 = max(P1.x_val,P2.x_val);
            int x21 = min(L.P1.x_val,L.P2.x_val);
            int x22 = max(L.P1.x_val,L.P2.x_val);
            s1 &= (x12 >= x21 && x22 >= x11);
        }
        return s1 && s2;
    }
} edges[300];

int main() {
    ifstream cin("fence4.in");
    ofstream cout("fence4.out");
    cin >> n >> observer.x_val >> observer.y_val;
    for(int i = 0; i<n; i++) {
        cin >> vertices[i].x_val >> vertices[i].y_val;
    }
    for(int i = 0; i<n; i++) {
        edges[i] = {vertices[i],vertices[(i+1)%n]};
        ang[i] = {atan2(vertices[i].y_val - observer.y_val, vertices[i].x_val - observer.x_val),i};
    }
    for(int i = 0; i<n; i++) {
        for(int j = i+2; j<n && (j+1)%n != i; j++) {
            isPoly &= !edges[i].intersects(edges[j]);
        }
    }
    sort(ang,ang+n);
    for(int i = 0; i<n; i++) {
        Point vertex1 = vertices[ang[i].s], vertex2 = vertices[ang[(i+1)%n].s];
        if((vertex1 - observer).cross(vertex2 - observer) == 0) {
            continue;
        }
        Point ray_dir = (vertex1 + vertex2 - observer) - observer, ortho = {-ray_dir.y_val, ray_dir.x_val};
        int mx = -1;
        double best_dist = 1000;
        for(int j = 0; j<n; j++) {
            if((edges[j].P2 - edges[j].P1).inner(ortho) != 0) {
                double t1 = (double) (edges[j].P2 - edges[j].P1).cross(observer - edges[j].P1) / (edges[j].P2 - edges[j].P1).inner(ortho);
                double t2 = (double) (observer - edges[j].P1).inner(ortho) / (edges[j].P2 - edges[j].P1).inner(ortho);
                if(t1 < 0 || t2 < 0 || t2 > 1) {
                    continue;
                }
                double dist = ray_dir.norm() * t1;
                if(dist < best_dist) {
                    best_dist = dist;
                    mx = j;
                }
            }
        }
        if(mx != -1) {
           edges_seen.insert({max(mx,(mx+1)%n),min(mx,(mx+1)%n)});
        }
    }
    if(isPoly) {
        cout << edges_seen.size() << endl;
        for(pair<int,int> i: edges_seen) {
            cout << vertices[i.s].x_val << " " << vertices[i.s].y_val << " " << vertices[i.f].x_val << " " << vertices[i.f].y_val << endl;
        }
    } else {
        cout << "NOFENCE" << endl;
    }
}