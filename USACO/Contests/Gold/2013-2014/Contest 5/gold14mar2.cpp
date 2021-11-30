#include <bits/stdc++.h>

using namespace std;

const double epsilon = 1e-6;

int n, m[100000];

bool ok(double x) {
    double sum = 0, mx = -2e9;
    vector<double> md(n), kadane(n, 0.0);
    for(int i = 0; i < n; i++) {
        md[i] = (double) m[i] - x, sum += md[i];
        if(i > 0 && i < n - 1) {
            kadane[i] = max(kadane[i - 1], 0.0) + md[i];
            mx = max(mx, kadane[i]);
        }
    }
    return sum - mx >= 0;
}

int main() {
    ifstream cin("sabotage.in");
    ofstream cout("sabotage.out");
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> m[i];
    }
    double lb = 0, ub = 2e4;
    while((ub - lb) >= epsilon) {
        double mid = (lb + ub) / 2;
        if(ok(mid)) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    cout << fixed << setprecision(3) << ub << endl;
}