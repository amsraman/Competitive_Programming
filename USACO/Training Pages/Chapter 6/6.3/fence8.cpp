/*
ID: adisund1
TASK: fence8
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int n, r, boards[50], rails[1023], left_over[50], ps[1023], sum_left;

bool chk(int x, int starting_point) {
    if(x == 0) {
        return true;
    }
    if(sum_left < ps[x-1]) {
        return false;
    }
    for(int i = starting_point; i<n; i++) {
        if(left_over[i] >= rails[x-1]) {
            sum_left -= left_over[i];
            left_over[i] -= rails[x-1];
            if(left_over[i] >= rails[0]) {
                sum_left += left_over[i];
            }
            int ns = ((x>2 && rails[x-1] == rails[x-2]) ? i : 0);
            if(chk(x-1,ns)) {
                return true;
            }
            if(left_over[i] >= rails[0]) {
                sum_left -= left_over[i];
            }
            left_over[i] += rails[x-1];
            sum_left += left_over[i];
            if(left_over[i] == rails[x-1]) {
                break;
            }
        }
    }
    return false;
}

int main() {
    freopen("fence8.in","r",stdin);
    freopen("fence8.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++) {
        cin >> boards[i];
    }
    cin >> r;
    for(int i = 0; i<r; i++) {
        cin >> rails[i];
    }
    sort(rails,rails+r);
    for(int i = 1; i<r; i++) {
        ps[i] = ps[i-1] + rails[i];
    }
    int lb = 0, ub = r;
    while(lb<ub) {
        int mid = (lb+ub+1)/2;
        sum_left = 0;
        for(int i = 0; i<n; i++) {
            left_over[i] = boards[i];
            if(left_over[i] >= rails[0]) {
                sum_left += left_over[i];
            }
        }
        if(chk(mid,0)) {
            lb = mid;
        } else {
            ub = mid-1;
        }
    }
    cout << ub << endl;
}