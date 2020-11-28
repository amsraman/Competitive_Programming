#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, m, k, index[1000];
vector<int> vec;
bool v[1000];

int main()
{
    ifstream infile("cruise.in");
    ofstream outfile("cruise.out");
    infile >> n >> m >> k;
    pair<int,int> edge[n];
    char dir[n];
    for(int i = 0; i<n; i++)
    {
        infile >> edge[i].first >> edge[i].second;
        edge[i].first--;
        edge[i].second--;
    }
    for(int i = 0; i<m; i++)
    {
        infile >> dir[i];
    }
    int cur = 0;
    while(!v[cur])
    {
        v[cur] = true;
        vec.push_back(cur);
        index[cur] = vec.size()-1;
        for(int i = 0; i<m; i++)
        {
            if(dir[i]=='L')
            {
                cur = edge[cur].first;
            }
            else
            {
                cur = edge[cur].second;
            }
        }
    }
    k-=index[cur];
    k%=(vec.size()-index[cur]);
    outfile << vec[index[cur]+k]+1 << endl;
}
