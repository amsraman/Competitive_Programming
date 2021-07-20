#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n;
pair<int,int> p[100];

ll cross(ll a, ll b, ll c, ll d) {
    return a * d - b * c;
}

int main() {
    cin >> n;
    for(int i = 0; i<n; i++) {
        cin >> p[i].f >> p[i].s;
    }
    int ans = 1;
    for(int i = 0; i<n; i++) {
        for(int j = i+1; j<n; j++) {
            int cur = 0;
            for(int k = 0; k<n; k++) {
                if(cross(p[i].f-p[k].f,p[i].s-p[k].s,p[k].f-p[j].f,p[k].s-p[j].s) == 0) {
                    ++cur;
                }
            }
            ans = max(ans,cur);
        }
    }
    cout << ans << endl;
}
