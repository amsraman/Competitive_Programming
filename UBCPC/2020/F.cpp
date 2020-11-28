#include <bits/stdc++.h>

using namespace std;

int n, adj[50][50], deg[50];

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cout << "? " << 1 << " " << i+1 << endl;
        cin >> deg[i];
    }
    for(int i = 0; i<n; i++)
        for(int j = i+1, temp; j<n; j++)
        {
            cout << "? " << 2 << " " << i+1 << " " << j+1 << endl;
            cin >> temp;
            if(temp==deg[i]+deg[j]-2)
                adj[i][j] = adj[j][i] = 1;
        }
    cout << "!" << endl;
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
            cout << adj[i][j] << " ";
        cout << endl;
    }
}
