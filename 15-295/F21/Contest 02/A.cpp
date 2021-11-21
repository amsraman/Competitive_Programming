#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n;
pair<string, int> orig[100000];
vector<pair<string, int>> ans;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    multiset<int> cur;
    for(int i = 0; i < n; i++) {
        cin >> orig[i].f;
        if(orig[i].f == "insert") {
            cin >> orig[i].s;
            cur.insert(orig[i].s);
        } else if(orig[i].f == "removeMin") {
            if(cur.empty()) {
                ans.push_back({"insert", 1});
                cur.insert(1);
            }
            cur.erase(cur.begin());
        } else {
            cin >> orig[i].s;
            if(!cur.empty() && *cur.begin() > orig[i].s) {
                ans.push_back({"insert", orig[i].s});
                cur.insert(orig[i].s);
            } else if(cur.empty() || *cur.begin() < orig[i].s) {
                while(!cur.empty() && *cur.begin() < orig[i].s) {
                    ans.push_back({"removeMin", -1});
                    cur.erase(cur.begin());
                }
                if(cur.empty() || *cur.begin() != orig[i].s) {
                    ans.push_back({"insert", orig[i].s});
                    cur.insert(orig[i].s);
                }
            }
        }
        ans.push_back(orig[i]);
    }
    cout << ans.size() << endl;
    for(auto it: ans) {
        cout << it.f;
        if(it.f != "removeMin") {
            cout << " " << it.s;
        }
        cout << '\n';
    }
}