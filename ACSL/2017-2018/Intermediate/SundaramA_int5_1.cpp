#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int maxi(int a, int b, int c)
{
    if(a>b)
    {
        if(a>c)
        {
            return a;
        }
        else
        {
            return c;
        }
    }
    else
    {
        if(b>c)
        {
            return b;
        }
        else
        {
            return c;
        }
    }
}

int main()
{
    string card = "23456789TJQKA";
    int value[13] = {2,3,4,5,6,7,8,0,-10,11,12,13,14};
    int p, puppet, n, finall;
    for(int z = 0; z<5; z++)
    {
        int type = 0;
        char a, moves[7];
        string deck, finaal;
        cout << "Enter initial point value: " << endl;
        cin >> p;
        cout << "Enter initial deck: " << endl;
        for(int i = 0; i<3; i++)
        {
            cin >> a;
            deck = deck + a;
        }
        for(int i = 0; i<7; i++)
        {
            cin >> moves[i];
        }
        for(int i = 0; i<3; i++)
        {
            if(type==0)
            {
                puppet = maxi(card.find(deck[0]),card.find(deck[1]),card.find(deck[2]));
                p = p + value[puppet];
                if((card[puppet]=='A')&&(p>99))
                {
                    p = p - 13;
                }
                if(p>99)
                {
                    type++;
                    finall = p;
                    p = 0;
                    finaal = "dealer";
                }
                n = deck.find(card[puppet]);
                deck.erase(n,1);
                deck = deck + moves[2*i];
                p = p + value[card.find(moves[2*i+1])];
                if((moves[2*i+1]=='A')&&(p>99))
                {
                    p = p - 13;
                }
                if(p>99)
                {
                    type++;
                    finall = p;
                    p = 0;
                    finaal = "player";
                }
            }
        }
        if(type==0)
        {
            puppet = maxi(card.find(deck[0]),card.find(deck[1]),card.find(deck[2]));
            p = p + value[puppet];
            if((card[puppet]=='A')&&(p>99))
            {
                p = p - 13;
            }
            if(p>99)
            {
                type++;
                finall = p;
                p = 0;
                finaal = "dealer";
            }
        }
        if(type==1)
        {
            cout << finall << ", " << finaal << endl;
        }
        else
        {
            cout << "Game doesn't end" << endl;
        }
    }
    return 0;
}
