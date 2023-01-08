#include <iostream>

using namespace std;


struct Pokoj {
    string imie_goscia = "Niezarezerwowany";
    string nazwisko_goscia = "Niezarezerwowany";
    int liczba_dni_rezerwacji = NULL;
    int liczba_osob_w_pokoju = NULL;
    double cena_za_dobe = 300.00;
    double cena_calkowita = NULL;
    bool czy_pokoj_wolny = true;
};


Pokoj wpisz_dane_nowego_goscia(int liczba_pokoi) {
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

    pokoj.cena_calkowita = (pokoj.cena_za_dobe * pokoj.liczba_dni_rezerwacji);
    pokoj.czy_pokoj_wolny = false;
    --liczba_pokoi;

    return pokoj;
}

void zapisz_rezerwacje_w_bazie(const Pokoj& pokoj, Pokoj pokoje[], int n) {
    pokoje[n] = pokoj;
}

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

void pokaz_pokoje(const Pokoj pokoje[], int n) {
    for (int i = 0; i < n; i++) {
        pokaz_pokoj(pokoje[i]);
    }
}

void sortowanie_pokoi_wzgledem_ceny(Pokoj pokoje[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 1; j--) {
            if (pokoje[j].cena_calkowita < pokoje[j - 1].cena_calkowita) {
                swap(pokoje[j - 1], pokoje[j]);
            }
        }
    }
}

void sortowanie_pokoi_wzgledem_dni_rezerwacji(Pokoj pokoje[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 1; j--) {
            if (pokoje[j].liczba_dni_rezerwacji < pokoje[j - 1].liczba_dni_rezerwacji) {
                swap(pokoje[j - 1], pokoje[j]);
            }
        }
    }
}

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
    int liczba_zarezerwowanych_pokoi = 0;
    char wybor_usera = 'n';
    bool pierwsze_uruchomienie_programu = true;

    do {
        if (pierwsze_uruchomienie_programu) {
            cout << "Witaj w Hotelu, czy chcesz zarezerwowac pokoj? <t> <n>: ";
            pierwsze_uruchomienie_programu = false;
        }
        else {
            cout << "Czy chcesz zarezerwowac jeszcze jeden pokoj? <t> <n>: ";
        }
        cin >> wybor_usera;
            

        if (wybor_usera == 't') {
            Pokoj nowa_rezerwacja = wpisz_dane_nowego_goscia(liczba_zarezerwowanych_pokoi);
            zapisz_rezerwacje_w_bazie(nowa_rezerwacja, pokoje, liczba_zarezerwowanych_pokoi);
            ++liczba_zarezerwowanych_pokoi;
           
        }
        else if (wybor_usera == 'n') {
            cout << "Dziekujemy za skorzystanie z naszych uslug. Do zobaczenia!\n";
        }
        else {
            cout << "Program nie obsluguje opcji, ktora zostala wybrana - "
                << wybor_usera
                << ". Czy chodzilo Ci o <t> lub <n>?\n";
        }
    } while (wybor_usera != 'n');

    sortowanie_pokoi_wzgledem_ceny(pokoje, liczba_zarezerwowanych_pokoi);
    pokaz_pokoje(pokoje, liczba_zarezerwowanych_pokoi);
}
