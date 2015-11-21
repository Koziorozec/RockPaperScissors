// PapierNozyceKamien.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <array>

enum Ruch { Papier, Nozyce, Kamien };
enum Wynik { Remis, Wygral_Pierwszy, Wygral_Drugi };



std::ostream& operator<<(std::ostream& s, Ruch w)
{
	return s << ((w == Kamien) ? "Kamien" : (w == Papier) ? "Papier" : "Nozyce");
}

class Gracz {
public:
	virtual void przedstawSie() = 0;
	virtual Ruch ruch(Ruch poprzedniRuchPrzeciwnika) = 0;
	virtual void reset() = 0;
};


class Gra {
	std::array<int, 3> _ktoWygralPojedynek;
	std::array<int, 3> _iloscPunktowWGrze;
	std::array<int, 3> _iloscWygranychGier;
	Gracz & _gracz1;
	Gracz & _gracz2;

	std::array<std::array<Wynik, 3>, 3> _macierzWynikow;


public:
	Gra(Gracz & gracz1, Gracz & gracz2) : _gracz1(gracz1), _gracz2(gracz2) {

		_macierzWynikow[0] = { Remis, Wygral_Drugi, Wygral_Pierwszy };
		_macierzWynikow[1] = { Wygral_Pierwszy, Remis, Wygral_Drugi };
		_macierzWynikow[2] = { Wygral_Drugi, Wygral_Pierwszy, Remis };

		_iloscPunktowWGrze[0] = _iloscPunktowWGrze[1] = _iloscPunktowWGrze[2] = 0;
		zeruj();
	}
	void graj() {

		Ruch staryRuch1 = Papier;
		Ruch staryRuch2 = Papier;
		for (int gra = 0;gra < 10;gra++) {
			zeruj();
			for (int pojedynek = 0;pojedynek < 10000;pojedynek++) {
				Ruch ruch1 = _gracz1.ruch(staryRuch2);
				Ruch ruch2 = _gracz2.ruch(staryRuch1);
				_ktoWygralPojedynek[ktoWygral(ruch1, ruch2)]++;
				staryRuch1 = ruch1;
				staryRuch2 = ruch2;
			}
			_iloscPunktowWGrze[pokazWynikiPojedynku()] += abs(_ktoWygralPojedynek[Wygral_Drugi] - _ktoWygralPojedynek[Wygral_Pierwszy]);
			
		}
		pokazWynikiGry();
	}
	void zeruj() {
		_ktoWygralPojedynek[0] = _ktoWygralPojedynek[1] = _ktoWygralPojedynek[2] = 0;
		_gracz1.reset();
		_gracz2.reset();
	}

	Wynik ktoWygral(Ruch ruchGracza1, Ruch ruchGracza2)const {


		return _macierzWynikow[ruchGracza1][ruchGracza2];
	}
	Wynik pokazWynikiPojedynku() {
		for (int i = 0;i < _ktoWygralPojedynek.size();++i) {
			std::cout << _ktoWygralPojedynek[i] << " ";
		}

		if (_ktoWygralPojedynek[Wygral_Pierwszy] == _ktoWygralPojedynek[Wygral_Drugi]) {
			std::cout << "Remis!\n";
			return Wynik::Remis;
		}
		else {
			if (_ktoWygralPojedynek[Wygral_Pierwszy] > _ktoWygralPojedynek[Wygral_Drugi]) {
				_iloscWygranychGier[Wygral_Pierwszy]++;
				std::cout << "Pojedynek wygral gracz: "; _gracz1.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _ktoWygralPojedynek[Wygral_Pierwszy] - _ktoWygralPojedynek[Wygral_Drugi] << " punktow\n";
				return Wynik::Wygral_Pierwszy;
			}
			else {
				_iloscWygranychGier[Wygral_Drugi]++;
				std::cout << "Pojedynek wygral gracz: "; _gracz2.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _ktoWygralPojedynek[Wygral_Drugi] - _ktoWygralPojedynek[Wygral_Pierwszy] << " punktow\n";
				return Wynik::Wygral_Drugi;
			}
		}
	}
	void pokazWynikiGry()const {
		std::cout << std::endl << std::endl << std::endl;
		for (int i = 0;i < _iloscPunktowWGrze.size();++i) {
			std::cout << _iloscPunktowWGrze[i] << " ";
		}

		if (_iloscPunktowWGrze[Wygral_Pierwszy] == _iloscPunktowWGrze[Wygral_Drugi]) {
			std::cout << "Remis!\n";
		}
		else {
			if (_iloscPunktowWGrze[Wygral_Pierwszy] > _iloscPunktowWGrze[Wygral_Drugi]) {
				std::cout << "Gre wygral gracz: "; _gracz1.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _iloscPunktowWGrze[Wygral_Pierwszy] - _iloscPunktowWGrze[Wygral_Drugi] << " punktow\n";
			}
			else {
				std::cout << "Gre wygral gracz: "; _gracz2.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _iloscPunktowWGrze[Wygral_Drugi] - _iloscPunktowWGrze[Wygral_Pierwszy] << " punktow\n";
			}
		}
	}
};


class Gracz1 : public Gracz {


public:
	Gracz1() {

	}

	virtual Ruch ruch(Ruch poprzedniRuchPrzeciwnika) {
		return Ruch(rand() % 3);
	}
	void przedstawSie() {
		std::cout << "Szymon Palka";
	}
	void reset() {

	}
};

class Gracz2 : public Gracz {
	int _licznik;
public:
	Gracz2() {
		_licznik = 0;
	}
	virtual Ruch ruch(Ruch poprzedniRuchPrzeciwnika) {
		// nie chcialem castowac
		if (_licznik == 0) {
			_licznik++;
			return Ruch::Papier;
		}
		if (_licznik == 1) {
			_licznik++;
			return Ruch::Nozyce;
		}
		if (_licznik == 2) {
			_licznik = 0;
			return Ruch::Kamien;
		}
	}
	void reset() {

	}
	virtual void przedstawSie() {
		std::cout << "Tomasz Pedzimaz";
	}
};

int main() {
	srand(time(NULL));

	Gracz1 gracz1;
	Gracz2 gracz2;
	Gra gra(gracz1, gracz2);
	gra.graj();
	return 0;
}

