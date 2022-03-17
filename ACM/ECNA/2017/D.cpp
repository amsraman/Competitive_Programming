#include <bits/stdc++.h>

using namespace std;

int n, k;

int main() {
    cin >> n >> k;
    stack<int> st;
    for(int i = 0; i < k; i++) {
        string comm;
        cin >> comm;
        if(comm == "undo") {
            int num;
            cin >> num;
            for(int j = 0; j < num; j++) {
                st.pop();
            }
        } else {
            st.push(atoi(comm.c_str()));
        }
    }
    int cur = 0;
    while(!st.empty()) {
        int md = st.top() % n;
        if(md < 0) {
            md += n;
        }
        cur = (cur + md) % n;
        st.pop();
    }
    cout << cur << endl;
}