#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, nxt[1000000][2], cnt[1000000], nc;

void ins(string x) {
    int cur_node = 0;
    for(char c: x) {
        int num = (c - '0');
        if(num & 1 ^ 1) {
            if(nxt[cur_node][0] == 0) {
                nxt[cur_node][0] = ++nc;
            }
            cur_node = nxt[cur_node][0];
        } else {
            if(nxt[cur_node][1] == 0) {
                nxt[cur_node][1] = ++nc;
            }
            cur_node = nxt[cur_node][1];
        }
    }
    ++cnt[cur_node];
}

void rem(string x) {
    int cur_node = 0;
    for(char c: x) {
        int num = (c - '0');
        if(num & 1 ^ 1) {
            cur_node = nxt[cur_node][0];
        } else {
            cur_node = nxt[cur_node][1];
        }
    }
    --cnt[cur_node];
}

int main() {
    cin >> t;
    char op;
    string num;
    for(int i = 0; i < t; i++) {
        cin >> op;
        if(op == '+') {
            cin >> num;
            reverse(num.begin(), num.end());
            while(num.length() <= 18) {
                num += '0';
            }
            ins(num);
        } else if(op == '-') {
            cin >> num;
            reverse(num.begin(), num.end());
            while(num.length() <= 18) {
                num += '0';
            }
            rem(num);
        } else {
            string pat;
            cin >> pat;
            reverse(pat.begin(), pat.end());
            while(pat.length() <= 18) {
                pat += '0';
            }
            reverse(pat.begin(), pat.end());
            int cur_node = 0;
            int ans = cnt[0];
            for(char c: pat) {
                if(nxt[cur_node][(c - '0')] == 0) {
                    nxt[cur_node][(c - '0')] = ++nc;
                }
                cur_node = nxt[cur_node][(c - '0')];
                ans += cnt[cur_node];
            }
            cout << ans << endl;
        }
    }
}