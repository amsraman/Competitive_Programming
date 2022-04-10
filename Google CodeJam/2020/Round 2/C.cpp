#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int t, n;
pair<int, int> points[100];

int main() {
    cin >> t;
    for(int _ = 1; _ <= t; _++) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> points[i].f >> points[i].s;
        }
        int ans = 1;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                ll dx = points[j].f - points[i].f, dy = points[j].s - points[i].s;
                map<ll, int> lines;
                for(int k = 0; k < n; k++) {
                    ++lines[dy * points[k].f - dx * points[k].s];
                }
                int odds = 0, single = 0;
                for(auto it: lines) {
                    if(it.s > 1) {
                        odds += it.s % 2;
                    } else {
                        ++single;
                    }
                }
                single += odds % 2;
                ans = max(ans, n - (single - min(2, single)));
            }
        }
        cout << "Case #" << _ << ": " << ans << endl;
    }
}