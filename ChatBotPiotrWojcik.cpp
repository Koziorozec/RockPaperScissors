#include <iostream>

int main() {
    std::cout << "Podaj swój wiek:" "\n";
    int wiek;
    std::cin >> wiek;
    std::cout << "Przywitaj sie" "\n" "Ja:  ";
    char przywitajsie;
    std::cin >> przywitajsie;
    std::cout << "\n" "Bot: " ;
    if((wiek<=2))
        std::cout << "jaki jestes maly";
    if((wiek>=3)&&(wiek<=10))
        std::cout << "no hej";
    if((wiek>=11)&&(wiek<=18))
        std::cout << "siemka";
    if((wiek>=19)&&(wiek<=50))
        std::cout << "witam";
    if((wiek>=51))
        std::cout << "dzien dobry szanownemu panu";

    std::cout << "\n" "Bot: czy chcesz porozmawiac o pogodzie?" "\n" "1.Tak"   "    2.Nie   Wybierz liczbe" "\n" "Ja:    ";
    int wybor;
    std::cin >> wybor;
        if((wybor == 1)){
            std::cout << "Bot:  ok pogadajmy" "\n" "jaka jest dzisiaj pogoda?";
            char pogoda;
            std::cout << "\n" "Ja:    ";
            std::cin >> pogoda;
            std::cout << "Bot:   ok dzieki ";

            std::cout << "\n" " Koniec rozmowy";
        }
        if((wybor == 2)){
            std::cout << "Bot:  w takim razie zegnam";
            std::cout << "\n" "Koniec rozmowy ";
        }
	return 0;
}
