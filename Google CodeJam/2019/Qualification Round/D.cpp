#include <bits/stdc++.h>

using namespace std;

int t, n, b, f;
string res[5];

int main() {
    cin >> t;
    while(t--) {
        cin >> n >> b >> f;
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < n; j++) {
                cout << (((j & 31) >> i) & 1);
            }
            cout << endl;
            cin >> res[i];
        }
        set<int> ans;
        for(int i = 0; i < n; i++) {
            ans.insert(i);
        }
        int pv = 100;
        for(int i = 0, j = -1; i < n - b; i++) {
            int cur = 0;
            for(int j = 4; j >= 0; j--) {
                cur = (cur << 1) + (res[j][i] - '0');
            }
            if(cur < pv) {
                ++j;
            }
            pv = cur;
            ans.erase(j * 32 + cur);
        }
        for(int i: ans) {
            cout << i << " ";
        }
        cout << endl;
        int res;
        cin >> res;
        assert(res == 1);
    }
}