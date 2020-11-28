#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

int t, n, m, c[300], ans;

int main()
{
    ifstream fin("pie_progress.txt");
    ofstream fout("output.txt");
    fin >> t;
    for(int z = 0; z<t; z++)
    {
        fin >> n >> m;
        ans = 0;
        priority_queue<int> q;
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<m; j++)
            {
                fin >> c[j];
            }
            sort(c,c+m);
            for(int j = 0; j<m; j++)
            {
                q.push(-c[j]-2*j-1);
            }
            ans-=q.top();
            q.pop();
        }
        fout << "Case #" << z+1 << ": " << ans << endl;
    }
}
