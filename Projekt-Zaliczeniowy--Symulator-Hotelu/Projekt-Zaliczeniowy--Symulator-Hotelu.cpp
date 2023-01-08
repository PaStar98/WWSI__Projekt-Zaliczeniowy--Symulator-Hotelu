#include <iostream>

using namespace std;

struct Pokoj {
    string imie_goscia = "Niezarezerwowany";
    string nazwisko_goscia = "Niezarezerwowany";
    int liczba_dni_rezerwacji = 0;
    int liczba_osob_w_pokoju = 0;
    float cena_za_dobe = 300.00;
    float cena_calkowita = (cena_za_dobe * liczba_dni_rezerwacji * liczba_osob_w_pokoju) * 0.7;
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
    cout << "Cena za dobe: " << pokoj.cena_za_dobe << endl;
    if (pokoj.czy_pokoj_wolny) {
        cout << "Pokoj gotowy do rezerwacji\n";
    }
    else {
        cout << "Pokoj ZAJETY\n";
    }
    cout << "----------------------------\n\n";
}

void pokaz_wszystkie_pokoje(const Pokoj pokoje[], int n) {
    for (int i = 0; i < n; i++) {
        pokaz_pokoj(pokoje[i]);
    }
}

int main() {
    Pokoj pokoje[10];
    const int wszystkie_dostepne_pokoje = sizeof(pokoje) / sizeof(*pokoje);
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

    pokaz_wszystkie_pokoje(pokoje, wszystkie_dostepne_pokoje);
}
