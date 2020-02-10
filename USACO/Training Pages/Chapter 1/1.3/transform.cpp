/*
ID: adityasund1
TASK: transform
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int n;
char in[10][10], trans[10][10];

bool check(int a, int b)
{
    int temp[10][10];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            temp[i][j] = in[i][j];
    if(a)
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                temp[i][j] = in[i][n-j-1];
    for(int i = 0; i<b; i++)
    {
        int temp2[10][10];
        for(int j = 0; j<n; j++)
            for(int k = 0; k<n; k++)
                temp2[j][k] = temp[j][k];
        for(int j = 0; j<n; j++)
            for(int k = 0; k<n; k++)
                temp[k][n-j-1] = temp2[j][k];
    }
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            if(temp[i][j]!=trans[i][j])
                return false;
    return true;
}

int main()
{
    freopen("transform.in","r",stdin);
    freopen("transform.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> in[i][j];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> trans[i][j];
    if(check(0,1))
        cout << 1 << endl;
    else if(check(0,2))
        cout << 2 << endl;
    else if(check(0,3))
        cout << 3 << endl;
    else if(check(1,0))
        cout << 4 << endl;
    else if(check(1,1)||check(1,2)||check(1,3))
        cout << 5 << endl;
    else if(check(0,0))
        cout << 6 << endl;
    else
        cout << 7 << endl;
}
