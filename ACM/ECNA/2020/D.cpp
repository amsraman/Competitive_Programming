#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int r, s, n, a[50], b[50], c[100];
ll tot1, tot2;
bool dp[101][50][50], doable[2000001];

int main()
{
    cin >> r >> s >> n;
    for(int i = 0; i<r; i++)
        cin >> a[i];
    for(int i = 0; i<s; i++)
        cin >> b[i];
    for(int i = 0; i<n; i++)
        cin >> c[i];
    for(int i = 0; i<r; i++)
        tot1+=a[i];
    for(int i = 0; i<s; i++)
        tot2+=b[i];
    doable[0] = true;
    for(int i = 1; i<=2e6; i++)
    {
        if(i>=tot1)
            doable[i]|=doable[i-tot1];
        if(i>=tot2)
            doable[i]|=doable[i-tot2];
    }
    for(int i = 0; i<r; i++)
        for(int j = 0; j<s; j++)
            dp[n][i][j] = true;
    for(int i = n-1; i>=0; i--)
        for(int j = 0; j<r; j++)
            for(int k = 0; k<s; k++)
            {
                ll num1 = 0, num2 = 0;
                for(int l = 0; l<r; num1+=a[(j+l)%r], num2 = 0, l++)
                    for(int m = 0; m<s; num2+=b[(k+m)%s], m++)
                        if(num1+num2<=c[i])
                            dp[i][j][k]|=(dp[i+1][(j+l)%r][(k+m)%s]&&doable[c[i]-num1-num2]);
            }
    cout << (dp[0][0][0]?"Yes":"No") << endl;
}