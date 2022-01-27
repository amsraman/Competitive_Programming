#include <bits/stdc++.h>

using namespace std;

int n, num[1001];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> num[i];
    }
    int cur = num[0];
    for(int i = 1; i < n; i++) {
        if(num[i] % cur == 0) {
            cout << num[i] << endl;
            cur = num[i + 1], i++;
        }
    }
}