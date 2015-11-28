// PapierNozyceKamien.cpp : Defines the entry point for the console application.
//

#include <random>
#include <iostream>
#include <array>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
using namespace std;

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
	std::array<int, 3> _ktoWygralGre;
	Gracz & _gracz1;
	Gracz & _gracz2;

	const std::array<std::array<Wynik, 3>, 3> _macierzWynikow;

public:
	Gra(Gracz & gracz1, Gracz & gracz2) : _gracz1(gracz1), _gracz2(gracz2),_macierzWynikow{{ {{Remis, Wygral_Drugi, Wygral_Pierwszy}},
		{{Wygral_Pierwszy, Remis, Wygral_Drugi}} ,
		{{Wygral_Drugi, Wygral_Pierwszy, Remis}} }} {
		_ktoWygralGre[0] = _ktoWygralGre[1] = _ktoWygralGre[2] = 0;
		zeruj();
	}
	void graj() {

		Ruch staryRuch1=Papier;
		Ruch staryRuch2=Papier;
		for (int pojedynek = 0;pojedynek < 10;pojedynek++) {
			for (int i = 0;i < 10000;i++) {
				Ruch ruch1 = _gracz1.ruch(staryRuch2);
				Ruch ruch2 = _gracz2.ruch(staryRuch1);
				_ktoWygralPojedynek[ktoWygral(ruch1, ruch2)]++;
				staryRuch1=ruch1;
				staryRuch2=ruch2;
			}
			_ktoWygralGre[pokazWynikiPojedynku()]+=abs(_ktoWygralPojedynek[Wygral_Drugi]-_ktoWygralPojedynek[Wygral_Pierwszy]);
			zeruj();
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
	Wynik pokazWynikiPojedynku()const {
		for (int i = 0;i < _ktoWygralPojedynek.size();++i) {
			std::cout << _ktoWygralPojedynek[i] << " ";
		}

		if (_ktoWygralPojedynek[Wygral_Pierwszy] == _ktoWygralPojedynek[Wygral_Drugi]) {
			std::cout << "Remis!\n";
			return Wynik::Remis;
		}
		else {
			if (_ktoWygralPojedynek[Wygral_Pierwszy] > _ktoWygralPojedynek[Wygral_Drugi]) {
				std::cout << "Pojedynek wygral gracz: "; _gracz1.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _ktoWygralPojedynek[Wygral_Pierwszy] - _ktoWygralPojedynek[Wygral_Drugi] << " punktow\n";
				return Wynik::Wygral_Pierwszy;
			}
			else {
				std::cout << "Pojedynek wygral gracz: "; _gracz2.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _ktoWygralPojedynek[Wygral_Drugi] - _ktoWygralPojedynek[Wygral_Pierwszy] << " punktow\n";
				return Wynik::Wygral_Drugi;
			}
		}
	}
	void pokazWynikiGry()const {
		std::cout << std::endl << std::endl << std::endl;
		for (int i = 0;i < _ktoWygralGre.size();++i) {
			std::cout << _ktoWygralGre[i] << " ";
		}

		if (_ktoWygralGre[Wygral_Pierwszy] == _ktoWygralGre[Wygral_Drugi]) {
			std::cout << "Remis!\n";
		}
		else {
			if (_ktoWygralGre[Wygral_Pierwszy] > _ktoWygralGre[Wygral_Drugi]) {
				std::cout << "Gre wygral gracz: "; _gracz1.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _ktoWygralGre[Wygral_Pierwszy] - _ktoWygralGre[Wygral_Drugi] << " punktow\n";
			}
			else {
				std::cout << "Gre wygral gracz: "; _gracz2.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _ktoWygralGre[Wygral_Drugi] - _ktoWygralGre[Wygral_Pierwszy] << " punktow\n";
			}
		}
	}
};


class Gracz2 : public Gracz {
public: Gracz2() {

}

    virtual Ruch ruch(Ruch poprzedniRuchPrzeciwnika){
        int licznik_papier;
        int licznik_kamien;
        int licznik_nozyce;
        Ruch ruchPP1;
        Ruch ruchPP2;
        int licznik_rand = 0;
        int v_r = 0;




        ruchPP2 = ruchPP1;
        ruchPP1 = poprzedniRuchPrzeciwnika;


        if(ruchPP1 == ruchPP2 && ruchPP1 == poprzedniRuchPrzeciwnika){
                if(poprzedniRuchPrzeciwnika == Ruch::Kamien){

                    return Ruch::Papier;
                }
                if(poprzedniRuchPrzeciwnika == Ruch::Nozyce){

                    return Ruch::Kamien;
                }
                if(poprzedniRuchPrzeciwnika == Ruch::Papier){

                    //cout << "d" << endl;
                    return Ruch::Nozyce;
                }}


        if (licznik_rand < 100)
		{
			srand(0);
			v_r = rand() % 3;
			if(Ruch(v_r) == poprzedniRuchPrzeciwnika){
			licznik_rand++;
		}}
		if (licznik_rand == 100)
		{
			srand(0);
			v_r = rand() % 3;
			return Ruch(v_r - 1);
		}




        if(poprzedniRuchPrzeciwnika == Ruch::Papier){
                //cout << "not";
            licznik_papier ++;
            if(licznik_kamien>= licznik_nozyce){

                //cout << "d2" << endl;
                return Ruch::Nozyce;
            }
            if(licznik_kamien<licznik_nozyce){

                return Ruch::Kamien;
            }}

            if(poprzedniRuchPrzeciwnika == Ruch::Kamien){
                  //  cout << "not";
                licznik_kamien++;
                if(licznik_nozyce >= licznik_papier){

                    return Ruch::Papier;
                }
                if(licznik_nozyce< licznik_papier){

                    //cout << "d3" << endl;
                    return Ruch::Nozyce;
                }
            }
            if(poprzedniRuchPrzeciwnika == Ruch::Nozyce){
                //cout << "not";
                licznik_nozyce++;
                if(licznik_kamien>=licznik_papier){

                    return Ruch::Papier;
                }
                if(licznik_kamien<licznik_papier){
                    return Ruch::Kamien;
                }}
    }
    void reset() {

	}


	void przedstawSie() {
		cout << "Marcin Aman";
	}
};

class Gracz1 : public Gracz {


public:
	Gracz1() {

	}

	virtual Ruch ruch(Ruch poprzedniRuchPrzeciwnika) {
		return Ruch(rand()%3);
	}
	void przedstawSie() {
		std::cout << "Szymon Palka";
	}
	void reset() {

	}
};

int main(){
    srand(time(NULL));

	Gracz1 gracz1;
	Gracz2 gracz2;
	Gra gra(gracz1, gracz2);
	gra.graj();
    return 0;
}
