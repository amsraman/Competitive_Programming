#include <bits/stdc++.h>

using namespace std;

int t, n, a, b, c, ta, tb, tc, mx;
vector<int> ans;

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n >> a >> b >> c;
        cout << "Case #" << _ << ": ";
        ta = tb = tc = 0;
        for(int i = 0; i<a-c; i++)
            ans.push_back(i+1);
        ans.push_back(n);
        for(int i = 0; i<n-a-b+c; i++)
            ans.push_back(1);
        for(int i = 0; i<c-1; i++)
            ans.push_back(n);
        for(int i = b-c; i>0; i--)
            ans.push_back(i);
        if((b-c==1)&&(c==1)&&(n-a-b+c>0))
            ans[ans.size()-1]++;
        if((b==1)&&(c==1))
        {
            ans.clear();
            for(int i = 0; i<a-1; i++)
                ans.push_back(i+1);
            for(int i = 0; i<n-a; i++)
                ans.push_back(1);
            ans.push_back(n);
        }
        if((a==2)&&(b==1)&&(c==1)&&(n>2))
        {
            ans.clear();
            ans.push_back(2);
            for(int i = 0; i<n-2; i++)
                ans.push_back(1);
            ans.push_back(n);
        }
        mx = 0;
        for(int i = 0; i<ans.size(); i++)
            if(mx<=ans[i])
                mx = ans[i], ta++;
        mx = 0;
        for(int i = ans.size()-1; i>=0; i--)
            if(mx<=ans[i])
                mx = ans[i], tb++;
        mx = 0;
        for(auto x: ans)
            mx = max(mx,x);
        for(auto x: ans)
            if(x==mx)
                tc++;
        bool bad = false;
        for(auto x: ans)
            if((x<1)||(x>n))
                bad = true;
        assert(!bad);
        if((ans.size()!=n)||(a!=ta)||(b!=tb)||(c!=tc))
            cout << "IMPOSSIBLE";
        else
            for(auto x: ans)
                cout << x << " ";
        cout << endl;
        ans.clear();
    }
}
