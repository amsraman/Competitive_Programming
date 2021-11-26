#include <bits/stdc++.h>

using namespace std;

int n;
array<int, 5> points[1000];
vector<int> good;

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 5; j++) {
            cin >> points[i][j];
        }
    }
    if(n >= 50) {
        cout << 0 << endl;
    } else {
        for(int i = 0; i < n; i++) {
            vector<array<int, 5>> dif;
            bool is_good = false;
            for(int j = 0; j < n; j++) {
                if(i != j) {
                    array<int, 5> tmp;
                    for(int k = 0; k < 5; k++) {
                        tmp[k] = points[j][k] - points[i][k];
                    }
                    dif.push_back(tmp);
                }
            }
            for(int j = 0; j < dif.size(); j++) {
                for(int k = j + 1; k < dif.size(); k++) {
                    int dot_prod = 0;
                    for(int l = 0; l < 5; l++) {
                        dot_prod += dif[j][l] * dif[k][l];
                    }
                    if(dot_prod > 0) {
                        is_good = true;
                    }
                }
            }
            if(!is_good) {
                good.push_back(i);
            }
        }
        cout << good.size() << endl;
        for(int i: good) {
            cout << i + 1 << " ";
        }
        cout << endl;
    }
}