#ifndef ROCKPAPERSCISSORSGRZEGORZKULINSKI_H
#define ROCKPAPERSCISSORSGRZEGORZKULINSKI_H
#include "gracz.h"
#include<vector>
#include<math.h>

class Gracz3 : public Gracz
{

	std::random_device _rd;
	
	std::mt19937 _gen;
	
	std::uniform_int_distribution<> _dis;
	
	struct Wygrana {
		int ja;
		int on;
		std::vector<int> wygrana_tab;
	};
	Wygrana wygr;
	float win_ratio();

	int limiter_szesciu = 0;
	bool inteligent = false;
	bool zmienny_inteligent = false;

	Ruch podpuszczacz( int numer );
	int numer_podpuszczacza = 1; //jedynkuj!!!	
	int kiedy_badanie = 0;

	Ruch kontrator( Ruch input );
	Ruch symulator( Ruch poprzedni_moj );
	Ruch statystyka( int ile_statnich );

	std::vector<Ruch> poczatkowe_ruchy;
	std::vector<Ruch> ruchy;
	std::vector<Ruch> moje_ruchy;
	std::vector<int> jego_okres;

	bool czy_wygralem( std::vector<Ruch> ja, std::vector<Ruch> on, int kiedy );
	
public:

	int analizer_up( std::vector<Ruch> potyczki, int ile_ostatnich );
	int analizer( std::vector<Ruch> potyczki, int ile );
	Ruch jaki_ruch_okresu( std::vector<Ruch> vec, int ile_ostatnich, int okres );
	void reset();
	Gracz3();
	void przedstawSie();
	Ruch ruch( Ruch stary_ruch );
	virtual ~Gracz3();
protected:
private:
};


#endif // ROCKPAPERSCISSORSGRZEGORZKULINSKI_H
