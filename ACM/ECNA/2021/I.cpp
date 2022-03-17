#include <bits/stdc++.h>

using namespace std;

int n, p, u, pf, sf, ans;
vector<int> p1, u1, p2, u2;
bool in_p[101], in_u[101];

int main() {
    cin >> p >> u;
    ans = n = p + u;
    for(int i = 0, f; i < n; i++) {
        cin >> f;
        if(i < p) {
            p1.push_back(f);
        } else {
            u1.push_back(f);
        }
    }
    cin >> p >> u;
    for(int i = 0, f; i < n; i++) {
        cin >> f;
        if(i < p) {
            p2.push_back(f);
            in_p[f] = true;
        } else {
            u2.push_back(f);
            in_u[f] = true;
        }
    }
    if(!u1.empty()) {
        reverse(u1.begin(), u1.end());
    }
    if(!u2.empty()) {
        reverse(u2.begin(), u2.end());
    }
    for(int i: p1) {
        if(pf < p2.size() && i == p2[pf]) {
            ++pf, --ans;
        } else if(in_p[i]) {
            ++ans;
        }
    }
    for(int i: u1) {
        if(sf < u2.size() && i == u2[sf]) {
            ++sf, --ans;
        } else if(in_u[i]) {
            ++ans;
        }
    }
    cout << ans << endl;
}