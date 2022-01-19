#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n;
ll ans;
pair<int, pair<int, int>> nums[200000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < 2 * n; i++) {
        cin >> nums[i].s.f >> nums[i].s.s;
        if(nums[i].s.f > nums[i].s.s) {
            swap(nums[i].s.f, nums[i].s.s);
        }
        nums[i].f = nums[i].s.f + nums[i].s.s;
    }
    sort(nums, nums + 2 * n);
    for(int i = 0; i < 2 * n; i++) {
        if(i < n) {
            ans -= nums[i].s.f;
        } else {
            ans += nums[i].s.s;
        }
    }
    cout << ans << '\n';
}