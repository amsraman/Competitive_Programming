#include <iostream>
#include <fstream>

using namespace std;

string num[10] = {"0","1","2","3","4","5","6","7","8","9"}, s1, s2;

void add()
{
    string s3;
    int cnt = s1.length(), k = 0;
    for(int i = s2.length()-1; i>=0; i--)
    {
        cnt--;
        int z = (s2[i]-'0')+(s1[cnt]-'0')+k;
        s3 = num[z%10]+s3;
        k = z/10;
        z%=10;
    }
    while(k!=0)
    {
        if(cnt==0)
        {
            s3 = num[k]+s3;
            break;
        }
        cnt--;
        int z = (s1[cnt]-'0')+k;
        k = z/10;
        z%=10;
        s3 = num[z]+s3;
    }
    while(cnt!=0)
    {
        cnt--;
        s3 = num[s1[cnt]-'0']+s3;
    }
    s1 = s3;
}

int main()
{
    ifstream fin("sr4.txt");
    for(int z = 0; z<5; z++)
    {
        long long a, k = 0, ans = 0;
        string s;
        fin >> s >> a;
        while(s.length()%a!=0)
        {
            s+="0";
        }
        s1 = s2 = s.substr(0,a);
        for(int i = 1; i<s.length()/a; i++)
        {
            s2 = s.substr(i*a,a);
            add();
        }
        cout << s1 << endl;
    }
}
