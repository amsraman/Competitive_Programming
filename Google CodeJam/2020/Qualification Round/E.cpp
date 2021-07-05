#include <bits/stdc++.h>

using namespace std;

int t, n, k, ans[50][50];
bool row_taken[50][50];

void switch_num(int a, int b)
{
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
        {
            if(ans[i][j]==a)
                ans[i][j] = b;
            else if(ans[i][j]==b)
                ans[i][j] = a;
        }
}

bool solve()
{
    if(k==n+1||k==n*n-1)
        return false;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            ans[i][j] = -1;
    if(k%n==0)
    {
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                ans[i][j] = 1+((i-j+n)%n);
        switch_num(1,k/n);
        return true;
    }
    if(n==3)
        return false;
    int md, lst1, lst2;
    for(int i = 1; i<=n; i++)
        for(int d1 = 1; d1<=n; d1++)
            for(int d2 = 1; d2<=n; d2++)
                if(i!=d1&&i!=d2&&i*(n-2)+d1+d2==k)
                    md = i, lst1 = d1, lst2 = d2;
    if(lst1==lst2)
    {
        memset(row_taken,false,sizeof(row_taken));
        for(int i = 0; i<n-2; i++)
            ans[i][i] = 1;
        ans[n-2][n-1] = ans[n-1][n-2] = 1;
        for(int i = 0; i<n-3; i++)
            ans[i+1][i] = 2;
        ans[0][n-3] = ans[n-2][n-2] = ans[n-1][n-1] = 2;
        for(int num = 3; num<=n; num++)
        {
            for(int i = num-1; i<n; i++)
                ans[i][i-num+1] = num;
            for(int i = n-num+1; i<n; i++)
            {
                int ptr = 0;
                while(ans[ptr][i]!=-1||row_taken[num-1][ptr])
                    ++ptr;
                ans[ptr][i] = num, row_taken[num-1][ptr] = true;
            }
        }
        switch_num(ans[0][0],md), switch_num(ans[n-1][n-1],lst1);
        return true;
    }
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            ans[i][j] = 1+((i-j+n)%n);
    for(int i = 0; i<n; i++)
        swap(ans[n-2][i],ans[n-1][i]);
    switch_num(ans[0][0],md), switch_num(ans[n-2][n-2],lst1), switch_num(ans[n-1][n-1],lst2);
    return true;
}

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> k;
        cout << "Case #" << _ << ": ";
        if(solve())
        {
            cout << "POSSIBLE" << endl;
            for(int i = 0; i<n; i++)
            {
                for(int j = 0; j<n; j++)
                    cout << ans[i][j] << " ";
                cout << endl;
            }
        }
        else
            cout << "IMPOSSIBLE" << endl;
    }
}