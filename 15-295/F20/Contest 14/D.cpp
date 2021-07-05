#include <bits/stdc++.h>

using namespace std;

int n, q, ans[100000], val[1000000];
vector<int> ind[1000000], words;
vector<string> ins_list;
string combined_string = "{";

struct AhoCorasick {
    const static int mxN = 1e6, sigma = 28;
    int node_count, trie[mxN][sigma], failure_link[mxN], dictionary_link[mxN];
    bool word[mxN];
    AhoCorasick() {
        memset(trie,0,sizeof(trie));
        memset(failure_link,0,sizeof(failure_link));
        memset(dictionary_link,0,sizeof(dictionary_link));
        memset(word,false,sizeof(word));
        node_count = 0;
    }
    void build(vector<string> & dict) {
        for(int i = 0; i<(int)dict.size(); i++) {
            int cur = 0;
            for(char c: dict[i]) {
                if(!trie[cur][c-'a'])
                    trie[cur][c-'a'] = ++node_count;
                cur = trie[cur][c-'a'];
            }
            if(!word[cur]) {
                words.push_back(cur);
            }
            word[cur] = true, ind[cur].push_back(i);
        }
        queue<int> q;
        q.push(0);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            dictionary_link[u] = (word[failure_link[u]] ? failure_link[u] : dictionary_link[failure_link[u]]);
            for(int i = 0; i<sigma; i++) {
                if(trie[u][i] == 0) {
                    trie[u][i] = trie[failure_link[u]][i];
                } else {
                    failure_link[trie[u][i]] = (u == 0 ? 0 : trie[failure_link[u]][i]);
                    q.push(trie[u][i]);
                }
            }
        }
    }
    void process(string qry_string) {
        int cur = 0;
        for(char c: qry_string) {
            cur = trie[cur][c-'a'];
            int dict_ver = cur;
            while(dict_ver > 0) {
                if(word[dict_ver]) {
                    val[dict_ver]++;
                }
                dict_ver = dictionary_link[dict_ver];
            }
        }
        for(int word_node: words) {
            for(int ans_ind: ind[word_node]) {
                ans[ans_ind/3] += val[word_node] * (ans_ind%3 == 2 ? -1 : 1);
            }
        }
    }
} AC;

int main() {
    cin >> n;
    for(int i = 0; i<n; i++) {
        string input;
        cin >> input;
        combined_string += (input + "|" + input + "{");
    }
    cin >> q;
    for(int i = 0; i<q; i++) {
        string pref, suff;
        cin >> pref >> suff;
        ins_list.push_back("{"+pref), ins_list.push_back(suff+"{");
        ins_list.push_back(suff+"|"+pref);
    }
    AC.build(ins_list);
    AC.process(combined_string);
    for(int i = 0; i<q; i++) {
        cout << ans[i] << endl;
    }
}