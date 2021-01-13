#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <conio.h>
using namespace std;

// gra w hasła v3.2
//nie zapisuje do wektorow tylko na biezaco zczytuje hasla z plikow.

enum gra
{
    KALAMBURY = 1,
    CZOLKO,
    CZOLKO_BAT
};

enum rodzaj_slowa
{
    HASLO = 1,
    WYRAZENIE_ZAKAZANE
};

int ilosc_hasel_kalambury = 0, ilosc_hasel_czolko = 0, ilosc_hasel_czolkoBat = 0;

void licz_ilosc_hasel(fstream &plik, int gra)//liczymy ilosc hasel dla kazdej z gier
{
    string linia;
    int nr_linii = 1;
    switch(gra)
    {
        case KALAMBURY:{//dla kalambur w kliku jest haslo pod haslem wiec po prostu zliczamy ilosc linii
            while (!plik.eof())
            {
                getline(plik, linia);
                ilosc_hasel_kalambury++;
            }
        break;}
        case CZOLKO: case CZOLKO_BAT:{//policzymy ilosc hasel a nie linii czyli kolejno: 1. haslo, 2. slowo zakazane, 3. odstep(pusta linia) i dolicza tylko po napotkaniu linii 1
            while (!plik.eof())
            {
                getline(plik,linia);
                if (nr_linii == 1 && gra == CZOLKO) ilosc_hasel_czolko++;
                else if (nr_linii == 1 && gra == CZOLKO_BAT) ilosc_hasel_czolkoBat++;
                nr_linii++;
                if (nr_linii > 3) nr_linii = 1;
            }
        break;}
    }  //uzyskalismy ilosc hasel w pliku i zapisana jest ona w zmiennej ilosc_hasel
    plik.seekg(0, ios::beg);//ustawiamy ponownie wskaznik w pliku na jego poczatek by dalej mozna bylo go czytac
}

int losujHaslo(int gra)//losujemy nr hasla do wyswietlenia
{
    int numer = 0;
    if (gra == KALAMBURY) numer = ((rand() % ilosc_hasel_kalambury) + 1);
    else if (gra == CZOLKO) numer = ((rand() % ilosc_hasel_czolko) + 1);
    else if (gra == CZOLKO_BAT) numer = ((rand() % ilosc_hasel_czolkoBat) + 1);  
    return numer;
}

string pobierzHaslo(fstream &plik, int numer, int gra, int rodzaj)//argumenty kolejno: zmienna plikowa, numer hasła do wyciągnięcia z pliku, wybrana gra, które z dwóch słów(hasło czy zakazane słowo w czółku) będzie pobierane
{
    int nr_hasla = 0;
    string linia;
    int nr_linii = 1;
    switch(gra)
    {
        case KALAMBURY:// dla gry kalambury jest wyciągane tylko jedno słowo z pliku, więc zmienna połowa nie ma znaczenia (tu zawsze wartość 1)
            while (nr_hasla < numer)//poszukujemy w pliku wylosowanego hasła
            {
                getline(plik, linia);
                nr_hasla++;
            }
        break;
        case CZOLKO: case CZOLKO_BAT:{//w czółkach losujemy 2 wyrażenia (w pliku następują po sobie)
            if (rodzaj == HASLO) //losujemy hasło do odgadnięcia
            {
                while (nr_hasla < numer)
                {//używając getline() przechodzimy do kolejnych linii ale kolejne hasło napotykamy w co 3ciej linii
                    if (nr_linii == 1) {getline(plik, linia); nr_hasla++;}
                    else getline(plik, linia);
                    nr_linii++;
                    if (nr_linii > 3) nr_linii = 1;
                }
            }
            else if (rodzaj == WYRAZENIE_ZAKAZANE) //losujemy słowo zakazane (nie można go używać do pomocy w zgadywaniu)
            {
                while (nr_hasla < numer)//szukamy hasła o danym numerze, jak w przypadku powyzszym
                {
                    if (nr_linii == 1) {getline(plik, linia); nr_hasla++;}
                    else getline(plik, linia);
                    if (nr_hasla == numer) getline(plik, linia);//gdy znaleźliśmy nasze hasło, jego słowo zakazane jest zaraz po nim, więc pobieramy kolejną linię
                    nr_linii++;
                    if (nr_linii > 3) nr_linii = 1;
                }
            }
        break;}
    }
    plik.seekg(0, ios::beg);//cofamy wskaźnik na początek pliku
    return linia;
}

void wyswietlHaslo(fstream &plikGry, int numer, int gra)
{
    switch(gra)
    {
        case 1: {cout<<"Hasło brzmi: "<<pobierzHaslo(plikGry, numer, gra, HASLO)<<endl; break;}
        case 2: {cout<<"Hasło brzmi: "<<pobierzHaslo(plikGry, numer, gra, HASLO)<<endl;
            cout<<"wyrażenie zakazane brzmi: "<<pobierzHaslo(plikGry, numer, gra, WYRAZENIE_ZAKAZANE)<<endl; break;}
        case 3: {cout<<"Hasło brzmi: "<<pobierzHaslo(plikGry, numer, gra, HASLO)<<endl;
            cout<<"wyrażenie zakazane brzmi: "<<pobierzHaslo(plikGry, numer, gra, WYRAZENIE_ZAKAZANE)<<endl; break;}
    }
    cout<<"\nPo odgadnięciu hasła, wciśnij dowolny klawisz.\n";
    getch();
}


void menuGry(string nazwa, int gra, fstream &plikGry)//argumenty kolejno: nazwa gry, numer wybranej gry, zmienna plikowa
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
            case '1': {//zależnie od wyboru gry uruchamia losowanie numeru hasła, a potem jego wyświetlanie przekazując informację o tym, która gra została wybrana
                if (gra == KALAMBURY) {nr_hasla = losujHaslo(gra); wyswietlHaslo(plikGry, nr_hasla, gra);}
                else if (gra == CZOLKO) {nr_hasla = losujHaslo(gra); wyswietlHaslo(plikGry, nr_hasla, gra);}
                else if (gra == CZOLKO_BAT) {nr_hasla = losujHaslo(gra); wyswietlHaslo(plikGry, nr_hasla, gra);}
                break;}
            case '2': cout<<"Powrót do menu...\n"; Sleep(500);break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(500);
        }
    }
}

void menuGlowne(fstream &hkal, fstream &hcz, fstream &hczb)//argumenty: zmienne plikowe
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
            case '1': menuGry("Kalambury", KALAMBURY, hkal);break;
            case '2': menuGry("Czółko", CZOLKO, hcz);break;
            case '3': menuGry("Czółko-Batman", CZOLKO_BAT, hczb);break;
            case '0': cout<<"Do widzenia :)\n";break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(500);
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
        licz_ilosc_hasel(hkal, KALAMBURY);
        licz_ilosc_hasel(hcz, CZOLKO);
        licz_ilosc_hasel(hczb, CZOLKO_BAT);
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
    system("chcp 65001");//umożliwia wyświetlanie polskich znaków w konsoli (nie działa w przypadku gdy wpisujemy je z klawiatury podczas działania programu)
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