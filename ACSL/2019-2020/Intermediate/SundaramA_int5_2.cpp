#include <bits/stdc++.h>

using namespace std;

int t = 5, ans;
string a, b;

int common()
{
    for(int i = 0; i<min(a.length(),b.length()); i++)
        if(a[i]==b[i])
            return i;
    return 500;
}

int shift(string x, string y)
{
    for(int i = 0; i<min(x.length(),y.length()-1); i++)
        if(x[i]==y[i+1])
            return i;
    return 500;
}

int main()
{
    freopen("D:/2inttest.txt","r",stdin);
    while(t--)
    {
        ans = 0;
        cin >> a >> b;
        while((common()<500)||(shift(a,b)<500)||(shift(b,a)<500))
        {
            int x = common(), y = shift(a,b), z = shift(b,a);
            if(x<500)
                a.erase(x,1), b.erase(x,1);
            else if((y<=z)&&(y<500))
                b.erase(y,1);
            else if(z<500)
                a.erase(z,1);
        }
        for(int i = 0; i<min(a.length(),b.length()); i++)
            ans+=(a[i]-b[i]);
        cout << ans+abs(int(a.length())-int(b.length())) << endl;
    }
}
