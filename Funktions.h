#ifndef FUNKTIONS_H_INCLUDED
#define FUNKTIONS_H_INCLUDED

int getKey(); //czeka na kliknięcie klawisza przez użytkownika i przekazuje zmodyfikowany kod klawisza

int getKey_0_9(int minValue=0, int maxValue=9, bool exitStatus=false); //czeka na kliknięcie klawisza przez użytkownika i przekazuje wartość od 0 do 9

long mathPower(int number, int power); //liczy potęgi matematyczne (argument numer - liczba która ma być potęgowana, power - potęga

void Color(int color); //ustawia kolor konsoli (od 0 do 255)

void SCP(int position_X, int position_Y); //ustawia pozycje kursora w konsoli (Set Cursor Position)

void pause(); //oczekuje na reakcje użytkownika

void WindowSize(short windowWidth, short windowHeight); //zmienia rozmiar okna

int UID_creator();

#endif // FUNKTIONS_H_INCLUDED
