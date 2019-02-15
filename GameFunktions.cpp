#include <iostream>
#include <windows.h>

#include "Funktions.h"

using namespace std;

int input(bool printKey=false, int mini=0, int maxi=0)
{
    int x=0, inp=0, result=0;
    char table[10];
    for(;;)
    {
        inp=getKey();
        if(inp>=48 && inp<=58 && x<9) {table[x]=inp; x++; if(printKey==true) cout<<(char)inp;}
        else if(inp==8 && x>0) { if(printKey==true) cout<<"\b \b"; x--;}
        else if(inp==13) break;
        else continue;
    }
    int j=x-1;
    for(int i=0; i<x; i++)
    {
        result+=(((int)table[j]-48)*mathPower(10, i));
        j--;
    }
    if(mini!=0 && maxi!=0)
    {
        if(result<mini) result=mini;
        else if(result>maxi) result=maxi;
    }

    return result;
}


void draw(int Size, int width, int height)
{
    system("cls");

    for(int x=0; x<Size; x++)
        for(int y=0; y<Size; y++)
        {
            if(x!=Size-1 && y!=Size-1)
            {
                SCP(2+(x*3),(y*2));
                cout<<(char)179;
                SCP((x*3),1+(y*2));
                cout<<(char)196<<(char)196<<(char)197;
            }
            else if(x==Size-1 && y!=Size-1)
            {
                SCP((x*3),1+(y*2));
                cout<<(char)196<<(char)196;
            }
            else if(x!=Size-1 && y==Size-1)
            {
                SCP(2+(x*3),(y*2));
                cout<<(char)179;
            }
        }
    for(int i=0; i<height; i++)
    {
        SCP(width,i);
        cout<<(char)179;
    }
    SCP(width,1);
    cout<<(char)197;
    for(int i=0; i<19; i++)
    {
        SCP(width+1+i,1);
        cout<<(char)196;
    }


    SCP(width+2,0);
    cout<<"Informacje o grze";
    SCP(width+1,2);
    cout<<"Kolej gracza :";
    SCP(width+1,3);
    cout<<"Symbol       :";
    SCP(width+1,4);
    cout<<"Punkty       :";
    SCP(width+1,5);
    cout<<"Rekord       :";
}
