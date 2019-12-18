#include <bits/stdc++.h>

using namespace std;

int b, c, d, l, x, y, curl, sc;

int main()
{
    cin >> b >> c >> d >> l;
    while(l>=0)
    {
        curl = l, y = 0;
        while(curl>=0)
        {
            if(curl%d==0)
            {
                cout << x << " " << y << " " << curl/d << endl;
                sc++;
            }
            y++, curl-=c;
        }
        x++, l-=b;
    }
    if(sc==0) cout << "impossible" << endl;
}
