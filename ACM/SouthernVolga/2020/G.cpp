#include <bits/stdc++.h>
#define f first
#define s second
typedef long double ld;

using namespace std;

int n, h;
ld ans;
pair<int,int> points[200000], eye, peak;

ld norm(ld a, ld b)
{
    return sqrt(a*a+b*b);
}

ld cross(ld a, ld b, ld c, ld d)
{
    return a*d-b*c;
}

int main()
{
    cin >> n >> h;
    for(int i = 0; i<n; i++)
        cin >> points[i].f >> points[i].s;
    eye = {points[n-1].f,points[n-1].s+h}, peak = points[n-1];
    for(int i = n-2; i>=0; i--)
    {
        ld cross1 = cross(points[i].f-peak.f,points[i].s-peak.s,peak.f-eye.f,peak.s-eye.s);
        ld cross2 = cross(points[i+1].f-peak.f,points[i+1].s-peak.s,peak.f-eye.f,peak.s-eye.s);
        if(cross1>=0&&cross2>=0)
            ans+=norm(points[i+1].f-points[i].f,points[i+1].s-points[i].s), peak = points[i];
        else if(cross1>=0)
            ans+=norm(points[i+1].f-points[i].f,points[i+1].s-points[i].s)*cross1/(cross1-cross2), peak = points[i];
    }
    cout << fixed << setprecision(10) << ans << endl;
}