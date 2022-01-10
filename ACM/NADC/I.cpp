#include <bits/stdc++.h>

using namespace std;

int n, num;
set<array<int, 3>> times;

void mod(string s, vector<int> & v, int id) {
    if(s == "*") {
        int ub = (id == 0 ? 24 : 60);
        for(int i = 0; i < ub; i++) {
            v.push_back(i);
        }
        return;
    }
    int dash = -1;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == '-') {
            dash = i;
        }
    }
    if(dash != -1) {
        string s1 = s.substr(0, dash), s2 = s.substr(dash + 1, s.length() - dash);
        int lb = atoi(s1.c_str()), ub = atoi(s2.c_str());
        for(int i = lb; i <= ub; i++) {
            v.push_back(i);
        }
        return;
    }
    v.push_back(atoi(s.c_str()));
}

void proc(string s, vector<int> & v, int id) {
    vector<int> commas;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == ',') {
            commas.push_back(i);
        }
    }
    commas.push_back(s.length());
    int cur = 0;
    for(int i = 0; i < commas.size(); i++) {
        mod(s.substr(cur, commas[i] - cur), v, id);
        cur = commas[i] + 1;
    }
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        string hrs, mins, secs;
        vector<int> vh, vm, vs;
        cin >> hrs >> mins >> secs;
        proc(hrs, vh, 0);
        proc(mins, vm, 1);
        proc(secs, vs, 2);
        for(int h: vh) {
            for(int m: vm) {
                for(int s: vs) {
                    times.insert({h, m, s});
                    ++num;
                }
            }
        }
    }
    cout << times.size() << " " << num << endl;
}