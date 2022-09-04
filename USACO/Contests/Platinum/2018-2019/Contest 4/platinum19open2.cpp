#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int mod = 1e9 + 7;
const ll INF = 0xfffffffffffffff;

int n, k, he[30000][6], ve[30000][6], id[200000], nxt[132][6][4], num[2][132];
ll dp[2][132];
vector<int> msks;

vector<int> dig_vec(int msk) {
    vector<int> digits;
    while(msk > 0) {
        digits.push_back(msk % (k + 1)), msk /= (k + 1);
    }
    return digits;
}

int conv(vector<int> dig) {
    int res = 0;
    for(int i = k - 1; i >= 0; i--) {
        res = (k + 1) * res + dig[i];
    }
    return res;
}

bool valid(int msk) {
    int sz = 0;
    stack<int> st;
    vector<int> state(k, 0);
    for(; msk > 0; sz++, msk /= (k + 1)) {
        int dig = msk % (k + 1);
        if(dig == 0) {
            return false;
        }
        if(state[dig - 1] == 0) {
            st.push(dig - 1), state[dig - 1] = 1;
        } else if(state[dig - 1] == 1) {
            while(st.top() != dig - 1) {
                state[st.top()] = 2; st.pop();
            }
        } else {
            return false;
        }
    }
    return sz == k;
}

vector<int> normalize(vector<int> vec) {
    int num = 1;
    vector<int> mp(k, -1);
    for(int i = k - 1; i >= 0; i--) {
        if(mp[vec[i] - 1] == -1) {
            mp[vec[i] - 1] = num++;
        }
        vec[i] = mp[vec[i] - 1];
    }
    return vec;
}

bool singleton(vector<int> vec, int pos) {
    int same_group = 0;
    for(int d: vec) {
        same_group += d == vec[pos];
    }
    return same_group == 1;
}

vector<int> group_merge(vector<int> vec, int g1, int g2) {
    int rem = vec[g2];
    for(int i = 0; i < k; i++) {
        vec[i] = (vec[i] == rem ? vec[g1] : vec[i]);
    }
    return normalize(vec);
}

int main() {
    ifstream cin("escape.in");
    ofstream cout("escape.out");
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        for(int j = 1; j < k; j++) {
            cin >> he[i][j];
        }
    }
    for(int i = 0; i < k; i++) {
        for(int j = 1; j < n; j++) {
            cin >> ve[j][i];
        }
    }
    for(int i = 1; i < 200000; i++) {
        if(valid(i)) {
            msks.push_back(conv(normalize(dig_vec(i))));
        }
    }
    sort(msks.begin(), msks.end());
    msks.erase(unique(msks.begin(), msks.end()), msks.end());
    for(int msk = 0; msk < msks.size(); msk++) {
        id[msks[msk]] = msk, dp[0][msk] = INF;
    }
    dp[0][msks.size() - 1] = 0, num[0][msks.size() - 1] = 1;
    for(int i = 0; i < msks.size(); i++) {
        for(int j = 0; j < k; j++) {
            vector<int> vec = dig_vec(msks[i]);
            nxt[i][j][1] = i;
            nxt[i][j][3] = (j == 0 ? -1 : id[conv(group_merge(vec, k - j - 1, k - j))]);
            if(singleton(vec, k - j - 1)) {
                nxt[i][j][0] = nxt[i][j][2] = -1;
            } else {
                vec[k - j - 1] = k, nxt[i][j][0] = id[conv(normalize(vec))];
                if(j > 0) {
                    vec[k - j - 1] = vec[k - j], nxt[i][j][2] = id[conv(normalize(vec))];
                } else {
                    nxt[i][j][2] = -1;
                }
            }
        }
    }
    for(int i = 1; i < n * k; i++) {
        int row = i / k, col = i % k;
        for(int msk = 0; msk < msks.size(); msk++) {
            dp[i & 1][msk] = INF, num[i & 1][msk] = 0;
        }
        for(int msk = 0; msk < msks.size(); msk++) {
            for(int ed = 0; ed < 4; ed++) {
                int nxt_msk = nxt[msk][col][ed];
                if(nxt_msk == -1) {
                    continue;
                }
                ll cur = dp[i & 1 ^ 1][msk] + (ed & 1 ? ve[row][col] : 0) + (ed & 2 ? he[row][col] : 0);
                if(cur < dp[i & 1][nxt_msk]) {
                    dp[i & 1][nxt_msk] = cur;
                    num[i & 1][nxt_msk] = num[i & 1 ^ 1][msk];
                } else if(cur == dp[i & 1][nxt_msk]) {
                    num[i & 1][nxt_msk] = (num[i & 1][nxt_msk] + num[i & 1 ^ 1][msk]) % mod;
                }
            }
        }
    }
    cout << num[(n * k - 1) & 1][0] << endl;
}