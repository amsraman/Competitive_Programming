/*
ID: adityasund1
TASK: rect1
LANG: C++
*/
#include <bits/stdc++.h>

using namespace std;

int a, b, n, rect[1001][5], area[2500];

void upd(int lx, int ly, int ux, int uy, int clr, int pos)
{
    while((pos<=n)&&((ux<=rect[pos][0])||(lx>=rect[pos][2])||(uy<=rect[pos][1])||(ly>=rect[pos][3])))
        pos++;
    if(pos==n+1)
    {
        area[clr-1]+=(ux-lx)*(uy-ly);
        return;
    }
    if(lx<rect[pos][0])
        upd(lx,ly,rect[pos][0],uy,clr,pos+1);
    if(ux>rect[pos][2])
        upd(rect[pos][2],ly,ux,uy,clr,pos+1);
    if(ly<rect[pos][1])
        upd(max(lx,rect[pos][0]),ly,min(ux,rect[pos][2]),rect[pos][1],clr,pos+1);
    if(uy>rect[pos][3])
        upd(max(lx,rect[pos][0]),rect[pos][3],min(ux,rect[pos][2]),uy,clr,pos+1);
}

int main()
{
    freopen("rect1.in","r",stdin);
    freopen("rect1.out","w",stdout);
    cin >> a >> b >> n;
    for(int i = 0; i<n; i++)
        for(int j = 0; j<5; j++)
            cin >> rect[i+1][j];
    rect[0][2] = a, rect[0][3] = b, rect[0][4] = 1;
    for(int i = n; i>=0; i--)
        upd(rect[i][0],rect[i][1],rect[i][2],rect[i][3],rect[i][4],i+1);
    for(int i = 0; i<2500; i++)
        if(area[i]>0)
            cout << i+1 << " " << area[i] << endl;
}