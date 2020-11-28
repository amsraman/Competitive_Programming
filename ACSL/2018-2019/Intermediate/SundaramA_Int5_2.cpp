#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream fin("int2.txt");
    for(int z = 0; z<5; z++)
    {
        string a, b;
        fin >> a >> b;
        bool v[26], found;
        int p = 0, co[26];
        for(int i = 0; i<26; i++) co[i] = 0, v[i] = true;
        for(int i = 0; i<a.length(); i++)
        {
            found = false;
            for(int j = p; j<b.length(); j++)
            {
                if(b[j]==a[i])
                {
                    p = j+1;
                    found = true;
                    break;
                }
            }
            if(found) v[a[i]-'a'] = true;
        }
        for(int i = 0; i<26; i++) co[i]+=int(v[i]), v[i] = false;
        p = 0;
        for(int i = 0; i<b.length(); i++)
        {
            found = false;
            for(int j = p; j<a.length(); j++)
            {
                if(a[j]==b[i])
                {
                    p = j+1;
                    found = true;
                    break;
                }
            }
            if(found) v[b[i]-'a'] = true;
        }
        for(int i = 0; i<26; i++) co[i]+=int(v[i]), v[i] = false;
        p = b.length()-1;
        for(int i = a.length()-1; i>=0; i--)
        {
            found = false;
            for(int j = p; j>=0; j--)
            {
                if(a[i]==b[j])
                {
                    p = j-1;
                    found = true;
                    break;
                }
            }
            if(found) v[a[i]-'a'] = true;
        }
        for(int i = 0; i<26; i++) co[i]+=int(v[i]), v[i] = false;
        p = a.length()-1;
        for(int i = b.length()-1; i>=0; i--)
        {
            found = false;
            for(int j = p; j>=0; j--)
            {
                if(a[j]==b[i])
                {
                    p = j-1;
                    found = true;
                    break;
                }
            }
            if(found) v[b[i]-'a'] = true;
        }
        p = 0;
        for(int i = 0; i<26; i++) co[i]+=int(v[i]), v[i] = false;
        for(int i = 0; i<26; i++)
        {
            if(co[i]==4) cout << char('a'+i), p++;
        }
        if(p==0) cout << "NONE";
        cout << endl;
    }
}
