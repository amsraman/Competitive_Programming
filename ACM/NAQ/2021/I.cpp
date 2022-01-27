#include <bits/stdc++.h>

using namespace std;

int c, num[1000], tot[1000];
string targ[1000];
map<string, vector<int>> edges;
set<string> toppings;
bool tp[1000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> c;
    for(int i = 0; i < c; i++) {
        string s;
        cin >> s;
        if(s == "if") {
            string comm;
            cin >> comm;
            while(comm != "then") {
                if(comm == "and") {
                    tp[i] = true;
                } else if(comm != "or") {
                    edges[comm].push_back(i);
                    ++tot[i];
                }
                cin >> comm;
            }
            cin >> targ[i];
        } else {
            toppings.insert(s);
        }
    }
    queue<string> q;
    for(string s: toppings) {
        q.push(s);
    }
    while(!q.empty()) {
        string s = q.front();
        q.pop();
        for(int e: edges[s]) {
            if(tp[e]) {
                ++num[e];
                if(num[e] == tot[e] && !toppings.count(targ[e])) {
                    toppings.insert(targ[e]);
                    q.push(targ[e]);
                }
            } else if(!toppings.count(targ[e])) {
                toppings.insert(targ[e]);
                q.push(targ[e]);
            }
        }
    }
    cout << toppings.size() << '\n';
}