#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t, c, d, x[100], dist[100];
pair<int, int> edges[1000];

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> c >> d;
        vector<pair<int, int>> t1, t2;
        for(int i = 1; i < c; i++) {
            cin >> x[i];
            if(x[i] > 0) {
                t1.push_back({x[i], i});
                dist[i] = x[i];
            } else {
                t2.push_back({-x[i], i});
            }
        }
        for(int i = 0; i < d; i++) {
            cin >> edges[i].f >> edges[i].s;
            --edges[i].f, --edges[i].s;
        }
        sort(t1.begin(), t1.end());
        sort(t2.begin(), t2.end());
        vector<int> vec;
        vec.push_back(0);
        for(int i = 0, j = 0; i < t2.size(); i++) {
            while(vec.size() < t2[i].f) {
                vec.push_back(t1[j].f);
                ++j;
            }
            if(i == 0 || t2[i].f != t2[i - 1].f) {
                dist[t2[i].s] = vec.back() + 1;
            } else {
                dist[t2[i].s] = vec.back();
            }
            vec.push_back(dist[t2[i].s]);
        }
        cout << "Case #" << _ << ": ";
        for(int i = 0; i < d; i++) {
            if(dist[edges[i].f] == dist[edges[i].s]) {
                cout << 1000000 << " ";
            } else {
                cout << abs(dist[edges[i].f] - dist[edges[i].s]) << " ";
            }
        }
        cout << endl;
    }
}