#include <bits/stdc++.h>

using namespace std;

int n, m;
string winner, loser, ord[100];

int main()
{
    cin >> n >> m;
    for(int i = 0; i<n; i++)
        ord[i] = "T"+to_string(i+1);
    for(int i = 0, pos1, pos2; i<m; i++)
    {
        cin >> winner >> loser;
        for(int i = 0; i<n; i++)
        {
            if(ord[i]==winner)
                pos1 = i;
            if(ord[i]==loser)
                pos2 = i;
        }
        if(pos2<pos1)
            for(int i = pos2; i<pos1; i++)
                swap(ord[i],ord[i+1]);
    }
    for(int i = 0; i<n; i++)
        cout << ord[i] << " ";
    cout << endl;
}