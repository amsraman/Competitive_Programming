#include <bits/stdc++.h>

using namespace std;

string ai, phone;

int main() {
    cin >> ai >> phone;
    int n = ai.length(), m = phone.length(), ans = 0;
    for(int i = 0; i + m <= n; i++) {
        bool match = true;
        for(int j = 0; j < m; j++) {
            match &= (ai[i + j] == phone[j]);
        }
        if(match) {
            i += m - 1;
            ++ans;
        }
    }
    cout << ans << endl;
}