#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <map>
#include <functional>
#include <iomanip>
#include <vector>
#include <utility>
using namespace std;
// gra w hasła v2.0
// wersja ulepszona: hasla zapisane w plikach tekstowych, wiec mozna dodac nowe hasla, a program je odczyta i zapisze sobie, bo dziala na wektorach wiec
//nawet jesli pliki z haslami beda bardzo duze, to program sobie zrobi odpowiednio duze tablice. Pierwsze wydanie tej wersji, na poczatek aby dzialalo
//troche jeszcze ulungowe; kazda gra ma osobne menu, kazde wyswietlanie jest osobne, troche murzynski kod

vector<string> haslaKal;
vector<pair<string, string>> haslaCz;
vector<pair<string, string>> haslaCzBat;

int losujHaslo(int rozmiar)
{
    int result = (rand() % rozmiar);//cout<<endl<<rozmiar<<endl;
    return result;
}

void wyswietlHasloCz(int numer)
{
    cout<<"Hasło brzmi: "<<haslaCz[numer].first<<endl;
    cout<<"wyrażenie zakazane brzmi: "<<haslaCz[numer].second<<endl;
    cout<<"\nPo odgadnięciu hasła, wciśnij dowolny klawisz.\n";
    getch();
}

void wyswietlHasloCzBat(int numer)
{
    cout<<"Hasło brzmi: "<<haslaCzBat[numer].first<<endl;
    cout<<"wyrażenie zakazane brzmi: "<<haslaCzBat[numer].second<<endl;
    cout<<"\nPo odgadnięciu hasła, wciśnij dowolny klawisz.\n";
    getch();
}

void wyswietlHasloKalambury(int numer)
{
    cout<<"Hasło brzmi: "<<haslaKal[numer]<<endl;
    cout<<"\nPo odgadnięciu hasła, wciśnij dowolny klawisz.\n";
    getch();
}

void czolko()
{
    char wybor = '5';
    int haslo = 0;
    while (wybor != '2')
    {
        system("CLS");
        cout<<"Czółko.\nWybierz czynność:\n1. Losuj hasło\n2. Menu główne\n";
        cin>>wybor;
        switch (wybor)
        {
            case '1': {haslo = losujHaslo(haslaCz.size()); wyswietlHasloCz(haslo);break;}
            case '2': cout<<"Powrót do menu...\n"; Sleep(1000);break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(1000);
        }
    }
}

void czolkoBatman()
{
    char wybor = '5';
    int haslo = 0;
    while (wybor != '2')
    {
        system("CLS");
        cout<<"Czółko - wersja Batmaniasta.\nWybierz czynność:\n1. Losuj hasło\n2. Menu główne\n";
        cin>>wybor;
        switch (wybor)
        {
            case '1': {haslo = losujHaslo(haslaCzBat.size()); wyswietlHasloCzBat(haslo);break;}
            case '2': cout<<"Powrót do menu...\n"; Sleep(1000);break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(1000);
        }
    }
}

void kalambury()
{
    char wybor = '5';
    int haslo = 0;
    while (wybor != '2')
    {
        system("CLS");
        cout<<"Kalambury.\nWybierz czynność:\n1. Losuj hasło\n2. Menu główne\n";
        cin>>wybor;
        switch (wybor)
        {
            case '1': {haslo = losujHaslo(haslaKal.size()); wyswietlHasloKalambury(haslo);break;}
            case '2': cout<<"Powrót do menu...\n"; Sleep(1000);break;
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

void pobierzHasla(fstream &hkal, fstream &hcz, fstream &hczb)
{
    string linia;
    uint8_t nr_linii = 1;
    pair<string, string> para;
    while (!hkal.eof())
    {
        getline(hkal, linia);
        haslaKal.push_back(linia);
    }
    
    while (getline(hcz,linia))
    {
        switch(nr_linii)
        {
            case 1: para.first = linia; break;
            case 2: para.second = linia; break;
            case 3: break;
        }
        nr_linii++;
        if (nr_linii > 3) 
        {
            haslaCz.push_back(para);
            nr_linii = 1;
        }
    }

    while (getline(hczb,linia))
    {
        switch(nr_linii)
        {
            case 1: para.first = linia; break;
            case 2: para.second = linia; break;
            case 3: break;
        }
        nr_linii++;
        if (nr_linii > 3) 
        {
            haslaCzBat.push_back(para);
            nr_linii = 1;
        }
    }
}

void init()
{
    fstream hkal;
    fstream hcz;
    fstream hczb;
    hkal.open("hkal.txt", ios::in);
    if(hkal.good() != true) cout<<"Błąd odczytu hkal.txt"<<endl;
    hcz.open("hcz.txt", ios::in);
    if(hcz.good() != true) cout<<"Błąd odczytu hcz.txt"<<endl;
    hczb.open("hczb.txt", ios::in);
    if(hczb.good() != true) cout<<"Błąd odczytu hczb.txt"<<endl;

    if((hkal.good() == true) && (hcz.good() == true) && (hczb.good() == true)) 
    {
        pobierzHasla(hkal, hcz, hczb);
        hkal.close();
        hcz.close();
        hczb.close();
        menu();
    }
}

int main()
{
    system("chcp 65001");
    init();
    system("pause");
    return 0;
}


/*

//*/