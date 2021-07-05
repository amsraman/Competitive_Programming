/*
ID: adityasund1
TASK: rectbarn
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int r, c, p, x, y, height[3000], le[3000], re[3000], cur, ans;
bool blocked[3000][3000];

int main()
{
    freopen("rectbarn.in","r",stdin);
    freopen("rectbarn.out","w",stdout);
    cin >> r >> c >> p;
    memset(le,0x3f3f3f3f,sizeof(le)), memset(re,0x3f3f3f3f,sizeof(re));
    for(int i = 0; i<p; i++)
    {
        cin >> x >> y;
        blocked[x-1][y-1] = true;
    }
    for(int i = 0; i<r; i++)
    {
        cur = 0;
        for(int j = 0; j<c; j++)
        {
            if(blocked[i][j]) height[j] = cur = 0, le[j] = 3001;
            else height[j]++, cur++, le[j] = min(le[j],cur);
        }
        cur = 0;
        for(int j = c-1; j>=0; j--)
        {
            if(blocked[i][j]) re[j] = 3001, cur = 0;
            else
            {
                cur++, re[j] = min(re[j],cur);
                ans = max(ans,height[j]*(le[j]+re[j]-1));
            }
        }
    }
    cout << ans << endl;
}