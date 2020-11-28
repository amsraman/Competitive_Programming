#include <bits/stdc++.h>
#define PI 3.1415926535

using namespace std;

int t;
double p, x, y, ang;
string ans;

int main()
{
    freopen("progress_pie.txt","r",stdin);
    freopen("output.txt","w",stdout);
    cin >> t;
    for(int z = 0; z<t; z++)
    {
        cin >> p >> x >> y;
        if((x-50)*(x-50)+(y-50)*(y-50)>2500)
        {
            ans = "white";
        }
        else
        {
            ang = PI/2-atan2(y-50,x-50);
            if((x<50)&&(y>=50)) ang+=2*PI;
            if((ang>2*PI*p/100)||(p==0)) ans = "white";
            else ans = "black";
        }
        cout << "Case #" << z+1 << ": " << ans << endl;
    }
}
