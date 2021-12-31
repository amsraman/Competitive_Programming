#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int x, y, cat[32];
array<ll, 6> num[32];
array<int, 9> transition[4];
// 0: Inf Component
// 1: Main Diagonal
// 2: 1s Touching Right Only
// 3: -1s Touching Right Only
// 4: 1s Touching Bottom Only
// 5: -1s Touching Bottom Only
// 6: 1s Touching Right and Bottom
// 7: -1s Touching Right and Bottom
// 8: Predetermined

int get_component(ll x, ll y, int lev) {
    if(lev == 0) {
        return cat[0] = 0;
    }
    ll pw2 = (1LL << (lev - 1));
    int xs = (x >= pw2), ys = (y >= pw2), quad = (xs << 1) | ys;
    return cat[lev] = transition[quad][get_component(x - xs * pw2, y - ys * pw2, lev - 1)];
}

int main() {
    cin >> x >> y;
    num[0] = {1, 0, 0, 0, 0, 0};
    for(int i = 1; i < 32; i++) {
        num[i][0] = 3 * num[i - 1][0] + num[i - 1][2] + num[i - 1][4];
        num[i][1] = num[i - 1][0] + 2 * num[i - 1][1] + num[i - 1][3] + 2 * num[i - 1][5];
        num[i][2] = num[i - 1][2] + num[i - 1][3] + 2 * num[i - 1][4];
        num[i][3] = num[i - 1][2] + num[i - 1][3];
        num[i][4] = num[i - 1][1] + num[i - 1][5];
        num[i][5] = num[i - 1][4];
    }
    transition[0] = {0, 8, 0, 8, 0, 8, 0, 8, 8};
    transition[1] = {0, 1, 2, 3, 8, 1, 2, 1, 8};
    transition[2] = {0, 1, 8, 1, 4, 5, 4, 1, 8};
    transition[3] = {1, 6, 3, 2, 5, 4, 7, 6, 8};
    get_component(x, y, 31);
    if(cat[31] == 0) {
        cout << "infinity" << endl;
    } else {
        for(int i = 31; i >= 0; i--) {
            if(cat[i] == 1) {
                cout << num[i][1] << endl;
                break;
            }
        }
    }
}