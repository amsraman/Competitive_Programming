#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for(int _ = 1; _ <= t; _++) {
        int k, w; cin >> k >> w;
        cin.ignore();
        int cur = 1; set<int> wind; wind.insert(0);
        for(int i = 0; i < k; i++) {
            string s; getline(cin, s);
            int n = (int) s.length();
            set<int> nums;
            for(int dig = 1; dig <= 7; dig++) {
                for(int j = 0; j < n; j++) {
                    if(j + dig > n) break;
                    if(!all_of(s.begin() + j, s.begin() + j + dig, ::isdigit)) continue;
                    int tp = atoi(s.substr(j, dig).c_str());
                    nums.insert(tp);
                }
            }
            for(int num: nums) {
                if(num == cur) {
                    wind.insert(num);
                    while(wind.count(cur)) {
                        wind.erase(wind.begin());
                        ++cur;
                    }
                } else if(num > cur && num <= cur + w - 1 && !wind.count(num)) {
                    wind.insert(num);
                }
            }
        }
        cout << "Case " << _ << ": " << cur - 1 << " " << *--wind.end() << '\n';
    }
}