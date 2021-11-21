#include <bits/stdc++.h>

using namespace std;

int n, m, k, mt[100000], state[100000], id[27 * 27 * 27 * 27];
string p[100000], w[100000];
vector<int> g[100000], topo;
bool cyc;

int ltoi(char x) {
    if(x == '_') {
        return 0;
    }
    return (x - 'a' + 1);
}

int conv(string x) {
    int ret = 0;
    for(char ch: x) {
        ret = 27 * ret + ltoi(ch);
    }
    return ret;
}

void dfs(int x) {
    state[x] = 1;
    for(int i: g[x]) {
        if(state[i] == 1) {
            cyc = true;
        }
        if(state[i] == 0) {
            dfs(i);
        }
    }
    topo.push_back(x), state[x] = 2;
}

int main() {
    for(int i = 0; i < 27 * 27 * 27 * 27; i++) {
        id[i] = -1;
    }
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for(int i = 0; i < m; i++) {
        cin >> w[i] >> mt[i];
    }
    for(int i = 0; i < n; i++) {
        id[conv(p[i])] = i;
    }
    for(int i = 0; i < m; i++) {
        vector<int> tmpv;
        bool inok = false;
        for(int j = 0; j < (1 << k); j++) {
            string tmp = "";
            for(int b = 0; b < k; b++) {
                if(j & (1 << b)) {
                    tmp += '_';
                } else {
                    tmp += w[i][b];
                }
            }
            if(id[conv(tmp)] == mt[i] - 1) {
                inok = true;
            }
            if(id[conv(tmp)] != -1) {
                tmpv.push_back(id[conv(tmp)]);
            }
        }
        if(!inok) {
            cyc = true;
        }
        for(int x: tmpv) {
            if(x != mt[i] - 1) {
                g[mt[i] - 1].push_back(x);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(state[i] == 0) {
            dfs(i);
        }
    }
    if(cyc) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        reverse(topo.begin(), topo.end());
        for(int i: topo) {
            cout << i + 1 << " ";
        }
        cout << endl;
    }
}