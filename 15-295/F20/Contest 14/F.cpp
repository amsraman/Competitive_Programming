#include <bits/stdc++.h>

using namespace std;

int n, m, mat[20][20];
bool ans = false;
set<int> chk;

int main()
{
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
            cin >> mat[i][j];
    for(int sw1 = -1; sw1<m; sw1++)
        for(int sw2 = sw1+1; sw2<m; sw2++)
        {
            bool good = true;
            if(sw1!=-1)
                for(int i = 0; i<n; i++)
                    swap(mat[i][sw1],mat[i][sw2]);
            for(int i = 0; i<n; i++)
            {
                int bad = 0;
                for(int j = 0; j<m; j++)
                    if(mat[i][j]!=j+1)
                        bad++;
                if(bad>2)
                    good = false;
            }
            ans|=good;
            if(sw1!=-1)
                for(int i = 0; i<n; i++)
                    swap(mat[i][sw1],mat[i][sw2]);
        }
    cout << (ans?"YES":"NO");
}