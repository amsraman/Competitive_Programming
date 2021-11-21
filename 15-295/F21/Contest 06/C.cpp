#include <bits/stdc++.h>

using namespace std;

const int INF = 5e5;

int n, dist[26][26], ans;
string s, t, fin = "";

int main() {
    cin >> s >> t >> n;
    for(int i = 0; i < 26; i++) {
        for(int j = 0; j < 26; j++) {
            dist[i][j] = (i == j ? 0 : INF);
        }
    }
    for(int i = 0, z; i < n; i++) {
        char x, y;
        cin >> x >> y >> z;
        dist[(x - 'a')][(y - 'a')] = min(dist[(x - 'a')][(y - 'a')], z);
    }
    for(int k = 0; k < 26; k++) {
        for(int i = 0; i < 26; i++) {
            for(int j = 0; j < 26; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    bool pos = (s.length() == t.length());
    for(int i = 0; i < min(s.length(), t.length()); i++) {
        int nxt = INF;
        char lst = 'a';
        for(int j = 0; j < 26; j++) {
            if(dist[(s[i] - 'a')][j] != INF && dist[(t[i] - 'a')][j] != INF && nxt > dist[(s[i] - 'a')][j] + dist[(t[i] - 'a')][j]) {
                nxt = dist[(s[i] - 'a')][j] + dist[(t[i] - 'a')][j];
                lst = char('a' + j);
            }
        }
        if(nxt == INF) {
            pos = false;
        }
        ans += nxt;
        fin += lst;
    }
    if(!pos) {
        cout << -1 << endl;
    } else {
        cout << ans << endl << fin << endl;
    }
}