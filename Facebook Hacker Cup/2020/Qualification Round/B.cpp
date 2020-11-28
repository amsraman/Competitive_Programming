#include <bits/stdc++.h>

using namespace std;

int t, n;
string sh;

int main()
{
    freopen("alchemy_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int _ = 0; _<t; _++)
    {
        cin >> n >> sh;
        stack<char> s;
        for(int i = 0; i<n; i++)
        {
            if((!s.empty())&&(sh[i]!=s.top()))
                s.pop();
            else
                s.push(sh[i]);
        }
        s.pop();
        cout << "Case #" << _+1 << ": " << (s.empty()?'Y':'N') << endl;
    }
}
