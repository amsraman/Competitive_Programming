#include <bits/stdc++.h>

using namespace std;

double a, b, h;

int main()
{
    cin >> a >> b >> h;
    cout << max(1+ceil((h-a)/(a-b)),double(1)) << endl;
}
