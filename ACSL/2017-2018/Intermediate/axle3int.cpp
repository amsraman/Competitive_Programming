#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    string inp;
    string arra[8];
    string hex1 = "0123456789ABCDEF";
    string hex2[16] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
    ifstream infile("dontgiveafuckaboutthelogang.txt");
    for(int i = 0; i<8; i++)
    {
        infile >> inp;
        if(inp.length()==1)
        {
            arra[i] = hex2[0] + hex2[hex1.find(inp)];
        }
        else
        {
            arra[i] = hex2[hex1.find(inp[0])] + hex2[hex1.find(inp[1])];
        }
    }
    int used[8][8];
    int point[2];
    char i;
    int n, d, direc[4][2] = {0,1,1,0,0,-1,-1,0};
    for(int thisisanincrementvariabletbh = 0; thisisanincrementvariabletbh<5; thisisanincrementvariabletbh++)
    {
        for(int i = 0; i<8; i++)
        {
            for(int j = 0; j<8; j++)
            {
                used[i][j] = 0;
            }
        }
        infile >> point[0] >> point[1] >> i >> n;
        point[0]--;
        point[1]--;
        switch(i)
        {
        case 'A':
            d = 1;
            break;
        case 'B':
            d = 3;
            break;
        case 'L':
            d = 0;
            break;
        case 'R':
            d = 2;
            break;
        }
        if(arra[point[0]][point[1]]=='1')
        {
            d--;
            if(d<0)
            {
                d = d+4;
            }
            used[point[0]][point[1]]++;
        }
        for(int i = 0; i<n; i++)
        {
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
            if(arra[point[0]][point[1]]=='1')
            {
                d = (d+used[point[0]][point[1]]-1)%4;
                if(d<0)
                {
                    d = d+4;
                }
                used[point[0]][point[1]]++;
            }
        }
        cout << point[0]+1 << " " << point[1]+1 << endl;
    }
    return 0;
}
