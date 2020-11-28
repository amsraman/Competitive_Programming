#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n, ra, pa, rb, pb, c;
map<pair<ll,pair<pair<int,int>,bool>>,int> dp;

int conv(int x, int y)
{
    return x*x+y;
}

bool ok(int x, int y, ll msk)
{
    return (x>=0&&x<n&&y>=0&&y<=2*x&&!(msk&(1LL<<conv(x,y))));
}

int calc(ll msk, int r1, int c1, int r2, int c2, bool turn, bool reg)
{
    if(dp.count({msk,{{conv(r1,c1),conv(r2,c2)},turn}}))
        return dp[{msk,{{conv(r1,c1),conv(r2,c2)},turn}}];
    bool free = false;
    if(!turn)
    {
        int ret = -0x3f3f3f3f;
        if(ok(r1,c1-1,msk))
            ret = max(ret,calc(msk|(1LL<<conv(r1,c1-1)),r1,c1-1,r2,c2,!turn,0)), free = true;
        if(ok(r1,c1+1,msk))
            ret = max(ret,calc(msk|(1LL<<conv(r1,c1+1)),r1,c1+1,r2,c2,!turn,0)), free = true;
        if((c1%2==1)&&ok(r1-1,c1-1,msk))
            ret = max(ret,calc(msk|(1LL<<conv(r1-1,c1-1)),r1-1,c1-1,r2,c2,!turn,0)), free = true;
        if((c1%2==0)&&ok(r1+1,c1+1,msk))
            ret = max(ret,calc(msk|(1LL<<conv(r1+1,c1+1)),r1+1,c1+1,r2,c2,!turn,0)), free = true;
        dp[{msk,{{conv(r1,c1),conv(r2,c2)},turn}}] = ret+1;
    }
    else
    {
        int ret = 0x3f3f3f3f;
        if(ok(r2,c2-1,msk))
            ret = min(ret,calc(msk|(1LL<<conv(r2,c2-1)),r1,c1,r2,c2-1,!turn,0)), free = true;
        if(ok(r2,c2+1,msk))
            ret = min(ret,calc(msk|(1LL<<conv(r2,c2+1)),r1,c1,r2,c2+1,!turn,0)), free = true;
        if((c2&1)&&ok(r2-1,c2-1,msk))
            ret = min(ret,calc(msk|(1LL<<conv(r2-1,c2-1)),r1,c1,r2-1,c2-1,!turn,0)), free = true;
        if((c2&1^1)&&ok(r2+1,c2+1,msk))
            ret = min(ret,calc(msk|(1LL<<conv(r2+1,c2+1)),r1,c1,r2+1,c2+1,!turn,0)), free = true;
        dp[{msk,{{conv(r1,c1),conv(r2,c2)},turn}}] = ret-1;
    }
    if(!free&&!reg)
        dp[{msk,{{conv(r1,c1),conv(r2,c2)},turn}}] = calc(msk,r1,c1,r2,c2,!turn,1);
    else if(!free)
        dp[{msk,{{conv(r1,c1),conv(r2,c2)},turn}}] = 0;
    return dp[{msk,{{conv(r1,c1),conv(r2,c2)},turn}}];
}

int main()
{
    cin >> t;
    for(int cs = 1; cs<=t; cs++)
    {
        cin >> n >> ra >> pa >> rb >> pb >> c;
        ll init = ((1LL<<conv(ra-1,pa-1))|(1LL<<conv(rb-1,pb-1)));
        for(int i = 0, r, p; i<c; i++)
        {
            cin >> r >> p;
            init|=(1LL<<conv(r-1,p-1));
        }
        cout << "Case #" << cs << ": " << calc(init,ra-1,pa-1,rb-1,pb-1,0,0) << endl;
        dp.clear();
    }
}
