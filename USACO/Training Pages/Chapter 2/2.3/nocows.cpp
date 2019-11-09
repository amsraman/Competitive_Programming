/*
ID: adityasund1
TASK: nocows
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int tree[100][201];
bool v[100][201] = {false};

int solve(int a, int b)
{
    if(v[a][b])
    {
        return tree[a][b];
    }
    if(b==1)
    {
        return 1;
    }
    if(a==0)
    {
        return 0;
    }
    int ret = 0;
    for(int i = 1; i<b-1; i++)
    {
        ret+=solve(a-1,i)*solve(a-1,b-i-1);
        ret%=9901;
    }
    return ret;
}

int main()
{
    ifstream infile("nocows.in");
    ofstream outfile("nocows.out");
    int n, k;
    infile >> n >> k;
    for(int i = 0; i<k; i++)
    {
        for(int j = 0; j<=n; j++)
        {
            tree[i][j] = solve(i,j);
            v[i][j] = true;
        }
    }
   int ans = (solve(k-1,n)-solve(k-2,n))%9901;
   if(ans<0)
   {
       ans+=9901;
   }
   outfile << ans << endl;
}//Key Mistake: Forgot a constraint
