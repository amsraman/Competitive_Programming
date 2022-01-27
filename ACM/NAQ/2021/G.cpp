#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int c, n, err[1000];
vector<pair<int, int>> ve, vc;

void pr(pair<int, int> p) {
    if(p.f == p.s) {
        cout << p.f;
    } else {
        cout << p.f << '-' << p.s;
    }
}

int main() {
    cin >> c >> n;
    set<int> es, cs;
    for(int i = 0; i < c; i++) {
        cs.insert(i + 1);
    }
    for(int i = 0; i < n; i++) {
        cin >> err[i];
        cs.erase(err[i]);
        es.insert(err[i]);
    }
    int bg = -1, pv = - 1;
    for(int i: es) {
        if(i != pv + 1) {
            if(bg != -1) {
                ve.push_back({bg, pv});
            }
            bg = i;
        }
        pv = i;
    }
    ve.push_back({bg, pv});
    bg = pv = -1;
    for(int i: cs) {
        if(i != pv + 1) {
            if(bg != -1) {
                vc.push_back({bg, pv});
            }
            bg = i;
        }
        pv = i;
    }
    vc.push_back({bg, pv});
    cout << "Errors: ";
    if(ve.size() == 1) {
        pr(ve[0]);
    } else {
        for(int i = 0; i < ve.size() - 2; i++) {
            pr(ve[i]);
            cout << ", ";
        }
        pr(ve[ve.size() - 2]);
        cout << " and ";
        pr(ve.back());
    }
    cout << "\nCorrect: ";
    if(vc.size() == 1) {
        pr(vc[0]);
    } else {
        for(int i = 0; i < vc.size() - 2; i++) {
            pr(vc[i]);
            cout << ", ";
        }
        pr(vc[vc.size() - 2]);
        cout << " and ";
        pr(vc.back());
    }
    cout << '\n';
}