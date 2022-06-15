#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    string s, tot_str;
    while(getline(cin, s)) {
        tot_str += (s + '\n');
    }
    auto is_space = [](char c) {
        return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v');
    };
    auto is_prime = [](int x) {
        for(int i = 2; i * i <= x; i++) {
            if(x % i == 0) {
                return false;
            }
        }
        return x >= 2;
    };
    bool ans = true;
    char pv_char = ' ';
    int nums = 0;
    for(char c: tot_str) {
        if(!is_space(c) && !isdigit(c)) {
            ans = false;
        }
        nums += (is_space(pv_char) && isdigit(c));
        pv_char = c;
    }
    if(nums == 3) {
        vector<int> nums;
        ll cur = -1;
        for(char c: tot_str) {
            if(isdigit(c)) {
                if(cur == -1 && c == '0') {
                    ans = false;
                }
                cur = max(cur, 0LL) * 10 + c - '0';
                if(cur > 1e9) {
                    ans = false;
                }
            } else {
                if(cur >= 0) {
                    nums.push_back(cur);
                }
                cur = -1;
            }
        }
        ans = (ans && nums.size() == 3 && nums[0] > 3 && (nums[0] % 2 == 0) && (nums[1] + nums[2] == nums[0]) && is_prime(nums[1]) && is_prime(nums[2]));
    } else {
        ans = false;
    }
    cout << ans << endl;
}