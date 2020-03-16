#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int n, t = 4;
ll pre[301][301], ans;
char arr[300][300], temp[300][300];

int main()
{
    freopen("triangles.in","r",stdin);
    freopen("triangles.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            cin >> arr[i][j];
    while(t--)
    {
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                pre[i+1][j+1] = ll(arr[i][j]=='*')+pre[i][j];
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                for(int k = 1; k<n-max(i,j); k++)
                    if((arr[i][j]=='*')&&(arr[i+k][j+k]=='*'))
                        if((i-max(j+2*k-n+1,0)+1>=0)&&(j+k-min(i-k+1,0)+1<=n))
                            ans+=max(pre[i-max(j+2*k-n+1,0)+1][j+2*k-max(j+2*k-n+1,0)+1]-pre[i-k-min(i-k+1,0)+1][j+k-min(i-k+1,0)+1],ll(0));
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                temp[j][n-i-1] = arr[i][j];
        for(int i = 0; i<n; i++)
            for(int j = 0; j<n; j++)
                arr[i][j] = temp[i][j];
    }
    cout << ans << endl;
}
