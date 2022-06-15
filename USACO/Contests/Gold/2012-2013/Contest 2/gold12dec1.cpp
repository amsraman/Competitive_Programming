#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int ending(vector<int> & gangs, int num, int mx) {
    int n = gangs.size();
    set<pair<int, int>> cur;
    for(int i = 1; i < n; i++) {
        cur.insert({-gangs[i], i});
    }
    while(cur.begin()->f < 0) {
        pair<int, int> tp = *cur.begin();
        cur.erase(tp), cur.insert({tp.f + 1, tp.s});
        if(num == 0) {
            num = 1, mx = tp.s;
        } else if(mx != tp.s) {
            --num;
        } else {
            ++num;
        }
    }
    for(int i = 0; i < gangs[0]; i++) {
        if(num == 0) {
            num = 1, mx = 0;
        } else if(mx != 0) {
            --num;
        } else {
            ++num;
        }
    }
    if(mx == 0) {
        return num;
    }
    return 0;
}

int main() {
    ifstream cin("gangs.in");
    ofstream cout("gangs.out");
    int n, m;
    cin >> n >> m;
    vector<int> gangs(m), ans;
    for(int i = 0; i < m; i++) {
        cin >> gangs[i];
    }
    if(m == 1) {
        cout << "YES" << endl << n << endl;
        for(int i = 0; i < n; i++) {
            cout << 1 << endl;
        }
    } else {
        int best = ending(gangs, 0, 0);
        if(best == 0) {
            cout << "NO" << endl;
        } else {
            int num = 0, mx = 0;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if(gangs[j] > 0) {
                        --gangs[j];
                        int new_num = num, new_mx = mx;
                        if(num == 0) {
                            new_num = 1, new_mx = j;
                        } else if(j == mx) {
                            ++new_num;
                        } else {
                            --new_num;
                        }
                        if(ending(gangs, new_num, new_mx) == best) {
                            num = new_num, mx = new_mx;
                            ans.push_back(j);
                            break;
                        }
                        ++gangs[j];
                    }
                }
            }
            cout << "YES" << endl << best << endl;
            for(int a: ans) {
                cout << a + 1 << endl;
            }
        }
    }
}