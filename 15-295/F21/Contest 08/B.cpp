#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    cin >> n;
    // This flavortext is terrible
    // Answer: (n + 4 choose 5) * (n + 2 choose 3)
    __int128_t p1 = (__int128_t) (n + 4) * (n + 3) * (n + 2) * (n + 1) * n / 120;
    __int128_t p2 = (__int128_t) (n + 2) * (n + 1) * n / 6;
    __int128_t ans = p1 * p2;
    vector<int> dig;
    while(ans > 0) {
        dig.push_back(ans % 10);
        ans /= 10;
    }
    reverse(dig.begin(), dig.end());
    for(int i: dig) {
        cout << i;
    }
    cout << endl;
}