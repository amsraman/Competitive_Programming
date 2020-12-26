#include <bits/stdc++.h>

using namespace std;

int n;
map<char,int> val;
string in[36];
bool v[36], lat, red;
 
int conv(string s)
{
    int ret = 0;
    for(int i = 0; i<s.length(); i++)
        ret = 10*ret+(s[i]-'0');
    return ret;
}

int main()
{
    for(int i = 0; i<10; i++)
        val[char('0'+i)] = i;
    for(int i = 0; i<26; i++)
        val[char('A'+i)] = i+10;
    string s;
    getline(cin,s);
    while(!cin.eof())
    {
        lat = red = true;
        n = conv(s);
        for(int i = 0; i<n; i++)
            cin >> in[i];
        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<36; j++)
                v[j] = false;
            for(int j = 0; j<n; j++)
            {
                if(v[val[in[i][j]]])
                    lat = false;
                v[val[in[i][j]]] = true;
            }
            for(int j = 0; j<36; j++)
                v[j] = false;
            for(int j = 0; j<n; j++)
            {
                if(v[val[in[j][i]]])
                    lat = false;
                v[val[in[j][i]]] = true;
            }
        }
        for(int i = 1; i<n; i++)
            if(val[in[0][i-1]]+1!=val[in[0][i]])
                red = false;
        for(int i = 1; i<n; i++)
            if(val[in[i-1][0]]+1!=val[in[i][0]])
                red = false;
        if(!lat)
            cout << "No" << endl;
        else if(!red)
            cout << "Not Reduced" << endl;
        else
            cout << "Reduced" << endl;
        getline(cin,s);
        getline(cin,s);
    }
}