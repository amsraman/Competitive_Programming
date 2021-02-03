#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> vec;

int main()
{
    cin >> n;
    vec.push_back(0);
    for(int i = 0; i<17; i++)
        for(int j = 0; j<(1<<i); j++)
            vec.push_back(1-vec[j]);
    for(int i = 0; i<=n; i++)
        if(vec[i]==vec[i-1])
            vec[i] = 2;
    for(int i = 0; i<n; i++)
        cout << char('a'+vec[i]);
    cout << endl;
}