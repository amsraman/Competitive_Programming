#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    map<char, int> numer = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}};
    string s; cin >> s;
    for(int _ = 1; s != "0"; _++) {
        int n = s.length();
        vector<vector<bitset<5001>>> pos(n, vector<bitset<5001>>(n));
        vector<vector<vector<int>>> vals(n, vector<vector<int>>(n));
        for(int i = n - 1; i >= 0; i--) {
            pos[i][i][numer[s[i]]] = true; vals[i][i].push_back(numer[s[i]]);
            for(int j = i + 1; j < n; j++) {
                for(int k = i; k < j; k++) {
                    for(int p1: vals[i][k]) {
                        for(int p2: vals[k + 1][j]) {
                            if(p1 >= p2) pos[i][j][p1 + p2] = true;
                            else pos[i][j][p2 - p1] = true;
                        }
                    }
                }
                for(int k = 0; k <= 5000; k++) if(pos[i][j][k]) vals[i][j].push_back(k);
            }
        }
        cout << "Case " << _ << ": ";
        for(int p: vals[0][n - 1]) cout << p << " ";
        cout << '\n';
        cin >> s;
    }
}