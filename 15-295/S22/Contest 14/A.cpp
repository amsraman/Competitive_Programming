#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> ans;
    while(n > 3) {
        ans.push_back(2);
        n -= 2;
    }
    ans.push_back(n);
    cout << ans.size() << endl;
    for(int a: ans) {
        cout << a << " ";
    }
    cout << endl;
}