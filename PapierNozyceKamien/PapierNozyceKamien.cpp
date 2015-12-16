// PapierNozyceKamien.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <iomanip>

#include "PapierNozyceKamien.h"

class Gra {
	std::array<int, 3> _liczbaWygranychPojedynkow;
	std::array<int, 3> _liczbaZwyciestwDlaDanejParyGraczy;
	std::vector<std::unique_ptr<Gracz>> _gracze;

	std::vector<std::vector<Wynik> > _wynikiPojedynkow;

	std::array<std::array<Wynik, 3>, 3> _macierzWynikow;

	Wynik walkaDwochGraczy(Gracz & gracz1,Gracz & gracz2) {

		Ruch staryRuch1 = Papier;
		Ruch staryRuch2 = Papier;
		_liczbaZwyciestwDlaDanejParyGraczy[0] = _liczbaZwyciestwDlaDanejParyGraczy[1] = _liczbaZwyciestwDlaDanejParyGraczy[2] = 0;
		for (int gra = 0;gra < 10;gra++) {
			_liczbaWygranychPojedynkow[0] = _liczbaWygranychPojedynkow[1] = _liczbaWygranychPojedynkow[2] = 0;
			for (int pojedynek = 0;pojedynek < 10000;pojedynek++) {
				Ruch ruch1 = gracz1.ruch(staryRuch2);
				Ruch ruch2 = gracz2.ruch(staryRuch1);
				_liczbaWygranychPojedynkow[ktoWygral(ruch1, ruch2)]++;
				staryRuch1 = ruch1;
				staryRuch2 = ruch2;
			}
			_liczbaZwyciestwDlaDanejParyGraczy[pokazWynikiPojedynku()] += abs(_liczbaWygranychPojedynkow[Wygral_Drugi] - _liczbaWygranychPojedynkow[Wygral_Pierwszy]);

		}
		return zwrocWynikWalkiPomiedzyDwomaGraczami();
	}


public:
	Gra() {

		_macierzWynikow[0] = { Remis, Wygral_Drugi, Wygral_Pierwszy };
		_macierzWynikow[1] = { Wygral_Pierwszy, Remis, Wygral_Drugi };
		_macierzWynikow[2] = { Wygral_Drugi, Wygral_Pierwszy, Remis };

		_liczbaZwyciestwDlaDanejParyGraczy[0] = _liczbaZwyciestwDlaDanejParyGraczy[1] = _liczbaZwyciestwDlaDanejParyGraczy[2] = 0;
		zeruj();
	}
	void graj() {
		_wynikiPojedynkow.resize(_gracze.size());
		for (int i = 0;i < _wynikiPojedynkow.size();i++) {
			_wynikiPojedynkow[i].resize(_gracze.size());
		}

		for (int i = 0;i < _gracze.size();i++) {
			for (int j = 0;j < _gracze.size();j++) {
				if (i != j) {
					_wynikiPojedynkow[i][j]=walkaDwochGraczy(*_gracze[i], *_gracze[j]);
				}
			}
		}
	}

	void pokazKoncoweWyniki() {
		std::cout << "tabela wyników botów\n";
		std::vector<int> liczbaWygranych(_gracze.size());

		std::cout << std::setw(2) << " ";
		for (int i = 0;i < _gracze.size();i++) {
			std::cout << std::setw(2) << i;
		}
		std::cout << std::endl;

		for (int i = 0;i < _gracze.size();i++) {
			std::cout << std::setw(2) << i << std::setw(2);
			for (int j = 0;j < _gracze.size();j++) {
				if (_wynikiPojedynkow[i][j] == Wygral_Pierwszy) {
					liczbaWygranych[i]++;
				}
				std::cout << _wynikiPojedynkow[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::vector<std::pair<int, int> > paryKtoLiczbaWygranych;
		for (int i = 0;i < liczbaWygranych.size();i++) {
			paryKtoLiczbaWygranych.push_back(std::make_pair(i, liczbaWygranych[i]));
		}

		std::sort(paryKtoLiczbaWygranych.begin(), paryKtoLiczbaWygranych.end(),
			[](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
			return lhs.second > rhs.second; });

		std::cout << "posortowane wyniki botów\n";
		std::cout << std::endl;
		for (int i = 0;i < paryKtoLiczbaWygranych.size();i++) {
			std::cout << paryKtoLiczbaWygranych[i].first;
			std::cout << std::setw(20);
			_gracze[paryKtoLiczbaWygranych[i].first]->przedstawSie();
			std::cout  << " " << std::setw(2) << paryKtoLiczbaWygranych[i].second << std::endl;
		}
	}


	void zeruj() {
		_liczbaWygranychPojedynkow[0] = _liczbaWygranychPojedynkow[1] = _liczbaWygranychPojedynkow[2] = 0;
		for (auto & elem  : _gracze) {
			elem->reset();
		}
	}

	Wynik ktoWygral(Ruch ruchGracza1, Ruch ruchGracza2)const {


		return _macierzWynikow[ruchGracza1][ruchGracza2];
	}
	Wynik pokazWynikiPojedynku() {

		if (_liczbaWygranychPojedynkow[Wygral_Pierwszy] == _liczbaWygranychPojedynkow[Wygral_Drugi]) {
			return Wynik::Remis;
		}
		else {
			if (_liczbaWygranychPojedynkow[Wygral_Pierwszy] > _liczbaWygranychPojedynkow[Wygral_Drugi]) {
				return Wynik::Wygral_Pierwszy;
			}
			else {
				return Wynik::Wygral_Drugi;
			}
		}
	}
	Wynik zwrocWynikWalkiPomiedzyDwomaGraczami()const {
		if (_liczbaZwyciestwDlaDanejParyGraczy[Wygral_Pierwszy] == _liczbaZwyciestwDlaDanejParyGraczy[Wygral_Drugi]) {
			return Wynik::Remis;
		}
		else {
			if (_liczbaZwyciestwDlaDanejParyGraczy[Wygral_Pierwszy] > _liczbaZwyciestwDlaDanejParyGraczy[Wygral_Drugi]) {
				return Wynik::Wygral_Pierwszy;
			}
			else {
				return Wynik::Wygral_Drugi;
			}
		}
	}

	void dodajGracza(std::unique_ptr<Gracz>&& gracz) {
		_gracze.push_back(std::move(gracz));
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
	
	Gra gra;

	std::vector<std::unique_ptr<Gracz> > gamers;
	gamers.emplace_back(std::unique_ptr<Gracz>(new Gracz1()));
	gamers.emplace_back(std::unique_ptr<Gracz>(new Gracz1()));
	gamers.emplace_back(std::unique_ptr<Gracz>(new Gracz1()));
	gamers.emplace_back(std::unique_ptr<Gracz>(new Gracz1()));
	gamers.emplace_back(std::unique_ptr<Gracz>(new Gracz2()));
	gamers.emplace_back(std::unique_ptr<Gracz>(new Gracz2()));
	gamers.emplace_back(std::unique_ptr<Gracz>(new Gracz2()));
	gamers.emplace_back(std::unique_ptr<Gracz>(new Gracz2()));

	for (auto & elem : gamers) {
		gra.dodajGracza(std::move(elem));
	}
	


	gra.graj();
	gra.pokazKoncoweWyniki();
	return 0;
}

