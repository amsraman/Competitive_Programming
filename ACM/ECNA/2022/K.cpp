#include <bits/stdc++.h>

using namespace std;

int main() {
    string t1, t2;
    getline(cin, t1);
    getline(cin, t2);
    auto trim = [](string s) {
        string res = "";
        for(char c: s) if(c != ' ') res += c;
        return res;
    };
    t1 = trim(t1), t2 = trim(t2);
    t1 = "(-1(" + t1 + "))";
    t2 = "(-1(" + t2 + "))";
    auto tokenize = [](string s) {
        vector<string> yeet;
        string so_far = "";
        for(char c: s) {
            if(c == '(' || c == ')') {
                if(!so_far.empty()) yeet.push_back(so_far);
                so_far = "";
                so_far += c; yeet.push_back(so_far);
                so_far = "";
            } else {
                so_far += c;
            }
        }
        return yeet;
    };
    auto get_reps = [](vector<string> tok) {
        vector<pair<string, string>> res;
        stack<string> leader;
        for(string s: tok) {
            if(s == ")") {
                leader.pop();
            } else if(s != "(") {
                if(!leader.empty()) res.emplace_back(leader.top(), s);
                leader.push(s);
            }
        }
        return res;
    };
    vector<pair<string, string>> r1 = get_reps(tokenize(t1)), r2 = get_reps(tokenize(t2));
    sort(r1.begin(), r1.end());
    sort(r2.begin(), r2.end());
    cout << (r1 == r2 ? "Yes" : "No") << '\n';
}