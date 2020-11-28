#include <bits/stdc++.h>

using namespace std;

int t = 5, var[4], grid[4][4], arr1[4] = {1,1,-1,-1}, arr2[4] = {-1,1,1,-1};
string in, dig = "0123456789ABCDEF";

void fill_grid()
{
    for(int i = 0; i<4; i++)
        for(int j = 0; j<4; j++)
            if((var[0]!=-arr1[j])&&(var[1]!=-arr1[i])&&(var[2]!=-arr2[j])&&(var[3]!=-arr2[i]))
                grid[i][j] = 1;
}

int main()
{
    freopen("D:/3int.txt","r",stdin);
    while(t--)
    {
        cin >> in;
        in+='+';
        for(int i = 0; i<in.length(); i++)
        {
            if(in[i]=='+')
                fill_grid(), var[0] = var[1] = var[2] = var[3] = 0;
            else if(in[i]=='~')
                var[(in[i+1]-'A')]--, i++;
            else
                var[(in[i]-'A')]++;
        }
        for(int i = 0; i<4; i++)
            cout << dig[8*grid[i][0]+4*grid[i][1]+2*grid[i][2]+grid[i][3]];
        cout << endl;
        for(int i = 0; i<16; i++)
            grid[i/4][i%4] = 0;
    }
}
