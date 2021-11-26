#include <bits/stdc++.h>
typedef long long ll;
#define f first
#define s second

using namespace std;

int n, ans[100000];
pair<int, int> moves[100000];
vector<int> members[100000], top;

bool ok(pair<ll, ll> move) {
    return (move.f * move.f + move.s * move.s <= 1e12);
}

void unite(int x, int y, int sw) {
    if(members[x].size() < members[y].size()) {
        swap(x, y);
    }
    for(int i: members[y]) {
        ans[i] *= sw;
        members[x].push_back(i);
    }
    top.erase(find(top.begin(), top.end(), y));
    moves[x] = {moves[x].f + sw * moves[y].f, moves[x].s + sw * moves[y].s};
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> moves[i].f >> moves[i].s;
        ans[i] = 1;
        members[i].push_back(i);
    }
    for(int i = 0; i < n; i++) {
        top.push_back(i);
        if(top.size() < 3) {
            continue;
        }
        assert(top.size() == 3);
        if(ok({moves[top[0]].f + moves[top[1]].f, moves[top[0]].s + moves[top[1]].s})) {
            unite(top[0], top[1], 1);
        } else if(ok({moves[top[0]].f + moves[top[2]].f, moves[top[0]].s + moves[top[2]].s})) {
            unite(top[0], top[2], 1);
        } else if(ok({moves[top[1]].f + moves[top[2]].f, moves[top[1]].s + moves[top[2]].s})) {
            unite(top[1], top[2], 1);
        } else if(ok({moves[top[0]].f - moves[top[1]].f, moves[top[0]].s - moves[top[1]].s})) {
            unite(top[0], top[1], -1);
        } else if(ok({moves[top[0]].f - moves[top[2]].f, moves[top[0]].s - moves[top[2]].s})) {
            unite(top[0], top[2], -1);
        } else if(ok({moves[top[1]].f - moves[top[2]].f, moves[top[1]].s - moves[top[2]].s})) {
            unite(top[1], top[2], -1);
        }
    }
    if(!ok({moves[top[0]].f + moves[top[1]].f, moves[top[0]].s + moves[top[1]].s})) {
        unite(top[0], top[1], -1);
    }
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
/*
I'm drunk in the back of the car
And I cried like a baby coming home from the bar (oh)
Said I'm fine, but it wasn't true
I don't wanna keep secrets just to keep you
*/