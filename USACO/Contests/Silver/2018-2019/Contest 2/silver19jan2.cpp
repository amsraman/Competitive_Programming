#include <bits/stdc++.h>

using namespace std;

int n, area, perimeter;
char input[1000][1000];
bool visited[1000][1000];
vector<pair<int,int> > blobs;

void dfs(int a, int b)
{
    area++, perimeter+=4;
    visited[a][b] = true;
    if((a>0)&&(input[a-1][b]=='#')) perimeter--;
    if((b>0)&&(input[a][b-1]=='#')) perimeter--;
    if((a<n-1)&&(input[a+1][b]=='#')) perimeter--;
    if((b<n-1)&&(input[a][b+1]=='#')) perimeter--;
    if((a>0)&&(input[a-1][b]=='#')&&(!visited[a-1][b])) dfs(a-1,b);
    if((b>0)&&(input[a][b-1]=='#')&&(!visited[a][b-1])) dfs(a,b-1);
    if((a<n-1)&&(input[a+1][b]=='#')&&(!visited[a+1][b])) dfs(a+1,b);
    if((b<n-1)&&(input[a][b+1]=='#')&&(!visited[a][b+1])) dfs(a,b+1);
}

int main()
{
    freopen("perimeter.in","r",stdin);
    freopen("perimeter.out","w",stdout);
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            cin >> input[i][j];
        }
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if((!visited[i][j])&&(input[i][j]=='#'))
            {
                area = perimeter = 0;
                dfs(i,j);
                blobs.push_back({area,-perimeter});
            }
        }
    }
    sort(blobs.begin(),blobs.end());
    cout << blobs[blobs.size()-1].first << " " << -blobs[blobs.size()-1].second << endl;
}
