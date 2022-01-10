#include <bits/stdc++.h>

using namespace std;

int n, q, k[200000], rf[200000], sz[200000];
string s;
pair<string, int> ord[200000];
vector<int> matches[200000];

struct AhoCorasick {
    const static int sigma = 26;

    size_t node_count;
    vector<size_t> failure_link, dictionary_link;
    vector<array<size_t, sigma>> trie;
    vector<int> terminal;

    AhoCorasick(vector<string> & dict) {
        node_count = 0;
        build(dict);
    }

    void create_new_node() {
        failure_link.push_back(0), dictionary_link.push_back(0), terminal.push_back(0);
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
            terminal[cur] = i + 1;
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

    int process(string qry_string) {
        size_t cur = 0;
        int num_matches = 0, pos = 0;
        for(char c: qry_string) {
            cur = trie[cur][c - 'a'], ++pos;
            size_t dict_ver = cur;
            while(dict_ver > 0) {
                if(terminal[dict_ver] > 0) {
                    matches[terminal[dict_ver] - 1].push_back(pos);
                }
                dict_ver = dictionary_link[dict_ver];
            }
        }
        return num_matches;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> s >> q;
    for(int i = 0; i < q; i++) {
        cin >> ord[i].first >> k[i];
        ord[i].second = i;
        sz[i] = ord[i].first.length();
    }
    sort(ord, ord + q);
    vector<string> dict;
    for(int i = 0; i < q; i++) {
        if(i == 0 || ord[i].first != ord[i - 1].first) {
            dict.push_back(ord[i].first);
        }
        rf[ord[i].second] = dict.size() - 1;
    }
    AhoCorasick ac(dict);
    ac.process(s);
    for(int i = 0; i < q; i++) {
        if(matches[rf[i]].size() < k[i]) {
            cout << "-1\n";
        } else {
            cout << matches[rf[i]][k[i] - 1] - sz[i] + 1 << '\n';
        }
    }
}