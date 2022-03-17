#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int n, m, stat[50][50], tmp[50][50], ans = 5000;
vector<int> nums;
vector<pair<int, int>> entries[100];
multiset<int> statues[100];

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> stat[i][j];
            tmp[i][j] = stat[i][j];
            if(stat[i][j] > -1) {
                nums.push_back(stat[i][j]);
            }
        }
    }
    sort(nums.begin(), nums.end());
    for(int x = 0; x < 2; x++) {
        for(int y = 0; y < 2; y++) {
            int cur = 0;
            for(int i = 0; i < n + m - 1; i++) {
                entries[i].clear();
                statues[i].clear();
            }
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if(tmp[i][j] != -1) {
                        entries[i + j].push_back({i, j});
                    }
                }
            }
            for(int i = 0, k = 0; i < n + m - 1; i++) {
                for(pair<int, int> j: entries[i]) {
                    tmp[j.f][j.s] = nums[k++];
                    statues[i].insert(tmp[j.f][j.s]);
                }
            }
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if(stat[i][j] > -1) {
                        if(statues[i + j].count(stat[i][j])) {
                            statues[i + j].erase(statues[i + j].count(stat[i][j]));
                        } else {
                            ++cur;
                        }
                    }
                }
            }
            ans = min(ans, cur);
            for(int i = 0; i < m; i++) {
                for(int j = 0, k = n - 1; j < k; j++, k--) {
                    swap(stat[j][i], stat[k][i]);
                    swap(tmp[j][i], tmp[k][i]);
                }
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0, k = m - 1; j < k; j++, k--) {
                swap(stat[i][j], stat[i][k]);
                swap(tmp[i][j], tmp[i][k]);
            }
        }
    }
    cout << ans << endl;
}