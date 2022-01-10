#include <bits/stdc++.h>

using namespace std;

int wc, hc, wds, hs;

int main() {
    cin >> wc >> hc >> wds >> hs;
    cout << (wds + 2 <= wc && hs + 2 <= hc) << endl;
}