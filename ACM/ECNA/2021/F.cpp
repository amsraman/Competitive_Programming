#include <bits/stdc++.h>

using namespace std;

int n, m, lst, aug[1000][11], ans[10][10];
string init, enc;
bool many, none;

int conv(char c)
{
    if(c>='A'&&c<='Z')
        return (c-'A');
    if(c>='0'&&c<='9')
        return 26+(c-'0');
    return 36;
}

int mul(int x, int y)
{
    return (x*y)%37;
}

int inv(int x)
{
    int ret = 1, b = 35;
    while(b)
    {
        if(b&1)
            ret = mul(ret,x);
        x = mul(x,x), b>>=1;
    }
    return ret;
}

void gauss()
{
    for(int row = 0, col = 0; (row<m&&col<n); col++)
    {
        int tmp = row;
        while(tmp<m&&aug[tmp][col]==0)
            ++tmp;
        if(tmp==m)
            continue;
        for(int j = 0; j<=n; j++)
            swap(aug[row][j],aug[tmp][j]);
        for(int j = n; j>=col; j--)
            aug[row][j] = mul(aug[row][j],inv(aug[row][col]));
        for(int j = row+1; j<m; j++)
            if(aug[j][col]!=0)
                for(int k = n; k>=col; k--)
                    aug[j][k] = (aug[j][k]+37-mul(aug[j][col],aug[row][k]))%37;
        lst = row++;
    }
    for(int i = lst, ind = 0; i>=0; i--, ind = 0)
    {
        while(ind<n&&aug[i][ind]==0)
            ++ind;
        for(int j = i-1; j>=0; j--)
            if(aug[j][ind]!=0)
                for(int k = n; k>=ind; k--)
                    aug[j][k] = (aug[j][k]+37-mul(aug[j][ind],aug[i][k]))%37;
    }
}

int main()
{
    cin >> n;
    cin.ignore();
    getline(cin,init);
    getline(cin,enc);
    m = init.length()/n;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
            for(int k = 0; k<n; k++)
                aug[j][k] = conv(init[n*j+k]);
        for(int j = 0; j<m; j++)
            aug[j][n] = conv(enc[n*j+i]);
        lst = -1, gauss();
        for(int j = lst+1; j<m; j++)
            none|=(aug[j][n]!=0);
        many|=(lst<n-1);
        for(int j = 0; j<n; j++)
            ans[i][j] = aug[j][n];
    }
    if(none)
        cout << "No solution" << endl;
    else if(many)
        cout << "Too many solutions" << endl;
    else
    {
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<n; j++)
                cout << ans[i][j] << " ";
            cout << endl;
        }
    }
}