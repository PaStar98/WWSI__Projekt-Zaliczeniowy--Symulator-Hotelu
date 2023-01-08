# Podstawowy Symulator Hotelu
## Lista dostepnych funkcjonalności:
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
    
### Niektore funkcjonalnosci zostaly pominiete ze wzgledu na ilosc linijek kodu do sprawdzenia
## Program NIE obsluguje:    
 - Przekroczenia liczby dostepnych pokoi
 - Ujemnych liczb lub zera podanego przez uzytkownika w trakcie pobierania danych o liczbie dni rezerwacji lub liczbie osob
 - Sortowania od maksymalnej wartosci do minimalnej (jest zaimplementowana obsluga min -> max)
 - Wyswietlania TYLKO wolnych pokoi (program wyswietla wszystkie pokoje lub zarezerwowane)
