/*
ID: adityasund1
TASK: beads
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int n, cur, ans;
char c;
string beads;

int main()
{
    freopen("beads.in","r",stdin);
    freopen("beads.out","w",stdout);
    cin >> n >> beads;
    beads+=beads;
    for(int i = 0; i<n; i++)
    {
        cur = i;
        while((beads[cur]=='w')&&(cur<2*n-2))
            cur++;
        c = beads[cur], cur = i;
        while(((beads[cur]==c)||(beads[cur]=='w'))&&(cur<2*n-2))
            cur++;
        c = beads[cur];
        while(((beads[cur]==c)||(beads[cur]=='w'))&&(cur<2*n-2))
            cur++;
        if((beads[cur]!=beads[cur-1])&&(beads[cur]!='w'))
            cur--;
        ans = max(ans,cur-i+1);
    }
    cout << min(ans,n) << endl;
}
