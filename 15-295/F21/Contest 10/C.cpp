#include <bits/stdc++.h>

using namespace std;

string s, t;
bool automaton_works, array_works = true;

int main() {
    cin >> s >> t;
    multiset<int> s_chars;
    for(int i = 0, j = 0; i < s.length(); i++) {
        s_chars.insert(s[i]);
        if(j < t.length() && s[i] == t[j]) {
            ++j;
        }
        if(j == t.length()) {
            automaton_works = true;
        }
    }
    for(int i = 0; i < t.length(); i++) {
        if(!s_chars.count(t[i])) {
            array_works = false;
        } else {
            s_chars.erase(s_chars.find(t[i]));
        }
    }
    if(automaton_works) {
        cout << "automaton" << endl;
    } else if(array_works && s.length() == t.length()) {
        cout << "array" << endl;
    } else if(array_works) {
        cout << "both" << endl;
    } else {
        cout << "need tree" << endl;
    }
}