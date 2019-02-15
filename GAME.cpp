#include <iostream>
#include <windows.h>
#include <ctime>

#include "Funktions.h"
#include "GameFunktions.h"

using namespace std;

///zmienne
int tabSize=3; //odpowiada za komunikowanie ile pól posiada "plansza" w jednym rzędzie i ile jest rzędów
int width=0, height=0; //przesunięcie i rozmiar informacji podczas gry (prawe okienko w grze)
int tab[27][27]; //tablica odpowiadająca za same pola w rozgrywce i oflagowywanie ich jeżeli należy do gracza
int posX=0, posY=0; //pozycja x i y
int player=1, nowPlayer=2, humans=1 , maxPlayer=2, bots=1;
int winScore=3, minScore=2; //ile potrzeba symboli w rzędzie by wgrać całą rozgrywke i ile potrzeba symboli w rzędzie by naliczało graczowi punkty
int maxTour=9; //mówi ile maksymalnie tur może zostać wykonanych
int mainPlayer[]={0,0,0,0,0,0,0,0};

short win=-1; //znacznik zwycięscy przybiera wartość od -1 do 8

int playerScore[]= {0,0,0,0,0,0,0,0}; //punkty poszczególnych graczy (graczy liczymy tu od 0 a nie od 1 jak w "player")
int playerMaxScore[]= {0,0,0,0,0,0,0,0}; //najlepszy wynik symboli z rzędu graczy (graczy liczymy tu od 0 a nie od 1 jak w "player")







//odpowiada za zmienianie koloru na polach na podstawie tabeli i koordynatów x i y (startAtColor - odpowiednik backgroundColor)
void color2(int startAtColor)
{
    if(tab[posX][posY]==1) Color(startAtColor+10);
    else if(tab[posX][posY]==2) Color(startAtColor+14);
    else if(tab[posX][posY]==3) Color(startAtColor+11);
    else if(tab[posX][posY]==4) Color(startAtColor+13);
    else if(tab[posX][posY]==5) Color(startAtColor+12);
    else if(tab[posX][posY]==6) Color(startAtColor+15);
    else if(tab[posX][posY]==7) Color(startAtColor+6);
    else if(tab[posX][posY]==8) Color(startAtColor+8);
}

//odpowiada za rysowanie odpowiedniego znaku dla danego gracza
void drawChar(int x, int y)
{
    int what=tab[x][y];
    char ch[2]= {' ',' '};
    SCP((x*3),(y*2));

    if(what==1)
    {
        ch[0]='>';
        ch[1]='<';
    }
    else if(what==2)
    {
        ch[0]='(';
        ch[1]=')';
    }
    else if(what==3)
    {
        ch[0]='[';
        ch[1]=']';
    }
    else if(what==4)
    {
        ch[0]='<';
        ch[1]='>';
    }
    else if(what==5)
    {
        ch[0]=')';
        ch[1]='(';
    }
    else if(what==6)
    {
        ch[0]='}';
        ch[1]='{';
    }
    else if(what==7)
    {
        ch[0]='\\';
        ch[1]='\\';
    }
    else if(what==8)
    {
        ch[0]='/';
        ch[1]='/';
    }
    cout<<ch[0]<<ch[1];
}

//(check and select position) sprawdza czy pozycja jest już zajęta przez innego gracza jeżeli nie zostaje nadpisywana przez gracza aktualnego
bool checkAndSelPos(int x, int y)
{
    if(tab[x][y]==0)
    {
        tab[x][y]=player;
        Color(240);
        drawChar(x,y);
        Color(15);
        return true;
    }
    else
        return false;
}

//pokazuje odpowiednie informacje użytkownikowi w okienku prawej stronie
void showInfo()
{


    Color(15);
    int x=width-4;


    SCP(x,2);
    cout<<player<<" ";


    char ch[2]= {' ',' '};
    if(player==1)
    {
        ch[0]='>';
        ch[1]='<';
    }
    else if(player==2)
    {
        ch[0]='(';
        ch[1]=')';
    }
    else if(player==3)
    {
        ch[0]='[';
        ch[1]=']';
    }
    else if(player==4)
    {
        ch[0]='<';
        ch[1]='>';
    }
    else if(player==5)
    {
        ch[0]=')';
        ch[1]='(';
    }
    else if(player==6)
    {
        ch[0]='}';
        ch[1]='{';
    }
    else if(player==7)
    {
        ch[0]='\\';
        ch[1]='\\';
    }
    else if(player==8)
    {
        ch[0]='/';
        ch[1]='/';
    }
    SCP(x,3);
    cout<<ch[0]<<ch[1]<<" ";


    SCP(x,4);
    cout<<playerScore[player-1]<<"  ";
    SCP(x,5);
    cout<<playerMaxScore[player-1]<<"  ";
}

//odpowiada za poruszanie sie po planszy
int movement(char where)
{
    Color(15);
    color2(0);
    drawChar(posX,posY);

    if(where=='u')
    {
        posY--;
        if(posY<0) posY=tabSize-1;
        if(posY>=tabSize) posY=0;
    }
    else if(where=='d')
    {
        posY++;
        if(posY<0) posY=tabSize-1;
        if(posY>=tabSize) posY=0;
    }
    else if(where=='r')
    {
        posX++;
        if(posX<0) posX=tabSize-1;
        if(posX>=tabSize) posX=0;
    }
    else if(where=='l')
    {
        posX--;
        if(posX<0) posX=tabSize-1;
        if(posX>=tabSize) posX=0;
    }
    Color(240);
    drawChar(posX,posY);
}

//jeżeli był remis porównuje punkty graczy i typuje zwycięsce bądź jego brak
int checkScoreWinner()
{
    int table[]= {1,2,3,4,5,6,7,8}, table2[8];
    for(int i=0; i<8; i++)
    {
        table2[i]=playerScore[i];
    }

    for (int i=1; i<nowPlayer; i++)
    {
        for (int j=nowPlayer-1; j>=1; j--)
        {
            if (table2[j]>table2[j-1])
            {
                int buff=table2[j-1];
                table2[j-1]=table2[j];
                table2[j]=buff;

                buff=table[j-1];
                table[j-1]=table[j];
                table[j]=buff;
            }
        }
    }
    if (table2[0]==table2[1]) return 0;
    else
    {
        return table[0];
    }
}

//najważniejsza funkcja/algorytm odpowiada za: sprawdzanie czy ktoś nie wygrał stawiając maksymalną wartość symboli w grze; policzenie punktów gracza; sprawdzenie najdłuższego ciągu symboli gracza
bool checkScore()
{
    int check[4], p=player-1;
    playerScore[p]=0;

    for(int i=0; i<tabSize; i++)
    {
        check[0]=0;
        check[1]=0;
        for(int j=0; j<tabSize; j++)
        {
            if(tab[i][j]==player)
            {
                check[0]++;
                for(int SP=1; (SP-1)<(check[0]-minScore+1); SP++)
                {
                    playerScore[p]+=SP;
                }
                if(check[0]==winScore)
                {
                    win=player;
                    return true;
                }
            }
            else
            {
                if(playerMaxScore[p]<check[0]) playerMaxScore[p]=check[0];
                check[0]=0;
            }



            if(tab[j][i]==player)
            {
                check[1]++;
                for(int SP=1; (SP-1)<(check[1]-minScore+1); SP++)
                {
                    playerScore[p]+=SP;
                }
                if(check[1]==winScore)
                {
                    win=player;
                    return true;
                }
            }
            else
            {
                if(playerMaxScore[p]<check[1]) playerMaxScore[p]=check[1];
                check[1]=0;
            }
        }
    }

    for(int i=-(tabSize-1); i<tabSize; i++)
    {
        int x=0, y=0;
        if(i<0)
        {
            y=-i;
        }
        else x=i;
        check[2]=0;
        check[3]=0;

        for(int j=0; j<tabSize; j++)
        {
            if(tab[x+j][y+j]==player)
            {
                check[2]++;
                for(int SP=1; (SP-1)<(check[2]-minScore+1); SP++)
                {
                    playerScore[p]+=SP;
                }
                if(check[2]==winScore)
                {
                    win=player;
                    return true;
                }
            }
            else
            {
                if(playerMaxScore[p]<check[2]) playerMaxScore[p]=check[2];
                check[2]=0;
            }


            if(y>0) x=tabSize-1;
            /**< FIX: */
            if(tab[x-j][y+j]==player && (x-j>=0))
            {
                check[3]++;
                for(int SP=1; (SP-1)<(check[3]-minScore+1); SP++)
                {
                    playerScore[p]+=SP;
                }
                if(check[3]==winScore)
                {
                    win=player;
                    return true;
                }
            }
            else
            {
                if(playerMaxScore[p]<check[3]) playerMaxScore[p]=check[3];
                check[3]=0;
            }
        }
    }
    return false;
}

//wykonuje kroki związane z zmianą gracza
void enter()
{
    maxTour--;
    if(maxTour==0) win=0;
    checkScore();

    player++;
    if(player>nowPlayer) player=1;
}

//główna funkcja gry, pętla związana z ruchami graczy
int game()
{
    Color(240);
    drawChar(posX,posY);

    while(win==-1)
    {
        if(player<humans+1)
        {
            showInfo();
            bool playerMove=true;
            while(playerMove==true)
            {
                SCP((posX*3),(posY*2));
                switch(getKey())
                {
                case 87:
                case 119:
                case 372: ///up
                    movement('u');
                    break;
                case 65:
                case 97:
                case 375: ///left
                    movement('l');
                    break;
                case 83:
                case 115:
                case 380: ///down
                    movement('d');
                    break;
                case 68:
                case 100:
                case 377: ///right
                    movement('r');
                    break;
                case 32:
                case 13: ///enter
                    if(checkAndSelPos(posX,posY)==true) { enter(); playerMove=false; }
                    break;
                case 27: ///esc
                    break;
                }
            }
        }
        else
        {

            int x=0, y=0, xp=posX, yp=posY;

            srand(time(NULL));
            do
            {
                x=rand()%tabSize, y=rand()%tabSize;

                if(tab[x][y]==0) break;
                x=0, y=0;
            }
            while(true);

            tab[x][y]=player;
            Color(15);
            posX=x; posY=y;
            color2(0);
            drawChar(x,y);

            posX=xp; posY=yp;
            Color(240);
            drawChar(posX,posY);

            enter();
        }
    }
    return win;
}

//ustawienia gry
void settings()
{
    bool tf=true;
    while(tf==true)
    {
        Color(7);
    WindowSize(40, 10);
        system("cls");

        cout<<"   Ustawienia"<<endl<<endl
        <<"1. Zmien rozmiar planszy           :"<<endl
        <<"2. Zmien ilosc graczy              :"<<endl
        <<"3. Zmien ilosc botow               :"<<endl
        <<"4. Zmien ilosc znakow do wygranej  :"<<endl
        <<"5. Zmien od ilu znakow liczy punkty:"<<endl;
        Color(11);
        for(int i=1; i<6; i++)
        {
            SCP(37,i+1);
            if(i==1) cout<<tabSize;
            else if(i==2) cout<<humans;
            else if(i==3) cout<<bots;
            else if(i==4) cout<<winScore;
            else if(i==5) cout<<minScore<<endl;
        }
        Color(7);

        switch(getKey_0_9(1, 5, true))
        {
        case 1:
            cout << "Rozmiar planszy (3-26): ";
            tabSize=input(true,3,26);
            if(tabSize<=9)
                maxPlayer=tabSize-1;
            else if(tabSize<=26)
                maxPlayer=8;
            maxTour=tabSize*tabSize;
            if(nowPlayer>maxPlayer) {nowPlayer=maxPlayer; if(humans>nowPlayer) humans=nowPlayer; bots=nowPlayer-humans;}
            if(humans<2) {nowPlayer=humans+bots; bots=1;}
            if(winScore>tabSize) winScore=tabSize;
            if(minScore>tabSize) minScore=tabSize;
            break;


        case 2:
            cout << endl << "Ilosc graczy (1-"<<maxPlayer<<"): ";
            humans=input(true,1,maxPlayer);
            nowPlayer=humans+bots;
            if(nowPlayer>maxPlayer) {nowPlayer=maxPlayer; if(humans>nowPlayer) humans=nowPlayer; bots=nowPlayer-humans;}
            if(humans<2) {nowPlayer=humans+bots; bots=1;}
            break;


        case 4:
            cout << endl << "Znakow do wygranej (3-"<<tabSize<<"): ";
            winScore=input(true,3,tabSize);
            break;


        case 5:
            cout << endl << "Punkty od znakow (2-"<<tabSize<<"): ";
            minScore=input(true,3,tabSize);
            break;


        case -1:
            tf=false;
            break;

        case 3:
            int minVal=1;
            if(humans>1) minVal=0;
            cout << endl << "Ilosc botow ("<<minVal<<"-"<<maxPlayer-humans<<"): ";
            bots=input(true,minVal,maxPlayer-humans);
            nowPlayer=humans+bots;
            if(nowPlayer>maxPlayer) {nowPlayer=maxPlayer; if(humans>nowPlayer) humans=nowPlayer; bots=nowPlayer-humans;}
            if(humans<2) {nowPlayer=humans+bots; bots=1;}
            break;
        }
    }
}

//bazowa funkcja która załącza gre
void mainGame()
{
    Color(7);
    system("cls");

    if(tabSize==3)
    {
        width=30;
        height=6;
        system("mode 30, 6");
    }
    else if(tabSize==4)
    {
        width=33;
        height=7;
        system("mode 33, 7");
    }
    else if(tabSize==5)
    {
        width=36;
        height=9;
        system("mode 36, 9");
    }
    else if(tabSize>5)
    {
        width=33+(3*(tabSize-4));
        height=7+(2*(tabSize-4));
        WindowSize(width, height);
    }


    for(int i=0; i<tabSize; i++)
        for(int j=0; j<tabSize; j++)
            tab[i][j]=0;


    draw(tabSize, width-20, height);

    int whoWin = game();

    if(whoWin==0) whoWin=checkScoreWinner();
    else checkScoreWinner();

    Color(11);
    SCP(width/2-9,height/2-1);
    if(whoWin!=0)
    {
        cout<<" wygral gracz: ";
        Color(10);
        cout<<whoWin<<"  ";
        Color(11);
        SCP(width/2-9,height/2);
        cout<<" punkty:          ";
        Color(10);
        SCP(width/2,height/2);
        cout<<playerScore[whoWin-1];

    }
    else cout<<" brak zwyciescy     ";

    Color(7);

    SCP(width/2-10,height/2-2);
    cout<<(char)197;
    for(int i=0; i<18; i++)
        cout<<(char)196;
    cout<<(char)197;

    SCP(width/2-10,height/2+1);
    cout<<(char)197;
    for(int i=0; i<18; i++)
        cout<<(char)196;
    cout<<(char)197;

    SCP(width/2-10,height/2-1);
    cout<<(char)179;
    SCP(width/2+9,height/2-1);
    cout<<(char)179;
    SCP(width/2-10,height/2);
    cout<<(char)179;
    SCP(width/2+9,height/2);
    cout<<(char)179;

    pause();
    player=1;
    win=-1;
    posX=0;
    posY=0;
    for(int i=0; i<8; i++)
    {
        playerScore[i]= 0;
        playerMaxScore[i]= 0;
    }
}

//menu gry
void menu()
{
    for(;;)
    {
    WindowSize(40, 10);
        system("cls");
        Color(7);

        cout<<"   Menu Gry"<<endl<<endl
        <<"1. Graj"<<endl
        <<"2. Ustawienia"<<endl;

        int Count=getKey_0_9(1, 2);
        if(Count==1) mainGame();
        if(Count==2) settings();
    }
}



