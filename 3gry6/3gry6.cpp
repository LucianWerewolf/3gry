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
// gra w hasła v2.9
//po raz kolejny usprawnione pobieranie haseł: podanie pobranej pary do wektora w momencie gdy jesteśmy na numerze linii 2 a nie jak do tej pory na linii 3. 
//Wtedy wymuszało to by po ostatniej parze haseł była jakaś linia a nie koniec pliku, bo nr linii nie dochodził do 3 i nie zapisywała się ostatnia para haseł.
//w tej wersji został ten błąd naprawiony poprzez inkrementację numeru liniii i sprawdzenie warunku jej wartości na koniec, a dopisywanie pary do wektora po 
//pobraniu drugiego elementu pary (na linii 2)

vector<string> haslaKal;
vector<pair<string, string>> haslaCz;
vector<pair<string, string>> haslaCzBat;

int losujHaslo(int rozmiar)
{
    int result = (rand() % rozmiar);//cout<<endl<<rozmiar<<endl;
    return result;
}

void wyswietlHaslo(int numer, int gra)
{
    switch(gra)
    {
        case 1: {cout<<"Hasło brzmi: "<<haslaKal[numer]<<endl; break;}
        case 2: {cout<<"Hasło brzmi: "<<haslaCz[numer].first<<endl;
            cout<<"wyrażenie zakazane brzmi: "<<haslaCz[numer].second<<endl; break;}
        case 3: {cout<<"Hasło brzmi: "<<haslaCzBat[numer].first<<endl;
            cout<<"wyrażenie zakazane brzmi: "<<haslaCzBat[numer].second<<endl; break;}
    }
    cout<<"\nPo odgadnięciu hasła, wciśnij dowolny klawisz.\n";
    getch();
}


void menuGry(string nazwa, int gra)
{
    char wybor = '5';
    int haslo = 0;
    while (wybor != '2')
    {
        system("CLS");
        cout<<nazwa<<".\nWybierz czynność:\n1. Losuj hasło\n2. Menu główne\n";
        wybor = getch();
        switch (wybor)
        {
            case '1': {
                if (gra == 1) {haslo = losujHaslo(haslaKal.size()); wyswietlHaslo(haslo, gra);}
                else if (gra == 2) {haslo = losujHaslo(haslaCz.size()); wyswietlHaslo(haslo, gra);}
                else if (gra == 3) {haslo = losujHaslo(haslaCzBat.size()); wyswietlHaslo(haslo, gra);}
                break;}
            case '2': cout<<"Powrót do menu...\n"; Sleep(1000);break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(1000);
        }
    }
}

void menuGlowne()
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
            case '1': menuGry("Kalambury", 1);break;
            case '2': menuGry("Czółko", 2);break;
            case '3': menuGry("Czółko-Batman", 3);break;
            case '0': cout<<"Do widzenia :)\n";break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(1000);
        }
    }
}

void pobierzHasla(fstream &plik, int gra)
{
    string linia;
    uint8_t nr_linii = 1;
    pair<string, string> para;
    switch(gra)
    {
        case 1:{
            while (!plik.eof())
            {
                getline(plik, linia);
                haslaKal.push_back(linia);
            }
            break;}
        case 2: case 3: {
            while (getline(plik,linia))
            {
                switch(nr_linii)
                {
                    case 1: para.first = linia; break;
                    case 2: para.second = linia; break;
                    case 3: break;
                }
                if (nr_linii == 2) 
                {
                    if (gra == 2) haslaCz.push_back(para);
                    if (gra == 3) haslaCzBat.push_back(para);
                }
                nr_linii++;
                if (nr_linii > 3)  nr_linii = 1;
            }
        break;}
    }
}

void init()
{
    fstream hkal; //plik z haslami do kalambur
    fstream hcz;  // hasla do czółka
    fstream hczb; // hasła do czółka w temacie Batmana
    hkal.open("hkal.txt", ios::in);
    if(hkal.good() != true) cout<<"Błąd odczytu hkal.txt"<<endl;
    hcz.open("hcz.txt", ios::in);
    if(hcz.good() != true) cout<<"Błąd odczytu hcz.txt"<<endl;
    hczb.open("hczb.txt", ios::in);
    if(hczb.good() != true) cout<<"Błąd odczytu hczb.txt"<<endl;

    if((hkal.good() == true) && (hcz.good() == true) && (hczb.good() == true)) 
    {
        pobierzHasla(hkal, 1);
        pobierzHasla(hcz, 2);
        pobierzHasla(hczb, 3);
        hkal.close();
        hcz.close();
        hczb.close();
        menuGlowne();
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
    for (int i=0; i<haslaCz.size(); i++)
    {
        cout<<haslaCz[i].first<<endl<<haslaCz[i].second<<endl;
    }   cout<<endl<<"dupa"<<endl;
    for (int i=0; i<haslaCzBat.size(); i++)
    {
        cout<<haslaCzBat[i].first<<endl<<haslaCzBat[i].second<<endl;
    } 
//*/