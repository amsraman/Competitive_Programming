#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, ax, ay, bx, by, cx, cy;
pair<int, int> dir[8] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
bool bl[1000][1000], vis[1000][1000];

bool ok(int x, int y, int dx, int dy) {
    return (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < n);
}

int main() {
    cin >> n >> ax >> ay >> bx >> by >> cx >> cy;
    --ax, --ay, --bx, --by, --cx, --cy;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == ax || j == ay || (i - j == ax - ay) || (i + j == ax + ay)) {
                bl[i][j] = true;
            }
        }
    }
    queue<pair<int, int>> q;
    q.push({bx, by});
    vis[bx][by] = true;
    while(!q.empty()) {
        pair<int, int> tp = q.front();
        q.pop();
        int x = tp.f, y = tp.s;
        for(pair<int, int> d: dir) {
            if(ok(x, y, d.f, d.s) && !vis[x + d.f][y + d.s] && !bl[x + d.f][y + d.s]) {
                q.push({x + d.f, y + d.s});
                vis[x + d.f][y + d.s] = true;
            }
        }
    }
    cout << (vis[cx][cy] ? "YES" : "NO") << '\n';
}