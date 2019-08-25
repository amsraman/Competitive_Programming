#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m, q, a, b, id[1500][1500], low[1500][1500], bcc[1500][1500][4], cnt, cbcc = 1;
pair<int,int> st, fi, dir[4] = {make_pair(-1,0),make_pair(0,-1),make_pair(1,0),make_pair(0,1)};
vector<int> used;
vector<pair<pair<int,int>,int> > vbcc;
char z;
bool bl[1500][1500], v[1500][1500][4], v0[1500][1500], v1[1500][1500], art[1500][1500], done, bused[1500*1500*4+1];

bool valid(int a, int b){return ((a>=0)&&(a<n)&&(b>=0)&&(b<m)&&(!bl[a][b]));}

void bccdfs(int a, int b, int c, int d)
{
    v1[a][b] = true;
    id[a][b] = low[a][b] = cnt++;
    for(int i = 0; i<4; i++)
    {
        if(valid(a+dir[i].first,b+dir[i].second)&&(!v1[a+dir[i].first][b+dir[i].second]))
        {
            vbcc.push_back(make_pair(make_pair(a,b),i));
            bccdfs(a+dir[i].first,b+dir[i].second,a,b);
            low[a][b] = min(low[a][b],low[a+dir[i].first][b+dir[i].second]);
            if(low[a+dir[i].first][b+dir[i].second]>=id[a][b])
            {
                done = false, art[a][b] = true;
                while((!done)&&(vbcc.size()>=0))
                {
                    bcc[vbcc[vbcc.size()-1].first.first][vbcc[vbcc.size()-1].first.second][vbcc[vbcc.size()-1].second] = bcc[vbcc[vbcc.size()-1].first.first+dir[vbcc[vbcc.size()-1].second].first][vbcc[vbcc.size()-1].first.second+dir[vbcc[vbcc.size()-1].second].second][(vbcc[vbcc.size()-1].second+2)%4] = cbcc;
                    if(vbcc[vbcc.size()-1]==make_pair(make_pair(a,b),i)) done = true;
                    vbcc.pop_back();
                }
                cbcc++;
            }
        }
        else if(valid(a+dir[i].first,b+dir[i].second)&&((a+dir[i].first!=c)||(b+dir[i].second!=d)))
        {
            if(id[a+dir[i].first][b+dir[i].second]<id[a][b]) vbcc.push_back(make_pair(make_pair(a,b),i));
            low[a][b] = min(low[a][b],id[a+dir[i].first][b+dir[i].second]);
        }
    }
}

int main()
{
    ifstream infile("pushabox.in");
    ofstream outfile("pushabox.out");
    infile >> n >> m >> q;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            infile >> z;
            if(z=='#') bl[i][j] = true;
            if(z=='A') st = make_pair(i,j);
            if(z=='B') fi = make_pair(i,j);
        }
    }
    queue<pair<int,int> > q0;
    queue<pair<pair<int,int>,int> > q1;
    q0.push(st);
    while(!q0.empty())//preliminary bfs - establish starting points
    {
        int x = q0.front().first, y = q0.front().second;
        if(q0.front()==make_pair(fi.first-1,fi.second)) q1.push(make_pair(fi,0)), v[fi.first][fi.second][0] = true;
        if(q0.front()==make_pair(fi.first,fi.second-1)) q1.push(make_pair(fi,1)), v[fi.first][fi.second][1] = true;
        if(q0.front()==make_pair(fi.first+1,fi.second)) q1.push(make_pair(fi,2)), v[fi.first][fi.second][2] = true;
        if(q0.front()==make_pair(fi.first,fi.second+1)) q1.push(make_pair(fi,3)), v[fi.first][fi.second][3] = true;
        q0.pop();
        v0[x][y] = true;
        if(valid(x-1,y)&&((x-1!=fi.first)||(y!=fi.second))&&(!v0[x-1][y])) q0.push(make_pair(x-1,y)), v0[x-1][y] = true;
        if(valid(x,y-1)&&((x!=fi.first)||(y-1!=fi.second))&&(!v0[x][y-1])) q0.push(make_pair(x,y-1)), v0[x][y-1] = true;
        if(valid(x+1,y)&&((x+1!=fi.first)||(y!=fi.second))&&(!v0[x+1][y])) q0.push(make_pair(x+1,y)), v0[x+1][y] = true;
        if(valid(x,y+1)&&((x!=fi.first)||(y+1!=fi.second))&&(!v0[x][y+1])) q0.push(make_pair(x,y+1)), v0[x][y+1] = true;
    }
    bccdfs(fi.first,fi.second,fi.first,fi.second);
    while(vbcc.size()>0)
    {
        bcc[vbcc[vbcc.size()-1].first.first][vbcc[vbcc.size()-1].first.second][vbcc[vbcc.size()-1].second] = bcc[vbcc[vbcc.size()-1].first.first+vbcc[vbcc.size()-1].second][vbcc[vbcc.size()-1].first.second+vbcc[vbcc.size()-1].second][(vbcc[vbcc.size()-1].second+2)%4] = cbcc;
        vbcc.pop_back();
    }
    while(!q1.empty())//main bfs
    {
        int x = q1.front().first.first, y = q1.front().first.second, z = q1.front().second;
        q1.pop();
        if(valid(x+dir[(z+2)%4].first,y+dir[(z+2)%4].second)&&(!v[x+dir[(z+2)%4].first][y+dir[(z+2)%4].second][z])) q1.push(make_pair(make_pair(x+dir[(z+2)%4].first,y+dir[(z+2)%4].second),z)), v[x+dir[(z+2)%4].first][y+dir[(z+2)%4].second][z] = true;
        for(int i = 0; i<4; i++)//for each direction that has not been visited and is not the current one
        {
            if((i!=z)&&(valid(x+dir[i].first,y+dir[i].second))&&(!v[x][y][i]))
            {
                if(!art[x][y]) q1.push(make_pair(make_pair(x,y),i)), v[x][y][i] = true;
                else
                {
                    for(int j = 0; j<4; j++)//add all bccs for edges leading from the node in this direction
                    {
                        used.push_back(bcc[x+dir[i].first][y+dir[i].second][j]);
                        bused[bcc[x+dir[i].first][y+dir[i].second][j]] = bool(bcc[x+dir[i].first][y+dir[i].second][j]>0);
                    }
                    if((bused[bcc[x+dir[z].first][y+dir[z].second][0]])||(bused[bcc[x+dir[z].first][y+dir[z].second][1]])||(bused[bcc[x+dir[z].first][y+dir[z].second][2]])||(bused[bcc[x+dir[z].first][y+dir[z].second][3]]))//check if any edges going into the node in the direction you want are in the same bcc
                    {
                        q1.push(make_pair(make_pair(x,y),i));
                        v[x][y][i] = true;
                    }
                    while(used.size()!=0)
                    {
                        bused[used[used.size()-1]] = false;
                        used.pop_back();
                    }
                }
            }
        }
    }
    for(int i = 0; i<q; i++)
    {
        infile >> a >> b;
        outfile << ((v[a-1][b-1][0]||v[a-1][b-1][1]||v[a-1][b-1][2]||v[a-1][b-1][3]||((a-1==fi.first)&&(b-1==fi.second)))?("YES"):("NO")) << endl;
    }
}
