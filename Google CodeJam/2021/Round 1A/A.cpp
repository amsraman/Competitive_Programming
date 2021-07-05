#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int t, n;
string x[100], c1, c2;
int ans;

int main()
{
    cin >> t;
    for(int _ = 1; _<=t; _++)
    {
        cin >> n;
        for(int i = 0; i<n; i++)
            cin >> x[i];
        c1 = x[0];
        for(int i = 1; i<n; i++)
        {
            c2 = x[i];
            if(c2.length()>c1.length())
            {
                c1 = c2;
                continue;
            }
            string pf = c1.substr(0,c2.length());
            if(pf>c2)
            {
                ans+=(c1.length()-c2.length()+1);
                //We can pad with zeros
                while(c2.length()<=c1.length())
                    c2+='0';
            }
            else if(pf<c2)
            {
                ans+=(c1.length()-c2.length());
                //We can pad with zeros
                while(c2.length()<c1.length())
                    c2+='0';
            }
            else
            {
                int pos = c1.length()-1;
                while(pos>=0&&c1[pos]=='9')
                    --pos;
                if(pos<(int)c2.length())
                {
                    ans+=(c1.length()-c2.length()+1);
                    //We have to pad with zeros
                    while(c2.length()<=c1.length())
                        c2+='0';
                }
                else
                {
                    ans+=(c1.length()-c2.length());
                    for(int i = c2.length(); i<pos; i++)
                        c2+=c1[i];
                    c2+=char(c1[pos]+1);
                    while(c2.length()<c1.length())
                        c2+='0';
                }
            }
            c1 = c2;
        }
        cout << "Case #" << _ << ": " << ans << endl;
        ans = 0;
    }
}