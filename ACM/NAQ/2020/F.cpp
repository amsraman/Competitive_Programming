#include <bits/stdc++.h>

using namespace std;

int n;
string s;

int main()
{
    cin >> n;
    cin.ignore();
    for(int i = 0; i<n; i++)
    {
        getline(cin,s);
        if(s.length()>11&&s.substr(0,11)=="Simon says ")
            cout << s.substr(11,s.length()-11) << endl;
    }
}