#include <bits/stdc++.h>

using namespace std;

int n, x[1000], num[2000001];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for(int i = 2; i <= 2e6; i++) {
        if(i & 1) {
            num[i] = num[i - 1] + 1;
        } else {
            num[i] = num[i >> 1] + 1;
        }
    }
    for(int i = n - 1, j = 0; i >= 0; i--) {
        x[i] += j;
        j += num[x[i]];
    }
    for(int i = 0; i < n; i++) {
        vector<int> dig;
        while(x[i] > 0) {
            dig.push_back(x[i] & 1);
            x[i] >>= 1;
        }
        reverse(dig.begin(), dig.end());
        cout << 1;
        for(int j = 1; j < dig.size(); j++) {
            cout << "d+";
            if(dig[j]) {
                cout << "1+";
            }
        }
    }
    cout << '\n';
}