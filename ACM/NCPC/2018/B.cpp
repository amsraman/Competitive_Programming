#include <bits/stdc++.h>

using namespace std;

int n;
string res[1000];

bool solve()
{
    for(int i = 0; i<n; i++)
        if(res[i]!="mumble"&&atoi(res[i].c_str())!=i+1)
            return false;
    return true;
}

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> res[i];
    cout << (solve()?"makes sense":"something is fishy") << endl;
}