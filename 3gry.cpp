#include <iostream>
//#include <thread>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <conio.h>
using namespace std;
// gra w hasła v1.0
//pierwsza podstawowa wersja, bardzo ulungowa: hasla zakodowane w programie na sztywno, brak mozliwosci edycji po kompilacji

int losujHaslo(int max)
{
    int result = (rand() % max);
    return result;
}

void wyswietlHaslo(string * hasla, string * zakazane, int numer)
{
    cout<<"Hasło brzmi: "<<hasla[numer]<<endl;
    cout<<"wyrażenie zakazane brzmi: "<<zakazane[numer]<<endl;
    cout<<"\nPo odgadnięciu hasła, wciśnij dowolny klawisz.\n";
    getch();

}

void wyswietlHasloKalambury(string * hasla, int numer)
{
    cout<<"Hasło brzmi: "<<hasla[numer]<<endl;
    cout<<"\nPo odgadnięciu hasła, wciśnij dowolny klawisz.\n";
    getch();

}

void czolko()
{
    char wybor = '5';
    int haslo = 0;      //25 hasel
    string hasla[] = {"kominiarz", "policjant", "długopis", "ząb", "mięsień", "nóż", "kot", "telefon", "kwiat", "komputer", "kieliszek", "kawa", "samochód", "drzewo", "skrzypce", "shrek", "okno", "dom", "rycerz", "lustro", "szczoteczka", "mikrofon", "herbata", "rower", "kaloryfer"};
    string zakazane[] = {"komin", "mandat", "wkład", "dentysta", "biceps", "tnie", "miauczy", "dzwoni", "doniczka", "pecet", "wódka", "ziarna", "jeździ", "liście", "smyczek", "ogr", "rama", "mieszkanie", "lancelot", "zwierciadło", "do zębów", "wokalista", "czarna co myśli rozjaśnia", "góral", "grzeje"};
    while (wybor != '2')
    {
        system("CLS");
        cout<<"Czółko.\nWybierz czynność:\n1. Losuj hasło\n2. Menu główne\n";
        cin>>wybor;
        switch (wybor)
        {
            case '1': {haslo = losujHaslo(25); wyswietlHaslo(hasla, zakazane, haslo);break;}
            case '2': cout<<"Powrót do menu...\n"; Sleep(1500);break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(1000);
        }
    }
}

void czolkoBatman()
{
    char wybor = '5';
    int haslo = 0;      //10 hasel
    string hasla[] = {"bruce wayne", "peleryna", "nietoperz", "bat-mobil", "gotham", "joker", "two-face", "alfred", "robin", "james gordon"};
    string zakazane[] = {"batman", "na plecach", "symbol", "samochód", "miasto", "zielone włosy", "prawnik", "lokaj", "uczeń", "komisarz"};
    while (wybor != '2')
    {
        system("CLS");
        cout<<"Czółko - wersja Batmaniasta.\nWybierz czynność:\n1. Losuj hasło\n2. Menu główne\n";
        cin>>wybor;
        switch (wybor)
        {
            case '1': {haslo = losujHaslo(10); wyswietlHaslo(hasla, zakazane, haslo);break;}
            case '2': cout<<"Powrót do menu...\n"; Sleep(1500);break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(1000);
        }
    }
}

void kalambury()
{
    char wybor = '5';
    int haslo = 0;      //15 hasel
    string hasla[] = {"lokomotywa", "kot w butach", "księżniczka", "kac", "ubijać masło", "pilnować czegoś jak oka w głowie", "mieć głowę na karku", "błędny rycerz", "mijać się z celem", "skoczyć w ogień", "upiec dwie pieczenie na jednym ogniu", "mięso armatnie", "kurka wodna", "psia kość", "skrót myślowy"};
    while (wybor != '2')
    {
        system("CLS");
        cout<<"Kalambury.\nWybierz czynność:\n1. Losuj hasło\n2. Menu główne\n";
        cin>>wybor;
        switch (wybor)
        {
            case '1': {haslo = losujHaslo(15); wyswietlHasloKalambury(hasla, haslo);break;}
            case '2': cout<<"Powrót do menu...\n"; Sleep(1500);break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(1000);
        }
    }
}


void menu()
{
    srand(time(NULL));
    char wybor = '5';
    while(wybor != '0')
    {
        system("CLS");
        cout<<"Wybierz grę\n";
        cout<<"1. Kalambury\n2. Czółko (różne hasła)\n3. Czółko(Batman)\n0. Wyjście\n";
        cin>>wybor;
        switch (wybor)
        {
            case '1': kalambury();break;
            case '2': czolko();break;
            case '3': czolkoBatman();break;
            case '0': cout<<"Do widzenia :)\n";break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(1000);
        }
    }
}
int main()
{
    system("chcp 65001");
    menu();    
    system("pause");
    return 0;
}


/*
string dupa[] = {"żołądek jak bęben", "dópa różowa"};

cout << dupa << endl;
    for (int i=0; i<2; i++)
    {
        cout<<dupa[i]<<endl;
    }
//*/