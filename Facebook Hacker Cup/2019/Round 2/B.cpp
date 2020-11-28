#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

int t, n, m, x, y, link[4000], siz[4000], ans[4000], minc;
bool united[4000][4000], dp[4001][4001];
vector<pair<int,int> > vec;

int f(int a)
{
	while(a!=link[a])
	{
		a = link[a];
	}
	return a;
}

void unite(int a, int b)
{
	a = f(a), b = f(b);
	if(a==b) return;
	if(siz[a]<siz[b]) swap(a,b);
	link[b] = a;
	siz[a]+=siz[b];
}

int main()
{
	ifstream fin("bitstrings_as_a_service.txt");
	ofstream fout("output.txt");
	fin >> t;
	for(int z = 0; z<t; z++)
	{
		fin >> n >> m;
		for(int i = 0; i<n; i++)
		{
			link[i] = i, siz[i] = 1, ans[i] = 0;
		}
		for(int i = 0; i<=n; i++)
		{
			for(int j = 0; j<=n; j++)
			{
				dp[i][j] = united[min(i,n-1)][min(j,n-1)] = false;
			}
		}
		minc = 0;
		for(int i = 0; i<m; i++)
		{
			fin >> x >> y;
			int lb = x-1, ub = y-1;
			while(lb<ub)
			{
				united[lb][ub] = true;
				lb++, ub--;
			}
		}
		for(int i = 0; i<n; i++)
		{
			for(int j = i+1; j<n; j++)
			{
				if(united[i][j])
				{
					unite(i,j);
				}
			}
		}
		for(int i = 0; i<n; i++)
		{
			if(i==link[i])
			{
				vec.push_back({siz[i],i});
			}
		}
		dp[0][0] = true;
		for(int i = 0; i<vec.size(); i++)
		{
			for(int j = 0; j<=n; j++)
			{
				dp[i+1][j] = dp[i][j];
				if((j>=vec[i].first)&&(dp[i][j-vec[i].first]))
				{
					dp[i+1][j] = true;
				}
			}
		}
		for(int i = 0; i<=n; i++)
		{
			if((dp[vec.size()][i])&&(abs(2*i-n)<abs(2*minc-n)))
			{
				minc = i;
			}
		}
		for(int i = vec.size()-1; i>=0; i--)
		{
			if((vec[i].first<=minc)&&(dp[i][minc-vec[i].first]))
			{
				for(int j = 0; j<n; j++)
				{
					if(f(j)==vec[i].second)
					{
						ans[j] = 1;
					}
				}
				minc-=vec[i].first;
			}
		}
		fout << "Case #" << z+1 << ": ";
		for(int i = 0; i<n; i++)
		{
			fout << ans[i];
		}
		fout << endl;
		vec.clear();
	}
}
