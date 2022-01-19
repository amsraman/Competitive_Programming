#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, num[3], tp[3];
string s;
vector<pair<int, int>> seq;
bool done[200000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> s;
    for(char c: s) {
        ++num[c - 'A'];
    }
    tp[0] = (num[0] + num[1] - num[2]) / 2;
    tp[1] = (num[0] - num[1] + num[2]) / 2;
    tp[2] = (-num[0] + num[1] + num[2]) / 2;
    stack<int> st;
    queue<int> q;
    for(int i = 0; i < 2 * n; i++) {
        if(s[i] == 'C') {
            q.push(i);
        }
    }
    for(int i = 0, j = 0; i < 2 * n; i++) {
        if(s[i] == 'B') {
            if(j < tp[2]) {
                if(!q.empty()) {
                    int pv = q.front();
                    q.pop();
                    seq.push_back({i, pv});
                    done[i] = done[pv] = true;
                }
            } else if(!st.empty()) {
                int pv = st.top();
                st.pop();
                seq.push_back({pv, i});
                done[i] = done[pv] = true;
            }
            ++j;
        } else if(s[i] == 'A') {
            st.push(i);
        }
        if(i == q.front()) {
            q.pop();
        }
    }
    vector<int> vec1, vec2;
    for(int i = 0; i < 2 * n; i++) {
        if(!done[i] && s[i] == 'A') {
            vec1.push_back(i);
        }
        if(!done[i] && s[i] == 'C') {
            vec2.push_back(i);
        }
    }
    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());
    int sz = min(vec1.size(), vec2.size());
    for(int i = 0; i < sz; i++) {
        if(vec1[i] < vec2[i]) {
            seq.push_back({vec1[i], vec2[i]});
        }
    }
    if(seq.size() == n) {
        cout << "YES\n";
        for(pair<int, int> s: seq) {
            cout << s.f + 1 << " " << s.s + 1 << '\n';
        }
    } else {
        cout << "NO\n";
    }
}