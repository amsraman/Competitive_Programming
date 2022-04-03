#include <bits/stdc++.h>

using namespace std;

int n;
string words[100000], enc, st;

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> words[i];
    }
    cin >> enc;
    st = "<3";
    for(int i = 0; i < n; i++) {
        st += words[i] + "<3";
    }
    int le = enc.length(), ls = st.length();
    int pf = 0;
    for(int i = 0; i < le; i++) {
        if(pf < ls && enc[i] == st[pf]) {
            ++pf;
        }
    }
    cout << (pf == ls ? "yes" : "no") << endl;
}