/*
ID: adisund1
TASK: cryptcow
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int cow_count[3], kmp[75];
string message, ref_message = "Begin the Escape execution at the Break of Dawn";
unordered_set<string> bad_strings;

bool is_good(char c) {
    return (c == 'C' || c == 'O' || c == 'W');
}

bool pre_chk() {
    string message_s = message;
    string ref_s = ref_message;
    for(int i = 0; i<message_s.length(); i++) {
        if(is_good(message_s[i])) {
            message_s[i] = '~';
        }
    }
    sort(message_s.begin(),message_s.end());
    sort(ref_s.begin(),ref_s.end());
    return ref_s == message_s.substr(0,47);
}

bool kmp_chk(string &s, string &t, int ind, int len) {
    for(int i = 1; i<len; i++) {
        kmp[i] = kmp[i-1];
        while(kmp[i]>0&&s[ind+i]!=s[ind+kmp[i]])
            kmp[i] = kmp[kmp[i]-1];
        if(s[ind+i]==s[ind+kmp[i]])
            ++kmp[i];
    }
    for(int i = 0, j = 0; i<t.length(); i++) {
        if(t[i] == s[ind+j]) {
            j++;
        } else {
            j = kmp[j];
        }
        if(j == len) {
            return true;
        }
    }
    return false;
}

bool search(string s, string t) {
    if(bad_strings.count(s)) {
        return false;
    }
    if(s.length() == t.length()) {
        return s == t;
    }
    int pf = 0, sf = 0;
    while(pf < t.length() && !is_good(s[pf])) {
        if(s[pf] != t[pf]) {
            return false;
        }
        ++pf;
    }
    while(pf < t.length() && !is_good(s[s.length()-sf-1])) {
        if(s[s.length()-sf-1] != t[t.length()-sf-1]) {
            return false;
        }
        ++sf;
    }
    s.erase(0,pf), t.erase(0,pf);
    s.erase(s.length()-sf,sf), t.erase(t.length()-sf,sf);
    vector<int> pos;
    for(int i = 0, j = 0; i<s.length(); i++) {
        if(!is_good(s[i]) && (i == 0 || is_good(s[i-1]))) {
            j = i;
        }
        if(!is_good(s[i]) && (i == s.length()-1 || is_good(s[i+1])) && !kmp_chk(s,t,j,i-j+1)) {
            return false;
        }
        if(is_good(s[i])) {
            pos.push_back(i);
        }
    }
    if(s[pos[0]] != 'C' || s[pos.back()] != 'W') {
        return false;
    }
    for(int i = 0; i<pos.size(); i++) if(s[pos[i]] == 'O') {
            for(int j = i-1; j<pos.size(); j--) if(s[pos[j]] == 'C') {
                    for(int k = i+1; k<pos.size(); k++) if(s[pos[k]] == 'W') {
                            int pos0 = pos[j], pos1 = pos[i], pos2 = pos[k];
                            if(search(s.substr(0,pos0)+s.substr(pos1+1,pos2-pos1-1)+s.substr(pos0+1,pos1-pos0-1)+s.substr(pos2+1,s.length()-pos2-1),t)) {
                                return true;
                            }
                        }
                }
        }
    bad_strings.insert(s);
    return false;
}

int main() {
    ifstream cin("cryptcow.in");
    ofstream cout("cryptcow.out");
    getline(cin,message);
    for(char c: message) {
        if(c == 'C') {
            ++cow_count[0];
        } else if(c == 'O') {
            ++cow_count[1];
        } else if (c == 'W') {
            ++cow_count[2];
        }
    }
    if(cow_count[0] != cow_count[1] || cow_count[0] != cow_count[2] || 3*cow_count[0]+47 != message.length() || !pre_chk()) {
        cout << "0 0" << endl;
    } else if(search(message,ref_message)) {
        cout << 1 << " " << cow_count[0] << endl;
    } else {
        cout << "0 0" << endl;
    }
}
