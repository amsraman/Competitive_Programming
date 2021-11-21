#include <bits/stdc++.h>

using namespace std;

int n, m, k[100001], al[100001], ar[100001], bl[100001], br[100001], nxt[100001][2], cur[2];
bool pos[100001][2];

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> k[i + 1] >> al[i + 1] >> bl[i + 1] >> ar[i + 1] >> br[i + 1];
    }
    ++n;
    cur[0] = cur[1] = n - 1;
    int la = 0, lb = m, ra = 0, rb = m;
    bool inl = true, inr = true;
    for(int i = n - 1; i >= 0; i--) {
        la = max(la, al[i]), lb = min(lb, bl[i]);
        ra = max(ra, ar[i]), rb = min(rb, br[i]);
        pos[i][0] = inr && (k[i] >= la && k[i] <= lb);
        pos[i][1] = inl && (k[i] >= ra && k[i] <= rb);
        int nc0 = cur[0], nc1 = cur[1];
        if(pos[i][0]) {
            ra = ar[i], rb = br[i];
            inl = true;
            nc0 = i;
            nxt[i][0] = cur[1];
        }
        if(pos[i][1]) {
            la = al[i], lb = bl[i];
            inr = true;
            nc1 = i;
            nxt[i][1] = cur[0];
        }
        cur[0] = nc0, cur[1] = nc1;
        inl &= (k[i] >= al[i] && k[i] <= bl[i]);
        inr &= (k[i] >= ar[i] && k[i] <= br[i]);
    }
    if(pos[0][0]) {
        cout << "Yes" << endl;
        int card = 0, side = 0;
        while(card < n - 1) {
            for(int i = card; i < nxt[card][side]; i++) {
                cout << (side ^ 1) << " ";
            }
            card = nxt[card][side];
            side ^= 1;
        }
        cout << endl;
    } else if(pos[0][1]) {
        cout << "Yes" << endl;
        int card = 0, side = 1;
        while(card < n - 1) {
            for(int i = card; i < nxt[card][side]; i++) {
                cout << (side ^ 1) << " ";
            }
            card = nxt[card][side];
            side ^= 1;
        }
        cout << endl;
    } else {
        cout << "No" << endl;
    }
}