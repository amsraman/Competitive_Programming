#include <bits/stdc++.h>

using namespace std;

int w, p, pr[101];
set<int> ans;

int main()
{
    cin >> w >> p;
    for(int i = 0; i<p; i++)
        cin >> pr[i+1];
    pr[p+1] = w;
    for(int i = 0; i<=p+1; i++)
        for(int j = i+1; j<=p+1; j++)
            ans.insert(pr[j]-pr[i]);
    for(int i: ans)
        cout << i << " ";
    cout << endl;
}