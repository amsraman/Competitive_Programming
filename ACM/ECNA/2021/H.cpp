#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int r, c, t; cin >> r >> c;
	vector<vector<char>> grid(max(r, c), vector<char>(max(r, c)));
	vector<vector<int>> benefits(max(r, c), vector<int>(max(r, c), 0));
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			cin >> grid[i][j];
			if(grid[i][j] == 'd') benefits[i][j] = -2;
			if(grid[i][j] == 't') benefits[i][j] = -3;
			if(grid[i][j] == 'D') benefits[i][j] = 2;
			if(grid[i][j] == 'T') benefits[i][j] = 3;
            if(isdigit(grid[i][j])) benefits[i][j] = 1;
		}
	}
	cin >> t;
	vector<int> tiles(t);
	for(int i = 0; i < t; i++) {
		cin >> tiles[i];
	}
	sort(tiles.begin(), tiles.end());
	int ans = 0;
    auto filled = [&](int x, int y) {
        return (x >= 0 && x < r && y >= 0 && y < c && isdigit(grid[x][y]));
    };
	auto score = [&](int x, int y) { // takes in some inner point
		int res = 0, hcur = 0, hmult = 1, hmode = 2; bool con = false;
        while(filled(x, y - 1)) --y;
        for(int i = y; i < c; i++) {
            if(!isdigit(grid[x][i])) break;
            int add = grid[x][i] - '0';
            if(benefits[x][i] < 0) add *= abs(benefits[x][i]);
            if(benefits[x][i] > 0) hmult *= benefits[x][i];
            hcur += add;
            if(filled(x - 1, i) || filled(x + 1, i)) con = true;
            if(i > y && grid[x][i] != grid[x][i - 1]) {
                if(hmode != 2 && ((grid[x][i] > grid[x][i - 1]) ^ hmode)) return -1;
                hmode = grid[x][i] > grid[x][i - 1];
            }
            if(benefits[x][i] == 1) {
                con = true; continue;
            }
            int p1 = x, p2 = x;
            while(filled(p1 - 1, i)) --p1;
            while(filled(p2 + 1, i)) ++p2;
            if(p1 == x && p2 == x) continue;
            int vcur = 0, vmult = 1, vmode = 2;
            for(int j = p1; j <= p2; j++) {
                if(j > p1 && grid[j - 1][i] != grid[j][i]) {
                    if(vmode != 2 && ((grid[j][i] > grid[j - 1][i]) ^ vmode)) return -1;
                    vmode = grid[j][i] > grid[j - 1][i];
                }
                int add = grid[j][i] - '0';
                if(benefits[j][i] < 0) add *= abs(benefits[j][i]);
                if(benefits[j][i] > 0) vmult *= benefits[j][i];
                vcur += add;
            }
            if((vcur * vmult) % 3 != 0) return -1;
            res += vcur * vmult;
        }
        if((hcur * hmult) % 3 != 0) return -1;
        if(!filled(x, y + 1)) return 0;
		return (con ? res + hcur * hmult : -1);
	};
	for(int _ = 0; _ < 4; _++) {
		for(int i = 0; i < r; i++) {
			vector<int> pos;
			for(int j = 0; j < c; j++) {
				if(!filled(i, j)) {
					pos.push_back(j);
				}
			}
			for(int j = 0; j < pos.size(); j++) {
				for(int msk = 1; msk < (1 << t); msk++) {
					int sz = __builtin_popcount(msk);
                    if(sz == 1 && !filled(i, pos[j] - 1) && !filled(i, pos[j] + 1)) continue;
					if(j + sz > pos.size()) continue;
					for(int k = 0, at = 0; k < t; k++) {
						if((msk >> k) & 1) grid[i][pos[j + at++]] = char('0' + tiles[k]);
					}
					ans = max(ans, score(i, pos[j]));
                    for(int k = 0, at = 0; k < t; k++) {
                        if((msk >> k) & 1) grid[i][pos[j + at++]] = '-';
                    }
				}
			}
		}
		for(int i = 0; i < r; i++) {
			for(int j = 0, k = c - 1; j < k; j++, k--) {
				swap(grid[i][j], grid[i][k]);
                swap(benefits[i][j], benefits[i][k]);
			}
		}
        if(_ != 1) continue;
		for(int i = 0; i < max(r, c); i++) {
			for(int j = 0; j < i; j++) {
				swap(grid[i][j], grid[j][i]);
				swap(benefits[i][j], benefits[j][i]);
			}
		}
		swap(r, c);
	}
	cout << ans << '\n';
} // piece of shit problem. my submission count possibly unearths the biggest skill issue of all time