#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll n, k, a[200000];

int main()
{
    cin >> n >> k;
    for(int i = 0; i<n; i++)
        cin >> a[i];
    sort(a,a+n);
    ll p1 = n/2, med = a[n/2];
    while((p1<n)&&(a[p1]==a[p1+1]))
        p1++;
    p1++;
    while((p1<n)&&(k>0))
    {
        ll temp = min(k,(a[p1]-a[p1-1])*(p1-n/2));
        med+=temp/(p1-n/2), k-=temp;
        while((p1<n)&&(a[p1]==a[p1+1]))
            p1++;
        p1++;
    }
    if(k>0)
        med+=(k/((n+1)/2));
    cout << med << endl;
}