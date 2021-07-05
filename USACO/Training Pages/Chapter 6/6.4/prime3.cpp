/*
ID: adisund1
TASK: prime3
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int first_dig, sum;
set<int> usable_primes;
vector<int> first_col[10], last_col[10], ends_fixed[10][10], mid_fixed[10][10][10];
array<array<int,5>,5> cur;
set<array<array<int,5>,5>> ans;

bool isPrime(int x) {
    for(int i = 2; i*i<=x; i++)
        if(x%i == 0)
            return false;
    return true;
}

int sum_dig(int x) {
    int ret = 0;
    while(x > 0)
        ret += x%10, x /= 10;
    return ret;
}

bool chk_digs(int x, bool type) {
    bool ret = true;
    while(x > 0) {
        ret &= ((!type && (x%10 != 0)) || (type && (x%2 == 1 && x%10 != 5)));
        x /= 10;
    }
    return ret;
}

int get_row(int x, bool row, int inc = 0) {
    int ret = 0;
    for(int i = 0; i<5; i++)
        ret = ret*10+(row ? cur[x+inc*i][i] : cur[i][x]);
    return ret;
}

void row_fill(int x, int num, bool row) {
    for(int i = 4; i>=0; i--, num/=10) {
        if(row)
            cur[x][i] = num%10;
        else
            cur[i][x] = num%10;
    }
}

int main() {
    ifstream cin("prime3.in");
    ofstream cout("prime3.out");
    cin >> sum >> first_dig;
    for(int i = 10000; i<100000; i++)
        if(isPrime(i) && sum_dig(i) == sum) {
            usable_primes.insert(i);
            if((i/10000 == first_dig) && chk_digs(i,0))
                first_col[i%10].push_back(i);
            if(chk_digs(i,1))
                last_col[i%10].push_back(i);
            ends_fixed[i/10000][i%10].push_back(i);
            mid_fixed[i/10000][(i/100)%10][i%10].push_back(i);
        }
    for(int i: {1,3,7,9})
        for(int lst1: last_col[i]) {
            row_fill(4,lst1,true);
            for(int lst2: last_col[i]) {
                row_fill(4,lst2,false);
                for(int fst1: first_col[lst2/10000]) {
                    row_fill(0,fst1,true);
                    for(int fst2: first_col[lst1/10000]) {
                        row_fill(0,fst2,false);
                        for(int mid = 0; mid<10; mid++) {
                            if(mid + max(cur[0][0]+cur[4][4],cur[0][4]+cur[4][0]) > sum)
                                continue;
                            for(int mid_col: mid_fixed[cur[0][2]][mid][cur[4][2]]) {
                                row_fill(2,mid_col,false);
                                for(int mid_row: mid_fixed[cur[2][0]][mid][cur[2][4]]) {
                                    row_fill(2,mid_row,true);
                                    int row_sum1 = cur[0][1]+cur[2][1]+cur[4][1], row_sum2 = cur[0][3]+cur[2][3]+cur[4][3];
                                    int col_sum1 = cur[1][0]+cur[1][2]+cur[1][4], col_sum2 = cur[3][0]+cur[3][2]+cur[3][4];
                                    int lower_bound = row_sum2 - col_sum1, upper_bound = sum - max(row_sum1,col_sum1);
                                    for(int corner = max(0,lower_bound); corner<=min(9,upper_bound); corner++) {
                                        cur[1][1] = corner;
                                        cur[1][3] = sum - cur[1][0] - cur[1][1] - cur[1][2] - cur[1][4];
                                        cur[3][1] = sum - cur[0][1] - cur[1][1] - cur[2][1] - cur[4][1];
                                        cur[3][3] = sum - cur[3][0] - cur[3][1] - cur[3][2] - cur[3][4];
                                        int diag1 = cur[0][0] + cur[1][1] + cur[2][2] + cur[3][3] + cur[4][4];
                                        int diag2 = cur[0][4] + cur[1][3] + cur[2][2] + cur[3][1] + cur[4][0];
                                        if(diag1 != sum || diag2 != sum)
                                            continue;
                                        if(usable_primes.count(get_row(1,false)) && usable_primes.count(get_row(1,true)) && usable_primes.count(get_row(3,false)) 
                                            && usable_primes.count(get_row(3,true)) && usable_primes.count(get_row(0,true,1)) && usable_primes.count(get_row(4,true,-1)))
                                            ans.insert(cur);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    if(ans.empty())
        cout << "NONE" << '\n';
    int done = false;
    for(auto board: ans) {
        if(done)
            cout << '\n';
        done = true;
        for(int i = 0; i<5; i++) {
            for(int j = 0; j<5; j++)
                cout << board[i][j];
            cout << '\n';
        }
    }
}