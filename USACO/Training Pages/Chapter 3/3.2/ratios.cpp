/*
ID: adityasund1
TASK: ratios
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

int gcd(int a, int b)
{
    if((a==0)||(b==0))
    {
        return a+b;
    }
    return gcd(min(a,b),max(a,b)%min(a,b));
}

int main()
{
    ifstream infile("ratios.in");
    ofstream outfile("ratios.out");
    int mix[3][3], d[3];
    infile >> d[0] >> d[1] >> d[2];
    int k1 = gcd(gcd(d[0],d[1]),d[2]);
    d[0]/=k1;
    d[1]/=k1;
    d[2]/=k1;
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            infile >> mix[i][j];
        }
    }
    queue<pair<int,pair<int,int> > > q;
    q.push({0,{0,0}});
    bool v[101][101][101] = {false};
    v[0][0][0] = true;
    while(!q.empty())
    {
        int a = q.front().first, b = q.front().second.first, c = q.front().second.second;
        q.pop();
        int x = a*mix[0][0]+b*mix[1][0]+c*mix[2][0];
        int y = a*mix[0][1]+b*mix[1][1]+c*mix[2][1];
        int z = a*mix[0][2]+b*mix[1][2]+c*mix[2][2];
        int k = gcd(gcd(x,y),z);
        if((x==k*d[0])&&(y==k*d[1])&&(z==k*d[2])&&(k%k1==0)&&!((a==0)&&(b==0)&&(c==0)))
        {
            outfile << a << " " << b << " " << c << " " << k/k1 << endl;
            return 0;
        }
        if((a<99)&&(!v[a+1][b][c]))
        {
            q.push({a+1,{b,c}});
            v[a+1][b][c] = true;
        }
        if((b<99)&&(!v[a][b+1][c]))
        {
            q.push({a,{b+1,c}});
            v[a][b+1][c] = true;
        }
        if((c<99)&&(!v[a][b][c+1]))
        {
            q.push({a,{b,c+1}});
            v[a][b][c+1] = true;
        }
    }
    outfile << "NONE" << endl;
}
