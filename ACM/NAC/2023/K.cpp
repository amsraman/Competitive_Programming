#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    vector<string> line(n);
    vector<int> spc(n, 0), tab(n, 0), dep(n, 0);
    for(int i = 0, cur = 0; i < n; i++) {
        cin >> line[i];
        for(char c: line[i]) {
            if(c == 's') ++spc[i];
            if(c == 't') ++tab[i];
        }
        if(line[i].back() == '{') {
            dep[i] = cur++;
        } else {
            dep[i] = --cur;
        }
    }
    int we_try = 1;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int ns = dep[j] * spc[i] - dep[i] * spc[j], nt = dep[j] * tab[i] - dep[i] * tab[j];
            if(ns == 0 || nt == 0) continue;
            we_try = -ns / nt;
        }
    }
    bool works = true;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int sp1 = spc[i] + we_try * tab[i], sp2 = spc[j] + we_try * tab[j];
            if(dep[j] * sp1 != dep[i] * sp2) works = false;
        }
    }
    cout << (works ? we_try : -1) << '\n';
}