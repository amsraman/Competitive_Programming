#include <bits/stdc++.h>

using namespace std;

int t, x, y, tx, ty;
string ans;
bool ok;

int main()
{
    cin >> t;
    for(int cs = 0; cs<t; cs++)
    {
        cin >> x >> y;
        tx = abs(x), ty = abs(y), ans = "", ok = true;
        while(tx+ty>1)
        {
            if((tx%2)==(ty%2))
                ok = false;
            if((tx%4==1)^(ty%4==0))
                ans+="E", tx--;
            else if((tx%4==3)^(ty%4==0))
                ans+="W", tx++;
            else if((ty%4==1)^(tx%4==0))
                ans+="N", ty--;
            else
                ans+="S", ty++;
            tx/=2, ty/=2;
        }
        if(tx==1)
            ans+="E";
        else
            ans+="N";
        if(x<0)
            for(int i = 0; i<ans.length(); i++)
                if((ans[i]=='E')||(ans[i]=='W'))
                    ans[i] = ans[i]^'E'^'W';
        if(y<0)
            for(int i = 0; i<ans.length(); i++)
                if((ans[i]=='N')||(ans[i]=='S'))
                    ans[i] = ans[i]^'N'^'S';
        cout << "Case #" << cs+1 << ": " << (ok?(ans):("IMPOSSIBLE")) << endl;
    }
}
