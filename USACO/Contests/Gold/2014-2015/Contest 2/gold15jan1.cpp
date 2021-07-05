#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, max_cows, best_area;
pair<pair<int,int>,char> points[500];
vector<int> y_vals;

int main() {
    ifstream cin("cowrect.in");
    ofstream cout("cowrect.out");
    cin >> n;
    for(int i = 0; i<n; i++) {
        cin >> points[i].f.f >> points[i].f.s >> points[i].s;
        y_vals.push_back(points[i].f.s);
    }
    sort(points,points+n);
    sort(y_vals.begin(),y_vals.end());
    for(int i = 0; i<y_vals.size(); i++) {
        for(int j = i+1; j<y_vals.size(); j++) {
            int rec = -1, cows_seen = 0, ptr = 0;
            vector<pair<pair<int,int>,char>> relevant_points;
            for(int k = 0; k<n; k++) {
                if(points[k].f.s >= y_vals[i] && points[k].f.s <= y_vals[j]) {
                    relevant_points.push_back(points[k]);
                }
            }
            while(ptr < relevant_points.size()) {
                int nxt = relevant_points[ptr].f.f, cows_at_level = 0;
                bool fine = true;
                while(ptr < relevant_points.size() && relevant_points[ptr].f.f == nxt) {
                    if(relevant_points[ptr].f.s >= y_vals[i] && relevant_points[ptr].f.s <= y_vals[j]) {
                        fine &= (relevant_points[ptr].s == 'H');
                        ++cows_at_level;
                    }
                    ++ptr;
                }
                if(fine) {
                    cows_seen += cows_at_level;
                    if(rec == -1) {
                        rec = nxt;
                    }
                    if(cows_seen > max_cows) {
                        max_cows = cows_seen;
                        best_area = (nxt - rec) * (y_vals[j] - y_vals[i]);
                    } else if(cows_seen == max_cows) {
                        best_area = min(best_area,(nxt - rec) * (y_vals[j] - y_vals[i]));
                    }
                } else {
                    rec = -1, cows_seen = 0;
                }
            }
        }
    }
    cout << max_cows << endl << best_area << endl;
}