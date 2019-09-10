#include <fstream>
#include <iostream>
#include <set>
#define A 100000007
#define B 1000000007
#define INF 0x3f3f3f3f

using namespace std;

int n, m, ans = INF;
long long mod[501], hsh1[500][500], hsh2[500][500];
string sp[500], pl[500];
set<long long> s;
bool f;

long long gethsh1(int a, int b, int c)
{
    if(b==0){return hsh1[a][c];}
    long long ret = (hsh1[a][c]-mod[c-b+1]*hsh1[a][b-1])%B;
    if(ret<0){ret+=B;}
    return ret;
}

long long gethsh2(int a, int b, int c)
{
    if(b==0){return hsh2[a][c];}
    long long ret = (hsh2[a][c]-mod[c-b+1]*hsh2[a][b-1])%B;
    if(ret<0){ret+=B;}
    return ret;
}

int main()
{
    ifstream infile("cownomics.in");
    ofstream outfile("cownomics.out");
    infile >> n >> m;
    for(int i = 0; i<n; i++)
    {
        infile >> sp[i];
    }
    for(int i = 0; i<n; i++)
    {
        infile >> pl[i];
    }
    mod[0] = 1;
    for(int i = 1; i<m; i++)
    {
        mod[i] = (mod[i-1]*A)%B;
        if(mod[i]<0){mod[i]+=B;}
    }
    for(int i = 0; i<n; i++)
    {
        hsh1[i][0] = sp[i][0]-'A'+1;
        hsh2[i][0] = pl[i][0]-'A'+1;
        for(int j = 1; j<m; j++)
        {
            hsh1[i][j] = ((A*hsh1[i][j-1])+(sp[i][j]-'A'+1))%B;
            if(hsh1[i][j]<0){hsh1[i][j]+=B;}
            hsh2[i][j] = ((A*hsh2[i][j-1])+(pl[i][j]-'A'+1))%B;
            if(hsh2[i][j]<0){hsh2[i][j]+=B;}
        }
    }
    int c1 = 0, c2 = 0;
    while(c1<m)
    {
        f = false;
        for(int i = 0; i<n; i++)
        {
            s.insert(gethsh2(i,c1,c2));
        }
        for(int i = 0; i<n; i++)
        {
            if(s.count(gethsh1(i,c1,c2)))
            {
                f = true;
            }
        }
        s.clear();
        if((f)&&(c2<m-1))
        {
            c2++;
        }
        else
        {
            if(!f)
            {
                ans = min(ans,c2-c1+1);
            }
            c1++;
        }
    }
    outfile << ans << endl;
}
