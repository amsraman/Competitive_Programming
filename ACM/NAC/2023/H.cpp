#include <bits/stdc++.h>

using namespace std;

using fl = long double;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<vector<fl>> prb_win(1 << k, vector<fl>(k, 0));
    for(int msk = 1; msk < 1 << k; msk++) {
        for(int win_level = 0; win_level <= 2 * k; win_level++) {
            for(int win_msk = msk; win_msk > 0; win_msk = (win_msk - 1) & msk) {
                fl prb_follow = 1; int num_win = __builtin_popcount(win_msk);
                for(int player = 0; player < k; player++) {
                    if(!((msk >> player) & 1)) continue;
                    if((win_msk >> player) & 1) {
                        prb_follow *= (fl) (player <= win_level && win_level < (player + k)) / k;
                    } else {
                        prb_follow *= (fl) max(0, player + k - max(player, win_level + 1)) / k;
                    }
                }
                for(int player = 0; player < k; player++) {
                    if((win_msk >> player) & 1) {
                        prb_win[msk][player] += prb_follow / num_win;
                    }
                }
            }
        }
    }
    vector<vector<vector<fl>>> prb_second(k, vector<vector<fl>>(1 << k, vector<fl>(k + 1, 0)));
    for(int gap = 0; gap < k; gap++) {
        for(int msk = 1; msk < 1 << k; msk++) {
            // Case 1: There is a unique winner block
            for(int winner = 0; winner <= k; winner++) {
                if(winner > 0 && !((msk >> (winner - 1)) & 1)) continue;
                int all = (2 * msk + 1) ^ (1 << winner), fst = 1;
                while(!(((2 * msk + 1) >> fst) & 1)) ++fst;
                for(int second_msk = all; second_msk > 0; second_msk = (second_msk - 1) & all) {
                    int winner_base = winner == 0 ? 0 : (gap + winner - fst + 1);
                    for(int second_level = 1; second_level <= 2 * k; second_level++) {
                        fl prb_follow = 1; int num_second = __builtin_popcount(second_msk);
                        for(int player = 0; player <= k; player++) {
                            if(player > 0 && !((msk >> (player - 1)) & 1)) continue;
                            int cur_base = (player == 0 ? 0 : (gap + player - fst + 1));
                            if((second_msk >> player) & 1) {
                                prb_follow *= (fl) (cur_base <= second_level && second_level < cur_base + k) / k;
                            } else if(player == winner) {
                                prb_follow *= (fl) max(0, min(winner_base + k, second_level) - winner_base) / k;
                            } else {
                                prb_follow *= (fl) max(0, cur_base + k - max(cur_base, second_level + 1)) / k;
                            }
                        }
                        for(int player = 0; player <= k; player++) {
                            if((second_msk >> player) & 1) {
                                prb_second[gap][msk][player] += prb_follow / num_second;
                            }
                        }
                    }
                }
            }
            // Case 2: Multiple people tie for a winner block
            int all = 2 * msk + 1, fst = 1;
            while(!((all >> fst) & 1)) ++fst;
            for(int win_msk = all; win_msk > 0; win_msk = (win_msk - 1) & all) {
                int num_win = __builtin_popcount(win_msk);
                if(num_win < 2) continue;
                for(int win_level = 0; win_level <= 2 * k; win_level++) {
                    fl prb_follow = 1;
                    for(int player = 0; player <= k; player++) {
                        if(player > 0 && !((msk >> (player - 1)) & 1)) continue;
                        int cur_base = player == 0 ? 0 : (gap + player - fst + 1);
                        if((win_msk >> player) & 1) {
                            prb_follow *= (fl) (cur_base <= win_level && win_level < (cur_base + k)) / k;
                        } else {
                            prb_follow *= (fl) max(0, cur_base + k - max(cur_base, win_level + 1)) / k;
                        }
                    }
                    for(int player = 0; player <= k; player++) {
                        if((win_msk >> player) & 1) {
                            prb_second[gap][msk][player] += prb_follow / num_win;
                        }
                    }
                }
            }
        }
    }
    int base_below = max(0, n - k - 1);
    vector<vector<vector<fl>>> dp1(base_below + 1, vector<vector<fl>>(k, vector<fl>(1 << k, 0)));
    vector<vector<fl>> dp2(base_below + 1, vector<fl>(1 << k, 0));
    vector<fl> res(n, 0);
    if(n >= k + 1) {
        dp1[base_below][0][(1 << k) - 1] = 1;
    } else {
        int all = (1 << k) - 1;
        dp1[0][0][(all << (k + 1 - n)) & all] = 1;
    }
    for(int num_below = base_below; num_below >= 0; num_below--) {
        for(int msk = (1 << k) - 1; msk > 0; msk--) {
            for(int gap = 0; gap < k; gap++) {
                int fst = 0, len = __builtin_popcount(msk);
                while(!((msk >> fst) & 1)) ++fst;
                int snd = fst + 1;
                while(snd < k && !((msk >> snd) & 1)) ++snd;
                for(int elim = 0; elim <= k; elim++) {
                    if(elim > 0 && !((msk >> (elim - 1)) & 1)) continue;
                    int pl = elim == 0 ? (num_below + (k - fst) + gap) : (num_below + k - elim);
                    if(pl < n) {
                        res[pl] += dp1[num_below][gap][msk] * prb_second[gap][msk][elim] * (num_below + len);
                    }
                    int new_below = num_below, new_gap = gap, new_state = msk;
                    if(elim == 0) {
                        if(snd == k && num_below == 0) continue;
                        new_gap = snd - fst - 1, new_state ^= (1 << fst);
                    } else if(elim == fst + 1) {
                        if(snd == k && num_below == 0) continue;
                        new_gap += snd - fst, new_state ^= (1 << fst);
                    } else {
                        new_state ^= (1 << (elim - 1));
                    }
                    while(new_state % 2 == 0 && new_below > 0) {
                        new_state = (new_state / 2 + (1 << (k - 1)));
                        --new_below;
                    }
                    if(new_gap < k) {
                        dp1[new_below][new_gap][new_state] += dp1[num_below][gap][msk] * prb_second[gap][msk][elim];
                    } else {
                        dp2[new_below][new_state] += dp1[num_below][gap][msk] * prb_second[gap][msk][elim];
                    }
                }
            }
        }
        for(int msk = (1 << k) - 1; msk > 0; msk--) {
            for(int elim = 0; elim < k; elim++) {
                if(!((msk >> elim) & 1)) continue;
                int new_state = msk ^ (1 << elim), new_below = num_below, len = __builtin_popcount(msk);
                while(new_state % 2 == 0 && new_below > 0) {
                    new_state = (new_state / 2 + (1 << (k - 1)));
                    --new_below;
                }
                int pl = num_below + (k - elim - 1);
                if(pl < n) {
                    res[pl] += dp2[num_below][msk] * prb_win[msk][elim] * (num_below + len);
                }
                dp2[new_below][new_state] += dp2[num_below][msk] * prb_win[msk][elim];
            }
        }
    }
    cout << fixed << setprecision(9);
    for(int i = 0; i < n; i++) {
        cout << res[i] + 1 << '\n';
    }
}
/*
k > n?
*/