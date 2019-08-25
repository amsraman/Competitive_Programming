/*
ID: adityasund1
TASK: charrec
LANG: C++
*/
#include <fstream>
#include <iostream>

using namespace std;

int n, dist[1200][540], val[1200][3], dp[1201];
char rec[1200][3];
string font[540], in[1200], re = " abcdefghijklmnopqrstuvwxyz", ans[1200];

int main()
{
    ifstream infile("charrec.in");
    ifstream ffont("font.in");
    ofstream outfile("charrec.out");
    ffont >> n;
    for(int i = 0; i<n; i++) ffont >> font[i];
    infile >> n;
    for(int i = 0; i<n; i++) infile >> in[i];
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<540; j++)
        {
            for(int k = 0; k<20; k++)
            {
                if(in[i][k]!=font[j][k]) dist[i][j]++;
            }
        }
    }
    for(int curpos = 0; curpos<n; curpos++)
    {
        int mindist, cost, cnt;
        char minl;
        if(n-curpos>=21)
        {
            mindist = 0x3f3f3f3f, cnt = 0;
            for(int i = 0; i<27; i++)
            {
                cost = 0x3f3f3f3f;
                for(int j = 0; j<20; j++)
                {
                    int curc = 0, p1 = 0, p2 = 0;
                    while((p1<21)&&(p2<20))
                    {
                        if(p1==j) curc+=min(dist[curpos+p1][i*20+p2],dist[curpos+p1+1][i*20+p2]), p1+=2, p2++;
                        else curc+=dist[curpos+p1][i*20+p2], p1++, p2++;
                    }
                    cost = min(cost,curc);
                }
                if((cost==mindist)&&(re[i]!=minl)) cnt++;
                if(cost<mindist) mindist = cost, minl = re[i], cnt = 0;
            }
            val[curpos][0] = mindist;
            rec[curpos][0] = ((cnt==0)?(minl):('?'));
        }
        if(n-curpos>=20)
        {
            mindist = 0x3f3f3f3f, cnt = 0;
            for(int i = 0; i<27; i++)
            {
                cost = 0;
                for(int j = 0; j<20; j++) cost+=dist[curpos+j][i*20+j];
                if((cost==mindist)&&(re[i]!=minl)) cnt++;
                if(cost<mindist) mindist = cost, minl = re[i], cnt = 0;
            }
            val[curpos][1] = mindist;
            rec[curpos][1] = ((cnt==0)?(minl):('?'));
        }
        if(n-curpos>=19)
        {
            mindist = 0x3f3f3f3f, cnt = 0;
            for(int i = 0; i<27; i++)
            {
                cost = 0x3f3f3f3f;
                for(int j = 0; j<20; j++)
                {
                    int curc = 0, p1 = 0, p2 = 0;
                    while((p1<19)&&(p2<20))
                    {
                        if(p2==j) p2++;
                        curc+=dist[curpos+p1][i*20+p2];
                        p1++,p2++;
                    }
                    cost = min(cost,curc);
                }
                if((cost==mindist)&&(re[i]!=minl)) cnt++;
                if(cost<mindist) mindist = cost, minl = re[i], cnt = 0;
            }
            val[curpos][2] = mindist;
            rec[curpos][2] = ((cnt==0)?(minl):('?'));
        }
    }
    for(int i = 1; i<=n; i++) dp[i] = 0x3f3f3f3f;
    for(int i = 0; i<=n; i++)
    {
        if((i+19<=n)&&(rec[i][2]!='?')&&(dp[i]+val[i][2]<dp[i+19])) dp[i+19] = dp[i]+val[i][2], ans[i+19] = ans[i]+rec[i][2];
        if((i+20<=n)&&(rec[i][1]!='?')&&(dp[i]+val[i][1]<dp[i+20])) dp[i+20] = dp[i]+val[i][1], ans[i+20] = ans[i]+rec[i][1];
        if((i+21<=n)&&(rec[i][0]!='?')&&(dp[i]+val[i][0]<dp[i+21])) dp[i+21] = dp[i]+val[i][0], ans[i+21] = ans[i]+rec[i][0];
    }
    outfile << ans[n] << endl;
}
