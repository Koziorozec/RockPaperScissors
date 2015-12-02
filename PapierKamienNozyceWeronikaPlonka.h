  
#include <random>
#include <iostream>
#include <array>
 
 class WeronikaPlonka : public Gracz {
	int _licznik;
	Ruch bardzoDawny;
	Ruch dawny;
public:
	WeronikaPlonka() {
		bardzoDawny = Ruch::Kamien;
		dawny = Ruch::Kamien;
	}
 virtual void przedstawSie() {
		std::cout << "Weronika Płonka";
	}
};
