#include <bits/stdc++.h>

using namespace std;

int n, m, arr[8][8], ans;

bool isPrime(int hi)
{
    for(int i = 2; i*i<=hi; i++)
        if(hi%i==0)
            return false;
    return true;
}

int ok(int r, int c)
{
    int cur1 = 0, cur2 = 0;
    for(int i = 0; i<=r; i++)
        cur1 = 10*cur1+arr[i][c];
    for(int i = 0; i<=c; i++)
        cur2 = 10*cur2+arr[r][i];
    return (isPrime(cur1)&&isPrime(cur2));
}

void gen(int r, int c)
{
    if(r==n)
    {
        ans++;
        return;
    }
    if(c==m)
        gen(r+1,0);
    if((r==0)||(c==0))
        for(int i: {2,3,5,7})
        {
            arr[r][c] = i;
            if(ok(r,c))
                gen(r,c+1);
        }
    else
        for(int i: {1,3,7,9})
        {
            arr[r][c] = i;
            if(ok(r,c))
                gen(r,c+1);
        }
}

int main()
{
    cin >> n >> m;
    gen(0,0);
    cout << ans << endl;
}
