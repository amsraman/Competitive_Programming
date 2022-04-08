#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define f first
#define s second

using namespace std;

const int num_students = 100, num_questions = 10000;

int t, p;
string res[100], tres[100];

int main() {
    cin >> t >> p;
    for(int _ = 1; _ <= t; _++) {
        vector<pair<int, int>> ord;
        for(int i = 0; i < num_questions; i++) {
            ord.push_back({0, i});
        }
        for(int i = 0; i < num_students; i++) {
            cin >> res[i];
            tres[i] = res[i];
            for(int j = 0; j < num_questions; j++) {
                ord[j].f += res[i][j] - '0';
            }
        }
        sort(ord.begin(), ord.end());
        reverse(ord.begin(), ord.end());
        for(int i = 0; i < num_students; i++) {
            for(int j = 0; j < num_questions; j++) {
                tres[i][j] = res[i][ord[j].s];
            }
        }
        int best = -1;
        ld cm = 0;
        for(int i = 0; i < num_students; i++) {
            ld cur = 0, n1 = 0;
            for(int j = 0; j < num_questions; j++) {
                if(tres[i][j] == '1') {
                    cur += n1;
                } else {
                    ++n1;
                }
            }
            cur /= n1;
            if(cur >= cm) {
                best = i;
                cm = cur;
            }
        }
        cout << "Case #" << _ << ": " << best + 1 << endl;
    }
}