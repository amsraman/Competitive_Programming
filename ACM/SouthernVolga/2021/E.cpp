#include <bits/stdc++.h>

using namespace std;

int n, t[33];
map<pair<unsigned int, int>, int> thr;

int conv(string x) {
    vector<int> dots;
    for(int i = 0; i < x.length(); i++) {
        if(x[i] == '.') {
            dots.push_back(i);
        }
    }
    vector<string> nums;
    nums.push_back(x.substr(0, dots[0]));
    nums.push_back(x.substr(dots[0] + 1, dots[1] - dots[0] - 1));
    nums.push_back(x.substr(dots[1] + 1, dots[2] - dots[1] - 1));
    nums.push_back(x.substr(dots[2] + 1, x.length() - dots[2] - 1));
    int ret = 0;
    for(string s: nums) {
        ret = (ret << 8) | atoi(s.c_str());
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for(int i = 0; i < 33; i++) {
        cin >> t[i];
    }
    cin >> n;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        unsigned int ip = conv(s);
        bool bad = false;
        for(int j = 0; j < 33; j++, ip >>= 1) {
            if(!thr.count({ip, j})) {
                thr[{ip, j}] = t[32 - j];
            }
            if(thr[{ip, j}] == 0) {
                bad = true;
            }
        }
        if(bad) {
            cout << "b\n";
        } else {
            cout << "a\n";
            ip = conv(s);
            for(int j = 0; j < 33; j++, ip >>= 1) {
                --thr[{ip, j}];
            }
        }
    }
}
