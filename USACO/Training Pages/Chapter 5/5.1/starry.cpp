/*
ID: adityasund1
TASK: starry
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int w, h, gc, rc, minx, miny, maxx, maxy, gid, group[100][100], cid[26], curid;
char in[100][100];
pair<int,int> minc[26], maxc[26];
bool v[100][100][2];

void dfs(int a, int b, char c, int d)
{
    v[a][b][d] = true;
    group[a][b] = rc;
    minx = min(minx,a);
    miny = min(miny,b);
    maxx = max(maxx,a);
    maxy = max(maxy,b);
    if((a>0)&&(in[a-1][b]==in[a][b])&&(!v[a-1][b][d])){dfs(a-1,b,c,d);}
    if((a<h-1)&&(in[a+1][b]==in[a][b])&&(!v[a+1][b][d])){dfs(a+1,b,c,d);}
    if((b>0)&&(in[a][b-1]==in[a][b])&&(!v[a][b-1][d])){dfs(a,b-1,c,d);}
    if((b<w-1)&&(in[a][b+1]==in[a][b])&&(!v[a][b+1][d])){dfs(a,b+1,c,d);}
    if((a>0)&&(b>0)&&(in[a-1][b-1]==in[a][b])&&(!v[a-1][b-1][d])){dfs(a-1,b-1,c,d);}
    if((a>0)&&(b<w-1)&&(in[a-1][b+1]==in[a][b])&&(!v[a-1][b+1][d])){dfs(a-1,b+1,c,d);}
    if((a<h-1)&&(b>0)&&(in[a+1][b-1]==in[a][b])&&(!v[a+1][b-1][d])){dfs(a+1,b-1,c,d);}
    if((a<h-1)&&(b<w-1)&&(in[a+1][b+1]==in[a][b])&&(!v[a+1][b+1][d])){dfs(a+1,b+1,c,d);}
    in[a][b] = c;
}

bool check(int a, int b, int c, int d, int e, int f, int g, int h, bool x)
{
    bool ret = true;
    for(int i = a; i<=c; i++)
    {
        for(int j = b; j<=d; j++)
        {
            if((((in[i][j]=='0')!=(in[e][f]=='0'))&&((group[i][j]==rc)||(in[i][j]=='0'))&&((group[e][f]==curid)||(in[e][f]=='0'))&&x)||(((in[i][j]=='0')!=(in[f][e]=='0'))&&((group[i][j]==rc)||(in[i][j]=='0'))&&((group[f][e]==curid)||(in[f][e]=='0'))&&!x)){ret = false;}
            f+=h;
        }
        f-=((d-b+1)*h);
        e+=g;
    }
    return ret;
}

bool valid(int a, int b, int c, int d, int e)
{
    bool x = false, y = false;
    curid = cid[e];
    if((c-a==maxc[e].first-minc[e].first)&&(d-b==maxc[e].second-minc[e].second)){x = (check(a,b,c,d,minc[e].first,minc[e].second,1,1,1)||check(a,b,c,d,minc[e].first,maxc[e].second,1,-1,1)||check(a,b,c,d,maxc[e].first,minc[e].second,-1,1,1)||check(a,b,c,d,maxc[e].first,maxc[e].second,-1,-1,1));}
    if((d-b==maxc[e].first-minc[e].first)&&(c-a==maxc[e].second-minc[e].second)){y = (check(a,b,c,d,minc[e].second,minc[e].first,1,1,0)||check(a,b,c,d,minc[e].second,maxc[e].first,1,-1,0)||check(a,b,c,d,maxc[e].second,minc[e].first,-1,1,0)||check(a,b,c,d,maxc[e].second,maxc[e].first,-1,-1,0));}
    return (x||y);
}

int main()
{
    ifstream infile("starry.in");
    ofstream outfile("starry.out");
    infile >> w >> h;
    for(int i = 0; i<h; i++)
    {
        for(int j = 0; j<w; j++)
        {
            infile >> in[i][j];
        }
    }
    for(int i = 0; i<h; i++)
    {
        for(int j = 0; j<w; j++)
        {
            if((!v[i][j][0])&&(in[i][j]=='1'))
            {
                rc++;
                minx = miny = 101;
                maxx = maxy = 0;
                gid = -1;
                dfs(i,j,'1',0);
                for(int k = 0; k<gc; k++)
                {
                    if(valid(minx,miny,maxx,maxy,k)){gid = k;}
                }
                if(gid==-1)
                {
                    minc[gc] = {minx,miny};
                    maxc[gc] = {maxx,maxy};
                    gid = gc;
                    cid[gc] = rc;
                    gc++;
                }
                dfs(i,j,char('a'+gid),1);
            }
        }
    }
    for(int i = 0; i<h; i++)
    {
        for(int j = 0; j<w; j++){outfile << in[i][j];}
        outfile << endl;
    }
}
