#include <bits/stdc++.h>

using namespace std;

int h, c;
long long a[100000], d[100000], cur[100000];

bool ok(long long x)
{
    int ptr = 0;
    for(int i = 0; i<c; i++) cur[i] = a[i];
    for(int i = 0; i<h; i++)
    {
        while((ptr<c)&&(cur[ptr]+d[ptr]>x)) ptr++;
        if(ptr==c) return false;
        else cur[ptr]+=d[ptr];
    }
    return true;
}

int main()
{
    cin >> h >> c;
    for(int i = 0; i<c; i++) cin >> a[i] >> d[i];
    long long l = 1, g = 0xffffffffffffff;
    while(l<g)
    {
        long long mid = (l+g)/2;
        if(ok(mid)) g = mid;
        else l = mid+1;
    }
    for(int i = 0; i<c; i++) g = max(g,a[i]);
    cout << g << endl;
}
