/*
ID: adisund1
TASK: clocks
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int arr[9], init, dist[(1<<18)];
string moves[9] = {"ABDE","ABC","BCEF","ADG","BDEFH","CFI","DEGH","GHI","EFHI"};
bool vis[(1<<18)];
vector<int> ans;

int inc_bit(int state, int loc, int num) {
    int cur_bit = ((state & ((1 << (2 * loc + 1)) + (1 << (2 * loc)))) >> (2*loc));
    int new_bit = (cur_bit + num) % 4;
    state += (new_bit - cur_bit) * (1 << (2 * loc));
    return state;
}

int app_move(int state, int move, int num) {
    for(char c: moves[move]) {
        state = inc_bit(state,8-c+'A',num);
    }
    return state;
}

int main() {
    ifstream cin("clocks.in");
    ofstream cout("clocks.out");
    for(int i = 0; i<9; i++) {
        cin >> arr[i];
        init = 4 * init + (arr[i] / 3) % 4;
    }
    queue<int> q;
    q.push(0), vis[0] = true;
    while(!q.empty()) {
        int cur_state = q.front();
        q.pop();
        for(int i = 0; i<9; i++) {
            int nxt_state = app_move(cur_state,i,3);
            if(!vis[nxt_state]) {
                dist[nxt_state] = dist[cur_state] + 1;
                q.push(nxt_state);
                vis[nxt_state] = true;
            }
        }
    }
    while(init != 0) {
        for(int i = 0; i<9; i++) {
            int nxt_state = app_move(init,i,1);
            if(dist[nxt_state] == dist[init] - 1) {
                init = nxt_state;
                ans.push_back(i+1);
                break;
            }
        }
    }
    for(int i = 0; i<ans.size(); i++) {
        if(i > 0) {
            cout << " ";
        }
        cout << ans[i];
    }
    cout << endl;
}