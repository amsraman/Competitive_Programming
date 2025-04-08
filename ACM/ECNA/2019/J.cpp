#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<pair<int, int>> books;
    for(int i = 0; i < n; i++) {
        int l, d; cin >> l >> d;
        books.emplace_back(d, l);
    }
    sort(books.begin(), books.end());
    ll lb = 0, ub = 1e14;
    auto f = [&](ll per_day) {
        // observation: fixing the days we do on time, we always want to order them by deadline
        // so, maintain the following quantity for every prefix (by deadline time):
        //     (max we can get done, earliest we can get it done by)
        int mx = 0; ll sum = 0;
        priority_queue<int> q;
        for(int i = 0; i < n; i++) {
            auto [deadline, len] = books[i];
            if(sum + len <= 1LL * deadline * per_day) { // yay
                sum += len, ++mx;
                q.push(len);
            } else if(mx > 0) {
                int tp = q.top();
                if(len < tp) {
                    q.pop(); q.push(len);
                    sum += len - tp;
                }
            }
        }
        return n - mx;
    };
    while(lb < ub) {
        ll mid = (lb + ub) / 2;
        if(f(mid) <= m) {
            ub = mid;
        } else {
            lb = mid + 1;
        }
    }
    cout << ub << '\n';
}