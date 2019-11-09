/*
ID: adityasund1
TASK: camelot
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#define INF 0x3f3f3f

using namespace std;

int r, c, d[30][26][30][26], ans = INF;
pair<int,int> trans[8] = {{-2,-1},{-2,1},{2,-1},{2,1},{1,-2},{1,2},{-1,-2},{-1,2}};
bool v[30][26][30][26] = {false};

void mov(int a, int b)
{
    queue<pair<int,int> > q;
    q.push({a,b});
    d[a][b][a][b] = 0;
    v[a][b][a][b] = true;
    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i = 0; i<8; i++)
        {
            if((x+trans[i].first>=0)&&(x+trans[i].first<r)&&(y+trans[i].second>=0)&&(y+trans[i].second<c))
            {
                if(!v[a][b][x+trans[i].first][y+trans[i].second])
                {
                    d[a][b][x+trans[i].first][y+trans[i].second] = d[a][b][x][y]+1;
                    v[a][b][x+trans[i].first][y+trans[i].second] = true;
                    q.push({x+trans[i].first,y+trans[i].second});
                }
            }
        }
    }
}

int main()
{
    ifstream infile("camelot.in");
    ofstream outfile("camelot.out");
    infile >> r >> c;
    int b;
    for(int i = 0; i<30; i++){for(int j = 0; j<26; j++){for(int k = 0; k<30; k++){for(int l = 0; l<26; l++){d[i][j][k][l] = INF;}}}}
    pair<int,int> ki;
    vector<pair<int,int> > kn;
    char a;
    infile >> a >> b;
    ki = {b-1,a-'A'};
    for(int i = 0; i<r; i++)
    {
        for(int j = 0; j<c; j++)
        {
            mov(i,j);
        }
    }
    while(infile >> a >> b)
    {
        kn.push_back({b-1,a-'A'});
    }
    for(int i = 0; i<r; i++)
    {
        for(int j = 0; j<c; j++)
        {
            int z = 0, kd = max(max(ki.first,i)-min(ki.first,i),max(ki.second,j)-min(ki.second,j));
            for(int k = 0; k<kn.size(); k++)
            {
                z+=d[kn[k].first][kn[k].second][i][j];
            }
            ans = min(ans,z+kd);
            for(int k = 0; k<kn.size(); k++)
            {
                for(int l = max(0,ki.first-2); l<min(r,ki.first+3); l++)
                {
                    for(int m = max(0,ki.second-2); m<min(c,ki.second+3); m++)
                    {
                        ans = min(ans,z-d[kn[k].first][kn[k].second][i][j]+d[kn[k].first][kn[k].second][l][m]+d[i][j][l][m]+max(max(ki.first,l)-min(ki.first,l),max(ki.second,m)-min(ki.second,m)));
                    }
                }
            }
        }
    }
    outfile << ans << endl;
}
