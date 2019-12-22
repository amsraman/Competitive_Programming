#include <bits/stdc++.h>

using namespace std;

int n;
long long a, b, prevop = 1;
char op;

int main()
{
    cin >> n;
    for(int i = 0; i<n; i++)
    {
        cin >> a >> op >> b;
        if(op=='+') prevop = a+b-prevop;
        if(op=='-') prevop = (a-b)*prevop;
        if(op=='*') prevop = a*a*b*b;
        if(op=='/') prevop = (a+1)/2;
        cout << prevop << endl;
    }
}
