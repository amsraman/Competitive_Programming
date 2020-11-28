#include <bits/stdc++.h>

using namespace std;

int t, a;
string in[255], ans;
bool pos, done, v[255];
map<char,bool> mp;

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        pos = true, done = false, ans = "";
        cin >> a;
        for(int i = 0; i<a; i++)
            cin >> in[i];
        for(int i = 0; i<a; i++)
            v[i] = false;
        for(int mv = 0; !done; mv++)
        {
            mp['R'] = mp['P'] = mp['S'] = false;
            for(int i = 0; i<a; i++)
                if(!v[i])
                    mp[in[i][mv%in[i].length()]] = true;
            if(!mp['R']&&!mp['P']&&!mp['S'])
                done = true;
            else if(mp['R']&&mp['P']&&mp['S'])
                done = true, pos = false;
            else if(mp['R']&&!mp['P']&&!mp['S'])
                done = true, ans+="P";
            else if(!mp['R']&&mp['P']&&!mp['S'])
                done = true, ans+="S";
            else if(!mp['R']&&!mp['P']&&mp['S'])
                done = true, ans+="R";
            else
            {
                char rem;
                if(mp['R']&&mp['P'])
                    rem = 'P';
                else if(mp['R']&&mp['S'])
                    rem = 'R';
                else
                    rem = 'S';
                ans+=rem;
                for(int i = 0; i<a; i++)
                    if((!v[i])&&(in[i][mv%in[i].length()]!=rem))
                        v[i] = true;
            }
        }
        cout << "Case #" << cs+1 << ": " << (pos?(ans):("IMPOSSIBLE")) << endl;
    }
}
