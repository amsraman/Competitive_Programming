#include <bits/stdc++.h>

using namespace std;

long long ax, ay, bx, by, cx, cy;

int main() {
    cin >> ax >> ay >> bx >> by >> cx >> cy;
    if((by - ay) * (cx - bx) == (cy - by) * (bx - ax)) {
        cout << "No" << endl;
    } else {
        long long dist1 = (bx - ax) * (bx - ax) + (by - ay) * (by - ay);
        long long dist2 = (cx - bx) * (cx - bx) + (cy - by) * (cy - by);
        cout << (dist1 == dist2 ? "Yes" : "No") << endl;
    }
}