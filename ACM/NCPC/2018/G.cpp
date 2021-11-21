#include <bits/stdc++.h>

using namespace std;

int n, m, col[100][100];
set<int> used_vertices;
multiset<int> incident_colors[100];
set<pair<int, int>> used_edges;
vector<int> g[100], fan;
vector<string> match[100];

string conv(int x) {
    string ret = "";
    ret += char('A' + (x / n));
    ret += to_string(1 + (x % n));
    return ret;
}

void inv_col(int u, int c, int d) {
    for(int v: g[u]) {
        if(!used_edges.count({u, v}) && (col[u][v] == c || col[u][v] == d)) {
            used_edges.insert({u, v}), used_edges.insert({v, u});
            incident_colors[u].erase(incident_colors[u].find(col[u][v])), incident_colors[v].erase(incident_colors[v].find(col[u][v]));
            col[u][v] ^= (c ^ d), col[v][u] ^= (c ^ d);
            incident_colors[u].insert(col[u][v]), incident_colors[v].insert(col[u][v]);
            inv_col(v, c, d);
        }
    }
}

void misra_gries() {
    for(int i = 0; i < n * m; i++) {
        for(int j: g[i]) {
            if(col[i][j] > 0) {
                continue;
            }
            fan.push_back(j), used_vertices.insert(j);
            while(true) {
                int to_add = -1;
                for(int nxt: g[i]) {
                    if(used_vertices.count(nxt) || col[i][nxt] == 0) {
                        continue;
                    }
                    if(!incident_colors[fan.back()].count(col[i][nxt])) {
                        to_add = nxt;
                    }
                }
                if(to_add == -1) {
                    break;
                }
                fan.push_back(to_add);
                used_vertices.insert(to_add);
            }
            int c = 1, d = 1, w;
            while(incident_colors[i].count(c)) {
                ++c;
            }
            while(incident_colors[fan.back()].count(d)) {
                ++d;
            }
            inv_col(i, c, d);
            for(w = 0; w < fan.size(); w++) {
                if(!incident_colors[fan[w]].count(d)) {
                    break;
                }
                col[i][fan[w]] = col[fan[w]][i] = col[i][fan[w + 1]];
                incident_colors[fan[w]].insert(col[i][fan[w + 1]]);
                incident_colors[fan[w + 1]].erase(incident_colors[fan[w + 1]].find(col[i][fan[w + 1]]));
            }
            col[i][fan[w]] = col[fan[w]][i] = d;
            incident_colors[i].insert(d);
            incident_colors[fan[w]].insert(d);
            fan.clear(), used_vertices.clear(), used_edges.clear();
        }
    }
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < n * m; i++) {
        for(int j = i + 1; j < n * m; j++) {
            if(i / n != j / n) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    misra_gries();
    for(int i = 0; i < n * m; i++) {
        for(int j: g[i]) {
            if(i < j) {
                match[col[i][j] - 1].push_back(conv(i) + "-" + conv(j));
            }
        }
    }
    for(int i = 0; i < n * m - n + 1; i++) {
        for(string mv: match[i]) {
            cout << mv << " ";
        }
        if(!match[i].empty()) {
            cout << endl;
        }
    }
}