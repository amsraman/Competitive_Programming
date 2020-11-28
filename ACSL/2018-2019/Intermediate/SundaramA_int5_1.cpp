#include <iostream>
#include <fstream>

using namespace std;

int r, c, s, n, z;
string ans;
bool blocked[1000][1000];

void f1(int a, int b, int x)
{
    if(a==c-1)
    {
        return;
    }
    if((x==0)&&(a<c-3)&&(!blocked[a+1][b])&&(!blocked[a+2][b])&&(!blocked[a+3][b]))
    {
        ans+="A";
        f1(a+3,b,(x+1)%3);
    }
    else if((x==1)&&(a>-1)&&(a<c-2)&&(b!=-1)&&(b<r-1)&&(!blocked[a+1][b])&&(!blocked[a+1][b+1])&&(!blocked[a+2][b+1]))
    {
        ans+="B";
        f1(a+2,b+1,(x+1)%3);
    }
    else if((x==2)&&(a<c-2)&&(b<r-3)&&(!blocked[a+1][b])&&(!blocked[a+2][b])&&(!blocked[a+2][b+1])&&(!blocked[a+2][b+2]))
    {
        ans+="C";
        f1(a+2,b+2,(x+1)%3);
    }
    else
    {
        f1(a,b,(x+1)%3);
    }
}

void f2(int a, int b, int x)
{
    if(a==0)
    {
        return;
    }
    if((x==0)&&(a>2)&&(!blocked[a-1][b])&&(!blocked[a-2][b])&&(!blocked[a-3][b]))
    {
        ans = "A"+ans;
        f2(a-3,b,(x+1)%3);
    }
    else if((x==1)&&(a>2)&&(b>0)&&(!blocked[a-1][b])&&(!blocked[a-2][b])&&(!blocked[a-2][b-1]))
    {
        ans = "B"+ans;
        f2(a-2,b-1,(x+1)%3);
    }
    else if((x==2)&&(a>1)&&(a<c)&&(b>1)&&(!blocked[a-1][b])&&(!blocked[a-1][b-1])&&(!blocked[a-1][b-2])&&(!blocked[a-2][b-2]))
    {
        ans = "C"+ans;
        f2(a-2,b-2,(x+1)%3);
    }
    else
    {
        f2(a,b,(x+1)%3);
    }
}

int main()
{
    ifstream fin("int3.txt");
    for(int co = 0; co<5; co++)
    {
        fin >> r >> c >> s >> n;
        ans = "";
        for(int i = 0; i<1000; i++)
        {
            for(int j = 0; j<1000; j++)
            {
                blocked[i][j] = false;
            }
        }
        for(int i = 0; i<n; i++)
        {
            fin >> z;
            blocked[(z-1)%c][(z-1)/c] = true;
        }
        if((s-1)%c==0)
        {
            f1(((s-1)%c)-1,(s-1)/c,0);
        }
        else
        {
            f2(((s-1)%c)+1,(s-1)/c,0);
        }
        cout << ans << endl;
    }
}
