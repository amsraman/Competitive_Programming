#include <bits/stdc++.h>

using namespace std;

int n, m, mp[300000], val[300000], sus[400000];
vector<string> names;
multiset<int> sus_set[400000];
// LOL when the imposter is sus tfw

struct AhoCorasick {
    const static int sigma = 26;

    size_t node_count;
    vector<size_t> failure_link, dictionary_link;
    vector<array<size_t, sigma>> trie;
    vector<bool> terminal;

    AhoCorasick(vector<string> & dict) {
        node_count = 0;
        build(dict);
    }

    void create_new_node() {
        failure_link.push_back(0), dictionary_link.push_back(0), terminal.push_back(false);
        array<size_t, sigma> trie_node;
        trie_node.fill(0);
        trie.push_back(trie_node);
        node_count++;
    }

    void build(vector<string> & dict) {
        create_new_node();
        for(size_t i = 0; i < dict.size(); i++) {
            size_t cur = 0;
            for(char c: dict[i]) {
                if(!trie[cur][c - 'a']) {
                    trie[cur][c - 'a'] = node_count;
                    create_new_node();
                }
                cur = trie[cur][c - 'a'];
            }
            terminal[cur] = true;
            mp[i] = cur;
            sus_set[cur].insert(0);
        }
        queue<int> q; q.push(0);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            dictionary_link[u] = (terminal[failure_link[u]] ? failure_link[u] : dictionary_link[failure_link[u]]);
            for(int i = 0; i < sigma; i++) {
                if(trie[u][i] == 0) {
                    trie[u][i] = trie[failure_link[u]][i];
                } else {
                    failure_link[trie[u][i]] = (u == 0 ? 0 : trie[failure_link[u]][i]);
                    q.push(trie[u][i]);
                }
            }
        }
    }

    int qry(string qry_string) {
        size_t cur = 0;
        int ret = -1;
        for(char c: qry_string) {
            cur = trie[cur][c - 'a'];
            size_t dict_ver = cur;
            while(dict_ver > 0) {
                if(terminal[dict_ver]) {
                    ret = max(ret, sus[dict_ver]);
                }
                dict_ver = dictionary_link[dict_ver];
            }
        }
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    names.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> names[i];
    }
    AhoCorasick dbms(names);
    for(int i = 0, tp; i < m; i++) {
        cin >> tp;
        if(tp == 1) {
            int v, x;
            cin >> v >> x;
            int trie_ind = mp[v - 1];
            sus_set[trie_ind].erase(sus_set[trie_ind].find(val[v - 1]));
            val[v - 1] = x;
            sus_set[trie_ind].insert(val[v - 1]);
            sus[mp[v - 1]] = *(--sus_set[trie_ind].end());
        } else {
            string q;
            cin >> q;
            cout << dbms.qry(q) << '\n';
        }
    }
}