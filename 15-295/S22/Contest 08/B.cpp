#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, k;
ll nums[30];

int main() {
    cin >> t;
    nums[0] = 1;
    for(int i = 1; i < 30; i++) {
        nums[i] = nums[i - 1] * 2;
    }
    ++nums[0];
    for(int i = 0; i < 30; i++) {
        nums[i] *= (i + 1);
    }
    for(int i = 1; i < 30; i++) {
        nums[i] += nums[i - 1];
    }
    while(t--) {
        cin >> k;
        int ans = 0;
        while(nums[ans] + 1 <= k) {
            ++ans;
        }
        if(k < 2) {
            cout << 0 << '\n';
        } else if(k == 2) {
            cout << 1 << '\n';
        } else {
            cout << ans + 1 << '\n';
        }
    }
}