#include <bits/stdc++.h>

using namespace std;

array<int, 30> id, t1, t2;
vector<array<int, 30>> rots;
vector<int> grps[3];
set<array<int, 30>> seen;

array<int, 30> compose(array<int, 30> f1, array<int, 30> f2) {
    array<int, 30> res;
    for(int i = 0; i < 30; i++) {
        res[i] = f2[f1[i]];
    }
    return res;
}

int app(vector<int> gp, array<int, 30> f) {
    int ret = 0;
    for(int i: gp) {
        ret += (1 << (f[i]));
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    id = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
    t1 = {4, 0, 1, 2, 3, 9, 5, 6, 7, 8, 18, 19, 10, 11, 12, 13, 14, 15, 16, 17, 24, 20, 21, 22, 23, 29, 25, 26, 27, 28};
    t2 = {0, 9, 18, 19, 5, 4, 17, 24, 10, 1, 8, 16, 23, 29, 25, 20, 11, 6, 2, 3, 15, 28, 26, 12, 7, 14, 22, 27, 21, 13};
    queue<array<int, 30>> q;
    q.push(id);
    while(!q.empty()) {
        array<int, 30> cur = q.front();
        q.pop();
        array<int, 30> a1 = compose(cur, t1), a2 = compose(cur, t2);
        if(!seen.count(a1)) {
            seen.insert(a1);
            rots.push_back(a1);
            q.push(a1);
        }
        if(!seen.count(a2)) {
            seen.insert(a2);
            rots.push_back(a2);
            q.push(a2);
        }
    }
    for(int i = 0, sz; i < 3; i++) {
        cin >> sz;
        grps[i].resize(sz);
        for(int j = 0; j < sz; j++) {
            cin >> grps[i][j];
            --grps[i][j];
        }
    }
    bool ans = false;
    for(int i = 0; i < 60; i++) {
        for(int j = 0; j < 60; j++) {
            int msk1 = app(grps[0], id), msk2 = app(grps[1], rots[i]), msk3 = app(grps[2], rots[j]);
            if(((msk1 | msk2 | msk3) == (1 << 30) - 1) && max({msk1 & msk2, msk1 & msk3, msk2 & msk3}) == 0) {
                ans = true;
            }
        }
    }
    cout << (ans ? "Yes": "No") << '\n';
}