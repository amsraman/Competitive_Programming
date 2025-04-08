#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n; cin >> n;
	while(n > 0) {
		vector<pair<int, int>> p1, p2;
		set<pair<int, int>> edges;
		map<string, int> i1, i2;
		vector<string> r1, r2;
		int c1 = 0, c2 = 0;
		for(int i = 0; i < n; i++) {
			string w1, w2; cin >> w1 >> w2;
			if(!i1.count(w1)) i1[w1] = c1++, r1.push_back(w1);
			if(!i1.count(w2)) i1[w2] = c1++, r1.push_back(w2);
			p1.emplace_back(i1[w1], i1[w2]);
		}
		for(int i = 0; i < n; i++) {
			string w1, w2; cin >> w1 >> w2;
			if(!i2.count(w1)) i2[w1] = c2++, r2.push_back(w1);
			if(!i2.count(w2)) i2[w2] = c2++, r2.push_back(w2);
			p2.emplace_back(i2[w1], i2[w2]);
			edges.insert(p2.back());
		}
		map<pair<int, int>, set<int>> g2;
		vector<pair<int, int>> g1(c1);
		assert(c1 == c2);
		vector<int> id1(c1, 0), od1(c1, 0), id2(c1, 0), od2(c1, 0);
		for(auto [u, v]: p1) {
			++id1[u], ++od1[v];
		}
		for(auto [u, v]: p2) {
			++id2[u], ++od2[v];
		}
        vector<vector<pair<int, int>>> adj_edges(c1);
        for(auto [u, v]: p1) {
            adj_edges[v].emplace_back(u, v);
            adj_edges[u].emplace_back(u, v);
        }
		for(int i = 0; i < c1; i++) {
			pair<int, int> u1 = make_pair(id1[i], od1[i]);
			pair<int, int> u2 = make_pair(id2[i], od2[i]);
            g1[i] = u1; g2[u2].insert(i);
		}
		vector<int> mapping(c1, -1);
		vector<pair<string, string>> res;
		auto gen = [&](auto rec, int lev) {
			if(lev == c1) { // should be isomorphic
				for(int i = 0; i < c1; i++) {
					res.emplace_back(r1[i], r2[mapping[i]]);
				}
				return;
			}
            auto pos_matches = g2[g1[lev]];
            for(int mt: pos_matches) {
                bool good = true;
                mapping[lev] = mt;
                for(auto [u, v]: adj_edges[lev]) {
                    if(max(u, v) == lev && !edges.count({mapping[u], mapping[v]})) {
                        good = false;
                        break;
                    }
                }
                if(good) {
                    g2[g1[lev]].erase(mt);
                    rec(rec, lev + 1);
                    if(!res.empty()) return;
                    g2[g1[lev]].insert(mt);
                }
            }
		};
		gen(gen, 0);
		sort(res.begin(), res.end());
		for(auto [w1, w2]: res) {
			cout << w1 << '/' << w2 << '\n';
		}
		cout << '\n';
		cin >> n;
	}
}