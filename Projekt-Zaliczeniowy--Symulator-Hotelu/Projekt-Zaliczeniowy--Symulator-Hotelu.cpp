/*
    Podstawowy Symulator Hotelu

    Lista dostepnych mozliwosci:
        - Rezerwacja pokoju i zapisanie jej do "pseudo bazy"
        - Mozliwosc wyswietlania wszystkich pokoi lub zarezerwowanych
        - Sortowanie pod wzgledem 
            * ceny
            * liczbie osob w zarezerwowanym pokoju
            * liczba dni rezerwacji
        - Prostej grze w zgadywanie:
            * Uzytkownik ma wybor czy chce zagrac w gre
            * Uzytkownik wybiera liczbe z okreslonego zakresu (program aktualnie przewiduje zakres 1.. 10)
            * Uzytkownik podaje swoja liczbe
            * Jesli podana liczba jest zgodna z wylosowana przez program to uzytkownik zyskuje -50% znizki na pobyt w hotelu
            * Jesli podana liczbe NIE jest zgodna z wylsoowana przez program to uzytkownik musi doplacic +20% do pobytu w hotelu
            * Mozliwosc zagrania pojawia sie za kazdym razem kiedy Uzytkownik chce zarezerwowac nowy pokoj

    Niektore funkcjonalnosci zostaly pominiete ze wzgledu na ilosc linijek kodu do sprawdzenia
    Program NIE obsluguje:
        - Przekroczenia liczby dostepnych pokoi
        - Ujemnych liczb lub zera podanego przez uzytkownika w trakcie pobierania danych o liczbie dni rezerwacji lub liczbie osob
        - Sortowania od maksymalnej wartosci do minimalnej (jest zaimplementowana obsluga min -> max)
        - Wyswietlania TYLKO wolnych pokoi (program wyswietla wszystkie pokoje lub zarezerwowane)
*/
#include <iostream>
#include <random>

using namespace std;

struct Pokoj {
    string imie_goscia = "Niezarezerwowany";
    string nazwisko_goscia = "Niezarezerwowany";
    int liczba_dni_rezerwacji = 0;
    int liczba_osob_w_pokoju = 0;
    double cena_za_dobe = 300.00;
    double cena_calkowita = 0;
    bool czy_pokoj_wolny = true;
};

// <wpisz_dane_nowego_goscia> zbiera dane dotyczace osoby, ktora chce zarezerwowac pokoj
// funkcja zwraca <Pokoj pokoj>
Pokoj wpisz_dane_nowego_goscia(int liczba_pokoi, bool& czy_gral, bool& czy_wygral) {
    Pokoj pokoj;

    cout << "-------- Panel Rezerwacji --------\n";
    cout << "Imie: ";
    cin >> pokoj.imie_goscia;
    cout << "Nazwisko: ";
    cin >> pokoj.nazwisko_goscia;
    cout << "Dlugosc rezerwacji (liczba dni): ";
    cin >> pokoj.liczba_dni_rezerwacji;
    cout << "Dla ilu osob: ";
    cin >> pokoj.liczba_osob_w_pokoju;
    cout << "----------------------------------\n\n";

    if (czy_gral && czy_wygral) { // cena calkowita zmniejszona o 50% przez wygrana w grze
        pokoj.cena_calkowita = (pokoj.cena_za_dobe * pokoj.liczba_dni_rezerwacji) * 0.5;
    }
    else if (czy_gral && !czy_wygral) { // cena calkowita zwiekszona o 20% przez przegrana w grze
        pokoj.cena_calkowita = (pokoj.cena_za_dobe * pokoj.liczba_dni_rezerwacji) * 1.2;
    }
    else if (!czy_gral) { // cena standardowa za nie branie udzialu w grze
        pokoj.cena_calkowita = (pokoj.cena_za_dobe * pokoj.liczba_dni_rezerwacji);
    }
    
    pokoj.czy_pokoj_wolny = false;
    --liczba_pokoi;

    return pokoj;
}

// <wylosuj_liczbe> wspomaga funkcje <gra_w_losowanie>
int wylosuj_liczbe(int min, int max) {
    default_random_engine generator(unsigned(time(0)));
    uniform_real_distribution<> losowa(min, max);
    return losowa(generator);
}

// <gra_w_losowanie> Prosta gra, w ktorej nalezy odgadnac zadany zakres
// Jezeli Uzytkownikowi uda sie odgadnac liczbe to zyska -50% rabatu na pobyt w hotelu
// Jezeli Uzytkownik przegra, bedzie musial doplacic 20% do pobytu w hotelu
void gra_w_losowanie(int min, int max, bool& czy_gral, bool& czy_wygral) {
    //todo: handle +50%, -20% discount to room's price
    char wybor_usera;
    int wybor_liczby;

    cout << "Czy chcesz zagrac w gre?\n";
    cout << "Jesli wygrasz zaplacisz za pobyt w hotelu 50% mniej...\n";
    cout << "Jesli przegrasz zaplacisz za pobyt w hotelu 20% wiecej...\n";
    cout << "<t> - tak, <n> - nie: ";
    cin >> wybor_usera;

    do {
        if (wybor_usera == 't') { // Uzytkownik gra w gre
            int wylosowana_liczba = wylosuj_liczbe(min, max);
            czy_gral = true;

            cout << "Wybierz liczbe z przedzialu od " << min << ".. " << max << ": ";
            cin >> wybor_liczby;
            cout << "Wybrana liczba: " << wybor_liczby << endl;
            cout << "Wylosowana liczba: " << wylosowana_liczba << endl;

            if (wybor_liczby == wylosowana_liczba) { // wygrana Uzytkownika w grze
                czy_wygral = true;
                cout << "Gratulacje, udalo Ci sie zgadnac i otrzymujesz rabat w wysokosci 50%!\n";
                cout << "Zyczymy milego pobytu w naszym hotelu :)\n";
            }
            else { // niepoprawny input
                cout << "Niestety, nie udalo sie zgadnac.\n";
                cout << "Za pobyt w hotelu zaplacisz 20% wiecej :(\n";
            }

            break;
        }
        else if (wybor_usera == 'n') { // Uzytkownik rezygnuje z gry
            cout << "Wybrales pominiecie gry. Dokonaj rezerwacji. Zyczymy milego pobytu w hotelu.\n";
        }
        else { // niepoprawny input
            cout << "Program nie obsluguje opcji, ktora zostala przez Ciebie wybrana - <"
                << wybor_usera
                << ">, obsluga przyciskow <t> - tak, <n> - nie\n";
            cin >> wybor_usera;
        }
    } while (wybor_usera != 'n');
}

void zapisz_rezerwacje_w_bazie(const Pokoj& pokoj, Pokoj pokoje[], int n) {
    pokoje[n] = pokoj;
}

// <pokaz_pokoj> funkcja pomocnicza dla <pokaz_pokoje> i <pokaz_wolne_pokoje>
// wypisuje dane dotyczace pokoju, np. pokoj wolny lub zajety
void pokaz_pokoj(const Pokoj& pokoj) {
    cout << "---------- Pokoj ----------\n";
    cout << "Imie Goscia: " << pokoj.imie_goscia << endl;
    cout << "Nazwisko Goscia: " << pokoj.nazwisko_goscia << endl;
    cout << "Liczba dni rezerwacji: " << pokoj.liczba_dni_rezerwacji << endl;
    cout << "Liczba osob w pokoju: " << pokoj.liczba_osob_w_pokoju << endl;
    cout << "Cena za dobe: " << pokoj.cena_za_dobe << endl;
    if (pokoj.czy_pokoj_wolny) {
        cout << "Pokoj gotowy do rezerwacji\n";
    }
    else {
        cout << "Cena calkowita: " << pokoj.cena_calkowita << endl;
        cout << "Pokoj ZAJETY\n";
    }
    cout << "----------------------------\n\n";
}

// <pokaz_pokoje> wypisuje wszystkie wolne i zajete pokoje
void pokaz_pokoje(const Pokoj pokoje[], int n) {
    for (int i = 0; i < n; i++) {
        pokaz_pokoj(pokoje[i]);
    }
}

// <pokaz_wolne_pokoje> dziala jak funkcja powyzej, ale wypisuje TYLKO wolne pokoje
void pokaz_wolne_pokoje(const Pokoj pokoje[], int n) {
    for (int i = 0; i < n; i++) {
        if (pokoje[i].czy_pokoj_wolny) {
            pokaz_pokoj(pokoje[i]);
        }
    }
}

// sortuje ceny od min do max dla zarezerwowanych pokoi -> 300, 900, 600 -> 300, 600, 900
void sortowanie_pokoi_wzgledem_ceny(Pokoj pokoje[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 1; j--) {
            if (pokoje[j].cena_calkowita < pokoje[j - 1].cena_calkowita) {
                swap(pokoje[j - 1], pokoje[j]);
            }
        }
    }
}

// sortuje liczbe dni rezerwacji dla zarezerwowanych pokoi od min do max 
void sortowanie_pokoi_wzgledem_dni_rezerwacji(Pokoj pokoje[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 1; j--) {
            if (pokoje[j].liczba_dni_rezerwacji < pokoje[j - 1].liczba_dni_rezerwacji) {
                swap(pokoje[j - 1], pokoje[j]);
            }
        }
    }
}

// sortuje liczbe osob w pokoju dla zarezerwowanych pokoi od min do max
void sortowanie_pokoi_wzgledem_ilosc_osob(Pokoj pokoje[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 1; j--) {
            if (pokoje[j].liczba_osob_w_pokoju < pokoje[j - 1].liczba_osob_w_pokoju) {
                swap(pokoje[j - 1], pokoje[j]);
            }
        }
    }
}

int main() {
    Pokoj pokoje[10];
    const int wszystkie_dostepne_pokoje = 10;

    // <liczba_zarezerwowanych_pokoi> zmienna zmienia sie w zaleznosci
    // od tego czy pokoj zostal zarezerwowany dla uzytkownika
    int liczba_zarezerwowanych_pokoi = 0;
    char wybor_usera = 'n';

    // <pierwsze_uruchomienie_programu> - zmienna pomocnicza - pomaga dobrac odpowiednie cout'y
    bool pierwsze_uruchomienie_programu = true; 

    // <czy_gral_w_gre> i <czy_wygral_gre> - w zaleznosci od zawartosci zmiennej, 
    // w inny sposob bedzie naliczana cena calkowita za pobyt w hotelu
    bool czy_gral_w_gre = false;
    bool czy_wygral_gre = false;


    // Obsluga rezerwacji pokoju, gry w zgadywanie, zapisu rezerwacji w "pseudo bazie"
    do {
        if (pierwsze_uruchomienie_programu) {
            cout << "Witaj w HOTELU, czy chcesz zarezerwowac pokoj? <t> <n>: ";
            
        }
        else {
            cout << "Czy chcesz zarezerwowac jeszcze jeden pokoj? <t> <n>: ";
        }
        cin >> wybor_usera;
            

        if (wybor_usera == 't') { // Uzytkownik rezerwuje pokoj
            pierwsze_uruchomienie_programu = false;
            gra_w_losowanie(1, 10, czy_gral_w_gre, czy_wygral_gre);

            Pokoj nowa_rezerwacja = wpisz_dane_nowego_goscia(liczba_zarezerwowanych_pokoi, czy_gral_w_gre, czy_wygral_gre);
            zapisz_rezerwacje_w_bazie(nowa_rezerwacja, pokoje, liczba_zarezerwowanych_pokoi);
            ++liczba_zarezerwowanych_pokoi;
        }
        else if (wybor_usera == 'n') { // Uzytkownik zrezygnowal z rezerwacji pokoju
            cout << "Dziekujemy za skorzystanie z naszych uslug. Do zobaczenia!\n";
        }
        else { // niepoprawny input
            cout << "Program nie obsluguje opcji, ktora zostala wybrana - "
                << wybor_usera
                << ". Dostepne mozliwosci - <t> <n>: \n";
        }
    } while (wybor_usera != 'n');

    // <pierwsze_uruchomienie_programu> zyskuje wartosc false tylko wtedy, gdy Uzytkownik wykona rezerwacje pokoju
    if (pierwsze_uruchomienie_programu) {
        return 0;
    }

    // Obsluga sortowania pokoi, wyswietlania wolnych lub zajetych pokoi
    do {
        cout << "-----------------------------------------------------------------\n";
        cout << "Po rezerwacji przedstawiam Ci rozne mozliwosci jakich mozesz uzyc: \n";
        cout << "<s> Sortowanie pokoi, \n";
        cout << "<p> Pokazanie zajetych lub wolnych pokoi, \n";
        cout << "<w> Wyjscie z programu \n";
        cout << "Czy ktoras opcja Cie interesuje?: ";
        cin >> wybor_usera;
        cout << "-----------------------------------------------------------------\n";

        if (wybor_usera == 's') { // Uzytkownik wybral sortowanie
            cout << "Wybrales sortowanie\n";
            cout << "Sortowanie po cenie <c>\n";
            cout << "Sortowanie po dniach rezerwacji <r>\n";
            cout << "Sortowanie po liczbie osob na pokoju <l>\n";
            cout << "Wybierz: ";
            cin >> wybor_usera;

            if (wybor_usera == 'c') { // Uzytkownik wybral sortowanie po cenie
                sortowanie_pokoi_wzgledem_ceny(pokoje, liczba_zarezerwowanych_pokoi);
                pokaz_pokoje(pokoje, liczba_zarezerwowanych_pokoi);
            }
            else if (wybor_usera == 'r') {  // Uzytkownik wybral sortowanie po liczbie dni rezerwacji
                sortowanie_pokoi_wzgledem_dni_rezerwacji(pokoje, liczba_zarezerwowanych_pokoi);
                pokaz_pokoje(pokoje, liczba_zarezerwowanych_pokoi);
            }
            else if (wybor_usera == 'l') {  // Uzytkownik wybral sortowanie po ilosci osob w zajetym pokoju
                sortowanie_pokoi_wzgledem_ilosc_osob(pokoje, liczba_zarezerwowanych_pokoi);
                pokaz_pokoje(pokoje, liczba_zarezerwowanych_pokoi);
            }
            else { // niepoprawny input
                cout << "Wybrales nieprawidlowy przycisk: " << wybor_usera << endl;
            }
        }
        else if (wybor_usera == 'p') { // Uzytkownik wybral wyswietlenie pokoi
            cout << "Wybrales wyswietlanie pokoi\n";
            cout << "<w> Pokaz wszystkie pokoje\n";
            cout << "<z> Pokaz zajete pokoje\n";
            cout << "Wybierz: ";
            cin >> wybor_usera;

            if (wybor_usera == 'w') { // Uzytkownik wybral wyswietlenie wszystkich pokoi
                pokaz_wolne_pokoje(pokoje, wszystkie_dostepne_pokoje);
            }
            else if (wybor_usera == 'z') { // Uzytkownik wybral wyswietlenie zarezerwowanych pokoi
                pokaz_pokoje(pokoje, liczba_zarezerwowanych_pokoi);
            }
            else { // niepoprawny input
                cout << "Wybrales nieprawidlowy przycisk: " << wybor_usera << endl;
            }
        }
        else if (wybor_usera == 'w') { // wyjscie z programu
            cout << "Dziekujemy za skorzystanie z naszego programu!\n";
            break;
        }
        else { // niepoprawny input
            cout << "Niepoprawny przycisk - <" 
                << wybor_usera 
                << ">, program nie moze obsluzyc zadania, wybierz sposrod tych przyciskow: <s>, <p> lub <w>: ";
            cin >> wybor_usera;
        }
    } while (wybor_usera != 'n');
}
