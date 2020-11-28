#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n;
ll tot, ans;
string s;

int main()
{
    cin >> t;
    for(int cs = 1; cs<=t; cs++)
    {
        cin >> s;
        n = s.length(), tot = 0, ans = 0;
        vector<int> word;
        for(int i = 0; i<n; i++)
        {
            if((i>2)&&(s.substr(i-3,4)=="KICK"))
                word.push_back(0);
            if((i>3)&&(s.substr(i-4,5)=="START"))
                word.push_back(1), tot++;
        }
        for(int i = 0; i<word.size(); tot-=word[i], i++)
            if(word[i]==0)
                ans+=tot;
        cout << "Case #" << cs << ": " << ans << endl;
    }
}
