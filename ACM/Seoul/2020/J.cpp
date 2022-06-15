#include <bits/stdc++.h>

using namespace std;

int n;
bool sw[500][500], in[500][500];

bool gauss()
{
    for(int i = 0; i<n; i++)
        in[i][i] = true;
    for(int i = 0; i<n; i++)
    {
        int tmp  = i;
        while(tmp<n&&!sw[tmp][i])
            ++tmp;
        if(tmp==n)
            return false;
        for(int j = 0; j<n; j++)
            swap(sw[i][j],sw[tmp][j]), swap(in[i][j],in[tmp][j]);
        for(int j = i+1; j<n; j++)
            if(sw[j][i])
            {
                for(int k = i; k<n; k++)
                    sw[j][k]^=sw[i][k];
                for(int k = 0; k<n; k++)
                    in[j][k]^=in[i][k];
            }
    }
    for(int i = n-1; i>=0; i--)
        for(int j = i-1; j>=0; j--)
            if(sw[j][i])
                for(int k = 0; k<n; k++)
                    in[j][k]^=in[i][k];
    return true;
}

void solve(int x)
{
    for(int i = 0; i<n; i++)
        if(in[i][x])
            cout << i+1 << " ";
    cout << endl;
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> sw[i][j];
    for(int i = 0; i<n; i++)
        for(int j = 0; j<i; j++)
            swap(sw[i][j],sw[j][i]);
    if(!gauss())
        cout << -1 << endl;
    else
        for(int i = 0; i<n; i++)
            solve(i);
}