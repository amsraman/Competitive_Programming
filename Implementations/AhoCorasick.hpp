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
        // There's many different things you can do with an AC automaton :P
        // Guess I'll just display a basic example that counts the number of dictionary matches
        size_t cur = 0;
        int num_matches = 0;
        for(char c: qry_string) {
            cur = trie[cur][c - 'a'];
            size_t dict_ver = cur;
            while(dict_ver > 0) {
                if(terminal[dict_ver]) {
                    ++num_matches;
                }
                dict_ver = dictionary_link[dict_ver];
            }
        }
        return num_matches;
    }
};