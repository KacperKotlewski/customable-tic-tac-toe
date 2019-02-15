#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <conio.h>
#include <Lmcons.h>
#include <ctime>

using namespace std;

int getKey()
{
    bool fs=false; int x;
	for(;;)
	{
		x = getch();
		switch (x)
		{
		case 0:
		case 224:
			fs=true;
            break;
		default:
			if (fs==true)
            {
				x=300+x;
				return x;
			} else return x;
			fs=false;
		}
	}
}

int getKey_0_9(int minValue=0, int maxValue=9, bool exitStatus=false)
{
    for(;;)
    {
        int v=getKey();
        if(v-48>=minValue && v-48<=maxValue) return v-48;
        else if(exitStatus==true && v==27) return -1;
    }
}

long mathPower(int number, int power)
{
    if(power==0) return 1;
    long out=number;
    for(int i=0; i<power-1; i++)
        out=out*number;
    return out;
}

void Color(int color)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, color);
}

void SCP(int position_X, int position_Y)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { position_X, position_Y };
    SetConsoleCursorPosition(output, pos);
}

void pause()
{
    getch();
}

string to_string_int(int intiger)
{
    stringstream ss;
    ss << intiger;
    return ss.str();
}

void WindowSize(short windowWidth, short windowHeight)
{
    string str = "mode " + to_string_int( windowWidth ) + ", " + to_string_int( windowHeight );

    char wmode[str.length()];
    for(int i = 0; i<str.length(); i++)
        wmode[i]=str.at(i);

    system(wmode);

}

char base64ch[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789/-_";
int base64(int character)
{
    for(int i=0; i<65; i++)
        if(character==(int)base64ch[i]) return i+1;
}
int UID_creator()
{
    int reroll=1000;

    srand(time(NULL));
    char username[UNLEN+1], pcname[UNLEN+1];
    DWORD username_len = UNLEN+1;
    DWORD pcname_len = UNLEN+1;
    GetUserName(username, &username_len);
    GetComputerName(pcname, &pcname_len);
    string userID="", pcn(pcname), un(username);
    userID = pcn + "/" + un;
    string UIDtab[reroll];

    for(int i=0; i<reroll; i++)
    {
        string UIDs="";
        int UIDint=0;
        for(int i=0; i<userID.length(); i++)
            UIDint+=base64(userID.at(i));

        while(UIDint!=0)
        {
            char ch;
            if(UIDint>64) ch = base64ch[rand()%65];
            else ch = base64ch[rand()%UIDint];
            UIDs+=ch;
            UIDint-=base64(ch);
        }
        for(int i=0; i<UIDs.length(); i++)
            UIDint+=base64(UIDs.at(i));

        UIDtab[i]=UIDs;
    }
    for (int i=0; i<reroll; i++)
    {
        for (int j=reroll-1; j>0; j--)
        {
            string one=UIDtab[j], two=UIDtab[j-1];
            if (one.length()<two.length())
            {
                string buff=UIDtab[j-1];
                UIDtab[j-1]=UIDtab[j];
                UIDtab[j]=buff;
            }
        }
    }

    string UIDs = UIDtab[0];

    int UID=0;

    for(int i=0; i<UIDs.length(); i++)
        UID+=base64(UIDs.at(i))*mathPower(10, i/2);

    return UID;
}



