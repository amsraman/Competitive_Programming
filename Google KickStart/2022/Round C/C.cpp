#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    int t;
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int n, l;
        cin >> n >> l;
        vector<int> p(n), d(n);
        deque<pair<int, int>> ord;
        vector<vector<int>> pos(2);
        for(int i = 0; i < n; i++) {
            cin >> p[i] >> d[i];
            pos[d[i]].push_back(p[i]);
            ord.push_back({p[i], i});
        }
        sort(ord.begin(), ord.end());
        for(int i = 0; i < 2; i++) {
            if(!pos[i].empty()) {
                sort(pos[i].begin(), pos[i].end());
                if(i & 1 ^ 1) {
                    reverse(pos[i].begin(), pos[i].end());
                }
            }
        }
        cout << "Case #" << _ << ": ";
        for(int i = 0; i < n; i++) {
            int res1 = (pos[0].empty() ? INF : pos[0].back());
            int res2 = (pos[1].empty() ? INF : l - pos[1].back());
            if(res1 > res2) {
                cout << ord.back().s + 1 << " ";
                pos[1].pop_back(), ord.pop_back();
            } else if(res2 > res1) {
                cout << ord.front().s + 1 << " ";
                pos[0].pop_back(), ord.pop_front();
            } else {
                int m1 = ord.front().s, m2 = ord.back().s;
                pos[0].pop_back(), pos[1].pop_back();
                ord.pop_front(), ord.pop_back();
                if(m1 > m2) {
                    swap(m1, m2);
                }
                cout << m1 + 1 << " " << m2 + 1 << " ";
                i++;
            }
        }
        cout << endl;
    }
}