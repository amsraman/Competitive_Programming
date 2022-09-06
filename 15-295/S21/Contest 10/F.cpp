#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int t;
vector<array<int, 5>> states;
map<pair<array<int, 5>, array<int, 5>>, int> deg, position;

int main() {
    for(int i = 0; i <= 8; i++) {
        for(int j = 0; j <= 8 - i; j++) {
            for(int k = 0; k <= 8 - i - j; k++) {
                for(int l = 0; l <= 8 - i - j - k; l++) {
                    states.push_back({i, j, k, l, 8 - i - j - k - l});
                }
            }
        }
    }
    queue<pair<array<int, 5>, array<int, 5>>> q;
    for(array<int, 5> s1: states) {
        q.push({{8, 0, 0, 0, 0}, s1});
        q.push({s1, {8, 0, 0, 0, 0}});
        position[{{8, 0, 0, 0, 0}, s1}] = 2;
        position[{s1, {8, 0, 0, 0, 0}}] = 1;
        for(array<int, 5> s2: states) {
            set<pair<array<int, 5>, array<int, 5>>> nxt;
            for(int i = 1; i < 5; i++) {
                for(int j = 1; j < 5; j++) {
                    if(s1[i] != 0 && s2[j] != 0) {
                        --s1[i], ++s1[(i + j) % 5];
                        nxt.insert({s2, s1});
                        ++s1[i], --s1[(i + j) % 5];
                    }
                }
            }
            deg[{s1, s2}] = nxt.size();
        }
    }
    while(!q.empty()) {
        pair<array<int, 5>, array<int, 5>> tp = q.front(); q.pop();
        set<pair<array<int, 5>, array<int, 5>>> prv;
        for(int i = 1; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                if(tp.f[i] > 0 && tp.s[j] > 0 && i != j) {
                    --tp.s[j], ++tp.s[(j - i + 5) % 5];
                    --deg[{tp.s, tp.f}];
                    if(!position.count({tp.s, tp.f})) {
                        prv.insert({tp.s, tp.f});
                    }
                    ++tp.s[j], --tp.s[(j - i + 5) % 5];
                }
            }
        }
        if(position[tp] == 1) {
            for(auto prv_state: prv) {
                q.push(prv_state);
                position[prv_state] = 2;
            }
        } else {
            for(auto prv_state: prv) {
                if(deg[prv_state] == 0) {
                    q.push(prv_state);
                    position[prv_state] = 1;
                }
            }
        }
    }
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    for(int i = 0, f; i < t; i++) {
        string p1 = "Alice", p2 = "Bob";
        array<int, 5> a_frq = {0, 0, 0, 0, 0}, b_frq = {0, 0, 0, 0, 0};
        cin >> f;
        for(int j = 0, num; j < 8; j++) {
            cin >> num;
            ++a_frq[num];
        }
        for(int j = 0, num; j < 8; j++) {
            cin >> num;
            ++b_frq[num];
        }
        if(f == 1) {
            swap(a_frq, b_frq), swap(p1, p2);
        }
        if(!position.count({a_frq, b_frq})) {
            cout << "Deal\n";
        } else if(position[{a_frq, b_frq}] == 2) {
            cout << p1 << '\n';
        } else {
            cout << p2 << '\n';
        }
    }
}