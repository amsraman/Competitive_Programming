#include <bits/stdc++.h>

using namespace std;

int n;
string a;

int main()
{
    cin >> n;
    for(int z = 0; z<n; z++)
    {
        cin >> a;
        vector<char> vec;
        string ans = "YES";
        vec.push_back(' ');
        for(int i = 0; i<a.length(); i++)
        {
            char x = vec[vec.size()-1];
            if(((a[i]=='t')&&(x!='|'))||((a[i]=='j')&&(x!='*'))||((a[i]=='b')&&(x!='$'))) ans = "NO";
            if(((a[i]=='t')||(a[i]=='j')||(a[i]=='b'))&&(x!=' ')) vec.pop_back();
            if((a[i]=='$')||(a[i]=='|')||(a[i]=='*')) vec.push_back(a[i]);
        }
        if(vec.size()>1) ans = "NO";
        cout << ans << endl;
    }
}
