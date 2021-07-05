/*
ID: adisund1
TASK: wissqu
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int num_left[5] = {3,3,3,4,3}, ans;
pair<int,int> dir[9] = {{0,0},{1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,-1},{-1,1}};
set<pair<int,int>> spaces_left;
vector<pair<char,pair<int,int>>> moves_made, final_moves;
string grid[4];
bool sol_found;

bool ok(int x, int y, char letter) {
    for(auto d: dir) {
        if(x+d.first >= 0 && x+d.first < 4 && y+d.second >= 0 && y+d.second < 4 && grid[x+d.first][y+d.second] == letter) {
            return false;
        }
    }
    return true;
}

void search(int num_spaces_left) {
    if(num_spaces_left == 0) {
        ++ans;
        if(!sol_found) {
            sol_found = true;
            for(auto move: moves_made) {
                final_moves.push_back(move);
            }
        }
        return;
    }
    vector<pair<int,int>> cur_spaces;
    for(auto i: spaces_left) {
        cur_spaces.push_back(i);
    }
    for(int i = 0; i<5; i++) {
        if(num_spaces_left == 16 && i != 3) {
            continue;
        }
        if(num_left[i] > 0) {
            for(auto space: cur_spaces) {
                if(ok(space.first-1,space.second-1,char('A'+i))) {
                    spaces_left.erase(space);
                    moves_made.push_back({char('A'+i),space});
                    char orig = grid[space.first-1][space.second-1];
                    grid[space.first-1][space.second-1] = char('A'+i);
                    --num_left[i];
                    search(num_spaces_left-1);
                    ++num_left[i];
                    grid[space.first-1][space.second-1] = orig;
                    moves_made.pop_back();
                    spaces_left.insert(space);
                }
            }
        }
    }
}

int main() {
    ifstream cin("wissqu.in");
    ofstream cout("wissqu.out");
    for(int i = 0; i<4; i++) {
        cin >> grid[i];
    }
    for(int i = 1; i<=4; i++) {
        for(int j = 1; j<=4; j++) {
            spaces_left.insert({i,j});
        }
    }
    search(16);
    for(auto move: final_moves) {
        cout << move.first << " " << move.second.first << " " << move.second.second << endl;
    }
    cout << ans << endl;
}