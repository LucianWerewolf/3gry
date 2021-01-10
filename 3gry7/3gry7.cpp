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

// gra w hasła v3.0
//nie zapisuje do wektorow tylko na biezaco zczytuje hasla z plikow.
//w trakcie roboty; dodaj przywrocenie wskaznika na poczatek pliku

int losujHaslo(fstream &plik, int gra)//niech liczy ilosc linii i wtedy randa z tego i wysyla spowrotem
{
    int ilosc_hasel = 0;
    string linia;
    int nr_linii = 1;
    switch(gra)
    {
        case 1:{if(plik.good() != true) cout<<"Błąd odczytu hkal.txt"<<endl; else cout<<"odczyt ok"<<endl;
            while (!plik.eof())//tutaj przed wejsciem do petli odczytuje ok, a po wyjsciu z niej juz nie moze odczytac. Dlaczego????
            {//dla kalambur w kliku jest haslo pod haslem wiec po prostu zliczamy ilosc linii
                getline(plik, linia);
                cout<<"test w petli nr "<<ilosc_hasel;
                if(plik.good() != true) cout<<"Błąd odczytu hkal.txt"<<endl; else cout<<": odczyt ok"<<endl;
                ilosc_hasel++;//znacznik przestawic na poczatek pliku!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            }if(plik.good() != true) cout<<"Błąd odczytu hkal.txt"<<endl; else cout<<"odczyt ok"<<endl;
        break;}
        case 2: case 3:{//policzymy ilosc hasel a nie linii czyli kolejno: 1. haslo, 2. slowo zakazane, 3. odstep(pusta linia) i dolicza tylko po napotkaniu linii 1
            while (getline(plik,linia))
            {
                switch(nr_linii)
                {
                    case 1: ilosc_hasel++; break;
                    case 2: case 3: break;
                }
                nr_linii++;
                if (nr_linii > 3) nr_linii = 1;
            }
        break;}
    } cout<<ilosc_hasel<<endl; //uzyskalismy ilosc hasel w pliku i zapisana jest ona w zmiennej ilosc_hasel
    int result = ((rand() % ilosc_hasel) + 1); cout<<result<<endl;//losujemy jedno z nich
    return result;//zwracamy numer wylosowanego hasla
}

string pobierzHaslo(fstream &plik, int numer, int gra, int polowa)
{
    int nr_hasla = 0;
    string linia;
    int nr_linii = 1;
    switch(gra)
    {
        case 1:{if(plik.good() != true) cout<<"Błąd odczytu hkal.txt"<<endl; else cout<<"odczyt ok"<<endl;
            while (nr_hasla < numer)
            {
                getline(plik, linia);
                nr_hasla++;
            }
        break;}
        case 2: case 3:{
            if (polowa = 1) 
            {
                while (nr_hasla < numer)
                {
                    switch(nr_linii)
                    {
                        case 1: getline(plik, linia); nr_hasla++; break;
                        case 2: case 3: break;
                    }
                    nr_linii++;
                    if (nr_linii > 3) nr_linii = 1;
                }
            }
            else if (polowa = 2) 
            {
                while (nr_hasla < numer)
                {
                    switch(nr_linii)
                    {
                        case 1: break;
                        case 2: {getline(plik, linia); nr_hasla++; break;}
                        case 3: break;
                    }
                    nr_linii++;
                    if (nr_linii > 3) nr_linii = 1;
                }
            }
        break;}
    }
    return linia;
}

void wyswietlHaslo(fstream &plik, int numer, int gra)//bezie czytal linie z pliku i wyswietlal
{
    int zakazane = numer + 1;
    switch(gra)
    {
        case 1: {cout<<"Hasło brzmi: "<<pobierzHaslo(plik, numer, gra, 1)<<endl; break;}
        case 2: {cout<<"Hasło brzmi: "<<pobierzHaslo(plik, numer, gra, 1)<<endl;// ostatnia cyfra mowi pobierajacej funkcji czy pobrac haslo(1) czy slowo zakazane(2)
            cout<<"wyrażenie zakazane brzmi: "<<pobierzHaslo(plik, zakazane, gra, 2)<<endl; break;}
        case 3: {cout<<"Hasło brzmi: "<<pobierzHaslo(plik, numer, gra, 1)<<endl;
            cout<<"wyrażenie zakazane brzmi: "<<pobierzHaslo(plik, zakazane, gra, 2)<<endl; break;}
    }
    cout<<"\nPo odgadnięciu hasła, wciśnij dowolny klawisz.\n";
    getch();
}


void menuGry(string nazwa, int gra, fstream &plikGry)//spr czy pobiera prawidlowo i przekaz dalej do losowania odpowiednio
{
    char wybor = '5';
    int nr_hasla = 0;
    while (wybor != '2')
    {
        system("CLS");
        cout<<nazwa<<".\nWybierz czynność:\n1. Losuj hasło\n2. Menu główne\n";
        wybor = getch();
        switch (wybor)
        {
            case '1': {
                if (gra == 1) {nr_hasla = losujHaslo(plikGry, gra); wyswietlHaslo(plikGry, nr_hasla, gra);}
                else if (gra == 2) {nr_hasla = losujHaslo(plikGry, gra); wyswietlHaslo(plikGry, nr_hasla, gra);}
                else if (gra == 3) {nr_hasla = losujHaslo(plikGry, gra); wyswietlHaslo(plikGry, nr_hasla, gra);}
                break;}
            case '2': cout<<"Powrót do menu...\n"; Sleep(1000);break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(1000);
        }
    }
}

void menuGlowne(fstream &hkal, fstream &hcz, fstream &hczb)
{
    srand(time(NULL));
    char wybor = '5';
    while(wybor != '0')
    {
        system("CLS");
        cout<<"Wybierz grę\n";
        cout<<"1. Kalambury\n2. Czółko (różne hasła)\n3. Czółko(Batman)\n0. Wyjście\n";
        wybor = getch();
        switch (wybor)
        {
            case '1': menuGry("Kalambury", 1, hkal);break;//spr czy przekazuje prawidlowo ; drugi argument to wybor z tym ze jako int a nie char
            case '2': menuGry("Czółko", 2, hcz);break;
            case '3': menuGry("Czółko-Batman", 3, hczb);break;
            case '0': cout<<"Do widzenia :)\n";break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(1000);
        }
    }
}

void init(fstream &hkal, fstream &hcz, fstream &hczb)
{
    hkal.open("hkal.txt", ios::in);
    if(hkal.good() != true) cout<<"Błąd odczytu hkal.txt"<<endl;
    hcz.open("hcz.txt", ios::in);
    if(hcz.good() != true) cout<<"Błąd odczytu hcz.txt"<<endl;
    hczb.open("hczb.txt", ios::in);
    if(hczb.good() != true) cout<<"Błąd odczytu hczb.txt"<<endl;

    if((hkal.good() == true) && (hcz.good() == true) && (hczb.good() == true)) 
    {
        menuGlowne(hkal, hcz, hczb);
    }
}

void deinit(fstream &hkal, fstream &hcz, fstream &hczb)
{
    hkal.close();
    hcz.close();
    hczb.close();
}

int main()
{
    system("chcp 65001");
    fstream hkal; //plik z haslami do kalambur
    fstream hcz;  // hasla do czółka
    fstream hczb; // hasła do czółka w temacie Batmana
    init(hkal, hcz, hczb);
    deinit(hkal, hcz, hczb);
    system("pause");
    return 0;
}


/*

//*/