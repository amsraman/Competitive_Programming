#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> res; set<int> avail;
        bool pos = true;
        for(int i = 0; i < n - 1; i++) {
            avail.insert(a[i]);
            if(a[i] > a[i + 1]) {
                auto it = avail.lower_bound(a[i + 1]);
                if(it == avail.begin()) {
                    pos = false;
                    break;
                }
                bool fd = false;
                while(!avail.empty()) {
                    int tp = *--avail.end();
                    avail.erase(prev(avail.end()));
                    res.push_back(tp);
                    if(tp < a[i + 1]) {
                        fd = true;
                        break;
                    }
                }
                if(!fd) {
                    pos = false;
                    break;
                }
            }
        }
        avail.insert(a[n - 1]);
        while(!avail.empty()) {
            res.push_back(*--avail.end());
            avail.erase(prev(avail.end()));
        }
        if(!pos) {
            cout << "-1\n";
        } else {
            for(int val: res) {
                cout << val << " ";
            }
            cout << '\n';
        }
    }
}