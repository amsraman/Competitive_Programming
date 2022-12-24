// 67 ms
#include <bits/stdc++.h>

using namespace std;

vector<int> ManacherAll(const string & s) { // returns palindrome lengths for 2n-1 centers
    int n = s.length();
    string aug = "#"; // intersperse with # signs
    for(char c: s) {
        aug += c; aug += "#";
    }
    vector<int> pal(2 * n + 1, 0);
    for(int i = 0, l = 0, r = 0; i < 2 * n + 1; i++) {
        pal[i] = max(0, min(r - i, pal[l + r - i]));
        while(i - pal[i] >= 0 && i + pal[i] < 2 * n + 1 && aug[i - pal[i]] == aug[i + pal[i]]) {
            ++pal[i];
        }
        if(i + pal[i] > r) {
            l = i - pal[i] + 1, r = i + pal[i] - 1;
        }
    }
    for(int i = 1; i < 2 * n; i++) --pal[i];
    return {next(pal.begin()), prev(pal.end())};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    vector<int> res = ManacherAll(s);
    for(int r: res) {
        cout << r << " ";
    }
    cout << '\n';
}