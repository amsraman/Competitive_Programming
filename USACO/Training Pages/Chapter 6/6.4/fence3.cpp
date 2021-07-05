/*
ID: adisund1
TASK: fence3
LANG: C++
*/
#include <bits/stdc++.h>
#define f first
#define s second
#define epsilon 1e-5

using namespace std;

int f;
double best_x, best_y;
vector<pair<int,pair<int,int>>> x_lines, y_lines;

double cost(double x, double y) {
    double dist = 0;
    for(auto l: x_lines) {
        if(x < l.s.f) {
            dist += sqrt((x - l.s.f) * (x - l.s.f) + (y - l.f) * (y - l.f));
        } else if(x > l.s.s) {
            dist += sqrt((x - l.s.s) * (x - l.s.s) + (y - l.f) * (y - l.f));
        } else {
            dist += abs(y - l.f);
        }
    }
    for(auto l: y_lines) {
        if(y < l.s.f) {
            dist += sqrt((x - l.f) * (x - l.f) + (y - l.s.f) * (y - l.s.f));
        } else if(y > l.s.s) {
            dist += sqrt((x - l.f) * (x - l.f) + (y - l.s.s) * (y - l.s.s));
        } else {
            dist += abs(x - l.f);
        }
    }
    return dist;
}

double best_cost(double x_val) {
    double lb = 0, ub = 100;
    while(ub - lb > epsilon) {
        double mid1 = lb + (ub - lb)/3;
        double mid2 = ub - (ub - lb)/3;
        if(cost(x_val,mid1) > cost(x_val,mid2)) {
            lb = mid1;
        } else {
            ub = mid2;
        }
    }
    return cost(x_val,ub);
}

int main() {
    ifstream cin("fence3.in");
    ofstream cout("fence3.out");
    cin >> f;
    for(int i = 0, sx, sy, ex, ey; i<f; i++) {
        cin >> sx >> sy >> ex >> ey;
        if(sy == ey) {
            x_lines.push_back({sy,{min(sx,ex),max(sx,ex)}});
        } else {
            y_lines.push_back({sx,{min(sy,ey),max(sy,ey)}});
        }
        double lb = 0, ub = 100;
        while(ub - lb > epsilon) {
            double mid1 = lb + (ub - lb)/3;
            double mid2 = ub - (ub - lb)/3;
            if(best_cost(mid1) > best_cost(mid2)) {
                lb  = mid1;
            } else {
                ub = mid2;
            }
        }
        best_x = ub, lb = 0, ub = 100;
        while(ub - lb > epsilon) {
            double mid1 = lb + (ub - lb)/3;
            double mid2 = ub - (ub - lb)/3;
            if(cost(best_x,mid1) > cost(best_x,mid2)) {
                lb = mid1;
            } else {
                ub = mid2;
            }
        }
        best_y = ub;
    }
    cout << fixed << setprecision(1) << best_x << " " << best_y << " " << cost(best_x,best_y) << endl;
}