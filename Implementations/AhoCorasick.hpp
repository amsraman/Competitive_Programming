struct AhoCorasick {
    const static int sigma = 26;
    int dict_size, node_count = 0;
    vector<int> failure_link, dictionary_link, end_point;
    vector<array<int, sigma>> trie;
    vector<bool> terminal;
    AhoCorasick(const vector<string> & dict): dict_size((int) dict.size()), end_point((int) dict.size()) {
        build(dict);
    }
    void create_new_node() {
        failure_link.push_back(0), dictionary_link.push_back(0), terminal.push_back(false);
        array<int, sigma> trie_node;
        trie_node.fill(0);
        trie.push_back(trie_node);
        node_count++;
    }
    void build(const vector<string> & dict) {
        create_new_node();
        for(int i = 0; i < (int) dict.size(); i++) {
            int cur = 0;
            for(char c: dict[i]) {
                if(!trie[cur][c - 'a']) {
                    trie[cur][c - 'a'] = node_count;
                    create_new_node();
                }
                cur = trie[cur][c - 'a'];
            }
            terminal[cur] = true; end_point[i] = cur;
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
    void process(const string & qry_string) { // modify this ig
        int cur = 0, num_matches = 0;
        vector<bool> hit(node_count, false);
        for(char c: qry_string) {
            cur = trie[cur][c - 'a'];
            int dict_ver = cur;
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