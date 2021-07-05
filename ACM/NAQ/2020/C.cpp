#include <bits/stdc++.h>

using namespace std;

int num;
string board[8];
set<int> row, col, diag1, diag2;
bool valid = true;

int main()
{
    for(int i = 0; i<8; i++)
        cin >> board[i];
    for(int i = 0; i<8; i++)    
        for(int j = 0; j<8; j++)
            if(board[i][j]=='*')
            {
                ++num;
                if(row.count(i)||col.count(j)||diag1.count(i-j)||diag2.count(i+j))
                    valid = false;
                row.insert(i);
                col.insert(j);
                diag1.insert(i-j);
                diag2.insert(i+j);
            }
    valid&=(num==8);
    cout << (valid?"valid":"invalid") << endl;
}