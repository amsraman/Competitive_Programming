#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    ifstream infile("idontlikeyou.txt");
    string arra[8];
    string octalbin[8] = {"000","001","010","011","100","101","110","111"};
    string octal = "01234567";
    string hex = "0123456789ABCDEF";
    string hexbin[16] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
    string inp, bin;
    for(int i = 0; i<8; i++)
    {
        infile >> inp;
        for(int j = 0; j<6; j++)
        {
            bin = bin+hexbin[hex.find(inp[j])];
        }
        for(int j = 0; j<8; j++)
        {
            for(int k = 0; k<8; k++)
            {
                if(octalbin[k]==bin.substr(0,3))
                {
                    arra[7-i] = arra[7-i] + octal[k];
                    bin.erase(0,3);
                    break;
                }
            }
        }
    }
    int point[2];
    char i;
    int n, d, direc[8][2] = {0,1,1,1,1,0,1,-1,0,-1,-1,-1,-1,0,-1,1};
    for(int intelcorei5tbh = 0; intelcorei5tbh<5; intelcorei5tbh++)
    {
        infile >> point[0] >> point[1] >> i >> n;
        point[0] = 8 - point[0];
        point[1]--;
        switch(i)
        {
        case 'A':
            d = 2;
            break;
        case 'B':
            d = 6;
            break;
        case 'L':
            d = 0;
            break;
        case 'R':
            d = 4;
            break;
        }
        for(int i = 0; i<n; i++)
        {
            d = (d+(arra[point[0]][point[1]]-'0')-4)%8;
            if(d<0)
            {
                d = d+8;
            }
            point[0] = point[0] + direc[d][0];
            point[1] = point[1] + direc[d][1];
            if(point[0]==-1)
            {
                point[0] = 7;
            }
            else if(point[0]==8)
            {
                point[0] = 0;
            }
            if(point[1]==-1)
            {
                point[1] = 7;
            }
            else if(point[1]==8)
            {
                point[1] = 0;
            }
        }
        cout << 8-point[0] << " " << point[1]+1 << endl;
    }
    return 0;
}
