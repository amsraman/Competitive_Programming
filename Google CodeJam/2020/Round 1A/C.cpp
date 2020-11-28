#include <bits/stdc++.h>
#define f first
#define s second
typedef long long ll;

using namespace std;

int t, r, c, skill[100000], cn[100000][4], cur;
ll tot, ans;
bool removed[100000];
vector<int> remlist;

int score(int x)
{
    int ret = 0;
    for(int i = 0; i<4; i++)
        if(cn[x][i]!=-1)
            ret+=skill[cn[x][i]];
    return ret;
}

void rem(int x)
{
    tot-=ll(skill[x]);
    for(int i = 0; i<4; i++)
        if(cn[x][i]!=-1)
            cn[cn[x][i]][(i+2)%4] = cn[x][(i+2)%4];
}

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> r >> c;
        for(int i = 0; i<r; i++)
            for(int j = 0; j<c; j++)
                cin >> skill[c*i+j];
        queue<pair<int,int> > q;
        tot = ans = 0, cur = -1;
        for(int i = 0; i<r*c; i++)
        {
            q.push({i,0});
            for(int j = 0; j<4; j++)
                cn[i][j] = -1;
            removed[i] = false, tot+=ll(skill[i]);
            if(i-c>=0)
                cn[i][0] = i-c;
            if((i+1)%c!=0)
                cn[i][1] = i+1;
            if(i+c<r*c)
                cn[i][2] = i+c;
            if((i%c)!=0)
                cn[i][3] = i-1;
        }
        while(!q.empty())
        {
            int x = q.front().f, y = q.front().s, nc = 0;
            if(y!=cur)
            {
                while(remlist.size()!=0)
                    rem(remlist[remlist.size()-1]), remlist.pop_back();
                ans+=tot, cur = y;
            }
            for(int i = 0; i<4; i++)
                if(cn[x][i]!=-1)
                    nc++;
            if((!removed[x])&&(score(x)>nc*skill[x]))
            {
                removed[x] = true, remlist.push_back(x);
                for(int i = 0; i<4; i++)
                    if(cn[x][i]!=-1)
                        q.push({cn[x][i],y+1});
            }
            q.pop();
        }
        cout << "Case #" << cs+1 << ": " << ans << endl;
    }
}
