#include <bits/stdc++.h>

using namespace std;

string s;
int ans, num[1000000];

int main()
{
    cin >> s;
    int n = s.length();
    for(int i = 0; i<n; i++)
        if(s[i]==')')
        {
            num[i] = i+1;
            if(i>0&&s[i-1]=='(')
                num[i] = i-1;
            if(i>0&&s[i-1]==')'&&num[i-1]>0)
                num[i] = ((s[num[i-1]-1]=='(')?num[i-1]-1:i+1);
            if(s[num[i]-1]==')')
                num[i] = num[num[i]-1];
            ans = max(ans,i-num[i]+1);
        }
    int ct = 0;
    for(int i = 0; i<n; i++)
        if(i-num[i]+1==ans&&s[i]==')')
            ct++;
    if(ans==0)
        cout << "0 1" << endl;
    else
        cout << ans << " " << ct << endl;
}