#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

template <typename T>
struct FenwickTree {
    int n;
    vector<T> bit;
    FenwickTree(int n): n(n), bit(n, 0) {};
    FenwickTree(vector<T> & init): n((int) init.size()), bit((int) init.size()) {
        copy(init.begin(), init.end(), bit.begin());
        for(int i = 1; i <= n; i++) {
            if(i + (i & -i) <= n) {
                bit[i + (i & -i) - 1] += bit[i - 1];
            }
        }
    }
    T qry(int k) {
        T ret = 0;
        for(k++; k > 0; k -= k & -k) {
            ret += bit[k - 1];
        }
        return ret;
    }
    T qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }
    void upd(int k, T x) {
        for(k++; k <= n; k += k & -k) {
            bit[k - 1] += x;
        }
    }
};

ll count_swaps(vector<int> s) {
    int n = s.size();
    ll ans = 0;
    FenwickTree<int> ft(n);
    vector<queue<int>> lefts(n / 2), rights(n / 2);
    vector<bool> done(n, false);
    for(int i = 0; i < n; i++) {
        ft.upd(i, 1);
        if(s[i] < 0) {
            lefts[-s[i] - 1].push(i);
        } else {
            rights[s[i] - 1].push(i);
        }
    }
    for(int i = 0, j = 0; i < n / 2; i++) {
        while(done[j]) {
            ++j;
        }
        int left_thing, right_thing;
        if(s[j] < 0) {
            left_thing = j, right_thing = rights[-s[j] - 1].front();
        } else {
            left_thing = lefts[s[j] - 1].front(), right_thing = j;
        }
        lefts[abs(s[j]) - 1].pop(), rights[abs(s[j]) - 1].pop(), done[left_thing] = done[right_thing] = true;
        ft.upd(left_thing, -1); ans += ft.qry(left_thing);
        ft.upd(right_thing, -1); ans += ft.qry(right_thing);
    }
    return ans;
}

int main() {
    cout << count_swaps({2, 1, -1, -2}) << endl;
    cout << count_swaps({-2, 2, 2, -2, -2, 2}) << endl;
}