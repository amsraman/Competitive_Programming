#include <bits/stdc++.h>

using namespace std;

int kmp[100001], num[100001], sz;
string s;
bool ok[100001];

int main()
{
    cin >> s;
    for(int i = 1; i<s.length(); i++)
    {
        kmp[i] = kmp[i-1];
        while(kmp[i]>0&&s[i]!=s[kmp[i]])
            kmp[i] = kmp[kmp[i]-1];
        if(s[i]==s[kmp[i]])
            ++kmp[i];
        if(kmp[i]>0)
            num[kmp[i]-1]++;
    }
    int cur = s.length()-1;
    while(cur!=-1)
        ok[cur] = true, cur = kmp[cur]-1, ++sz;
    for(int i = s.length()-1; i>=0; i--)
        if(kmp[i]>0)
            num[kmp[i]-1]+=num[i];
    cout << sz << endl;
    for(int i = 0; i<s.length(); i++)
        if(ok[i])
            cout << i+1 << " " << num[i]+1 << endl;
}
