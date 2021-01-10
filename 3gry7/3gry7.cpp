#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <conio.h>
using namespace std;

// gra w hasła v3.0
//nie zapisuje do wektorow tylko na biezaco zczytuje hasla z plikow.

int losujHaslo(fstream &plik, int gra)//niech liczy ilosc linii i wtedy randa z tego i wysyla spowrotem
{
    int ilosc_hasel = 0;
    string linia;
    int nr_linii = 1;
    switch(gra)
    {
        case 1:{//dla kalambur w kliku jest haslo pod haslem wiec po prostu zliczamy ilosc linii
            while (!plik.eof())
            {
                getline(plik, linia);
                ilosc_hasel++;
            }
        break;}
        case 2: case 3:{//policzymy ilosc hasel a nie linii czyli kolejno: 1. haslo, 2. slowo zakazane, 3. odstep(pusta linia) i dolicza tylko po napotkaniu linii 1
            while (!plik.eof())
            {
                getline(plik,linia);
                switch(nr_linii)
                {
                    case 1: ilosc_hasel++; break;
                    case 2: case 3: break;
                }
                nr_linii++;
                if (nr_linii > 3) nr_linii = 1;
            }
        break;}
    }  //uzyskalismy ilosc hasel w pliku i zapisana jest ona w zmiennej ilosc_hasel
    plik.seekg(0, ios::beg);//ustawiamy ponownie wskaznik w pliku na jego poczatek by dalej mozna bylo go czytac
    return ((rand() % ilosc_hasel) + 1);//losujemy jedno z nich i zwracamy numer wylosowanego hasla
}

string pobierzHaslo(fstream &plik, int numer, int gra, int polowa)//argumenty kolejno: zmienna plikowa, numer hasła do wyciągnięcia z pliku, wybrana gra, które z dwóch słów(hasło czy zakazane słowo w czółku) będzie pobierane
{
    int nr_hasla = 0;
    string linia;
    int nr_linii = 1;
    switch(gra)
    {
        case 1:// dla gry nr1 czyli kalambury jest wyciągane tylko jedno słowo z pliku, więc zmienna połowa nie ma znaczenia (tu zawsze wartość 1)
            while (nr_hasla < numer)//poszukujemy w pliku wylosowanego hasła
            {
                getline(plik, linia);
                nr_hasla++;
            }
        break;
        case 2: case 3:{//w czółkach losujemy 2 wyrażenia (w pliku następują po sobie)
            if (polowa == 1) //losujemy hasło do odgadnięcia
            {
                while (nr_hasla < numer)
                {
                    switch(nr_linii)//używając getline() przechodzimy do kolejnych linii ale kolejne hasło napotykamy w co 3ciej linii
                    {
                        case 1: {getline(plik, linia); nr_hasla++; break;}
                        case 2: {getline(plik, linia); break;}
                        case 3: {getline(plik, linia); break;}
                    }
                    nr_linii++;
                    if (nr_linii > 3) nr_linii = 1;
                }
            }
            else if (polowa == 2) //losujemy słowo zakazane (nie można go używać do pomocy w zgadywaniu)
            {
                while (nr_hasla < numer)
                {
                    switch(nr_linii)//szukamy hasła o danym numerze, jak w przypadku (połowa=1)
                    {
                        case 1: {getline(plik, linia); nr_hasla++; break;}
                        case 2: {getline(plik, linia); break;}
                        case 3: {getline(plik, linia); break;}
                    }
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

void wyswietlHaslo(fstream &plikGry, int numer, int gra)//bezie czytal linie z pliku i wyswietlal
{
    switch(gra)
    {
        case 1: {cout<<"Hasło brzmi: "<<pobierzHaslo(plikGry, numer, gra, 1)<<endl; break;}
        case 2: {cout<<"Hasło brzmi: "<<pobierzHaslo(plikGry, numer, gra, 1)<<endl;// ostatnia cyfra mowi pobierajacej funkcji czy pobrac haslo(1) czy slowo zakazane(2)
            cout<<"wyrażenie zakazane brzmi: "<<pobierzHaslo(plikGry, numer, gra, 2)<<endl; break;}
        case 3: {cout<<"Hasło brzmi: "<<pobierzHaslo(plikGry, numer, gra, 1)<<endl;
            cout<<"wyrażenie zakazane brzmi: "<<pobierzHaslo(plikGry, numer, gra, 2)<<endl; break;}
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
            case '1': {//zależnie od wyboru gry (1=kalambury; 2=czółko; 3=czółko-batman) uruchamia losowanie numeru hasła, a potem jego wyświetlanie przekazując informację o tym, która gra została wybrana
                if (gra == 1) {nr_hasla = losujHaslo(plikGry, gra); wyswietlHaslo(plikGry, nr_hasla, gra);}
                else if (gra == 2) {nr_hasla = losujHaslo(plikGry, gra); wyswietlHaslo(plikGry, nr_hasla, gra);}
                else if (gra == 3) {nr_hasla = losujHaslo(plikGry, gra); wyswietlHaslo(plikGry, nr_hasla, gra);}
                break;}
            case '2': cout<<"Powrót do menu...\n"; Sleep(800);break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(800);
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
        {//drugi argument to wybor w postaci int - informacja dla dalszych funkcji którą grę uruchomiono
            case '1': menuGry("Kalambury", 1, hkal);break;
            case '2': menuGry("Czółko", 2, hcz);break;
            case '3': menuGry("Czółko-Batman", 3, hczb);break;
            case '0': cout<<"Do widzenia :)\n";break;
            default: cout<<"Błędny wybór"; wybor = '5'; Sleep(800);
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