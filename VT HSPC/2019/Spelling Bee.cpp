#include <bits/stdc++.h>

using namespace std;

int n;
string word, dict;
bool ok[26];

int main()
{
    cin >> word >> n;
    for(int i = 0; i<7; i++) ok[(word[i]-'a')] = true;
    for(int i = 0; i<n; i++)
    {
        cin >> dict;
        bool ok1 = false, ok2 = true;
        for(int j = 0; j<dict.length(); j++)
        {
            if(!ok[(dict[j]-'a')]) ok2 = false;
            if(dict[j]==word[0]) ok1 = true;
        }
        if(ok1&&ok2&&(dict.length()>=4)) cout << dict << endl;
    }
}
