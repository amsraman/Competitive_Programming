#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for(int _ = 1; _ <= n; _++) {
        vector<tuple<int, int, int>> cur;
        set<pair<int, int>> unused;
        for(int i = 1; i <= 6; i++) {
            for(int j = i; j <= 6; j++) {
                unused.insert({i, j});
            }
        }
        for(int i = 0; i < 13; i++) {
            char tp; cin >> tp;
            if(tp == 'H') {
                int n1, n2; cin >> n1 >> n2; cur.emplace_back(0, n1, n2);
                if(n1 > n2) swap(n1, n2);
                unused.erase({n1, n2});
            } else if(tp == 'V') {
                int n1, n2; cin >> n1 >> n2; cur.emplace_back(1, n1, n2);
                if(n1 > n2) swap(n1, n2);
                unused.erase({n1, n2});
            } else {
                int n1; cin >> n1; cur.emplace_back(2, n1, n1);
            }
        }
        vector<vector<int>> board(5, vector<int>(5, -1)); int ans = 0; bool yahtzee = false;
        auto score_vector = [&](vector<int> vec) {
            sort(vec.begin(), vec.end());
            auto dist = vec; dist.erase(unique(dist.begin(), dist.end()), dist.end());
            if(vec[0] == vec[4]) {
                if(!yahtzee) {
                    yahtzee = true;
                    return 50;
                }
                return 100;
            } else if(dist.size() == 5 && dist[0] + 4 == dist[4]) {
                return 40;
            } else if((dist.size() >= 4 && dist[0] + 3 == dist[3]) || (dist.size() == 5 && dist[1] + 3 == dist[4])) {
                return 30;
            } else if((vec[0] == vec[2] && vec[3] == vec[4]) || (vec[0] == vec[1] && vec[2] == vec[4])) {
                return 25;
            } else if(vec[0] == vec[3] || vec[1] == vec[4]) {
                return 4 * vec[2];
            } else if(vec[0] == vec[2] || vec[1] == vec[3] || vec[2] == vec[4]) {
                return 3 * vec[2];
            }
            return 0;
        };
        auto try_cards = [&]() {
            for(int i = 0; i < 5; i++) fill(board[i].begin(), board[i].end(), -1);
            for(auto [tp, n1, n2]: cur) {
                bool fd = false;
                for(int i = 0; i < 5; i++) {
                    for(int j = 0; j < 5; j++) {
                        if(board[i][j] != -1) continue;
                        if(tp == 0 && j < 4 && board[i][j + 1] == -1) {
                            board[i][j] = n1, board[i][j + 1] = n2; fd = true;
                            break;
                        }
                        if(tp == 1 && i < 4 && board[i + 1][j] == -1) {
                            board[i][j] = n1, board[i + 1][j] = n2; fd = true;
                            break;
                        }
                        if(tp == 2) {
                            board[i][j] = n1; fd = true;
                            break;
                        }
                    }
                    if(fd) break;
                }
                if(!fd) return;
            }
            int score = 0; vector<int> diag; yahtzee = false;
            for(int i = 0; i < 5; i++) diag.push_back(board[i][i]);
            score += score_vector(diag);
            diag.clear();
            for(int i = 0; i < 5; i++) diag.push_back(board[i][4 - i]);
            score += score_vector(diag);
            for(int i = 0; i < 5; i++) score += score_vector(board[i]);
            for(int i = 0; i < 5; i++) {
                for(int j = 0; j < i; j++) {
                    swap(board[i][j], board[j][i]);
                }
            }
            for(int i = 0; i < 5; i++) score += score_vector(board[i]);
            ans = max(ans, score);
        };
        try_cards();
        for(int i = 0; i < 13; i++) {
            auto [tp, n1, n2] = cur[i];
            if(tp == 2) continue;
            for(auto [in1, in2]: unused) {
                cur[i] = make_tuple(tp, in1, in2);
                try_cards();
                cur[i] = make_tuple(tp, in2, in1);
                try_cards();
            }
            cur[i] = make_tuple(tp, n1, n2);
        }
        cout << "Case " << _ << ": " << ans << '\n';
    }
}