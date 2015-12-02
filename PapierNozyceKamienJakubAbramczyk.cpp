

class Gracz2 : public Gracz {
	int _licznik;
public:
	Gracz2() {
		_licznik = 0;
	}
	virtual Ruch ruch(Ruch poprzedniRuchPrzeciwnika) {
		
		if (_licznik == 0) {
			_licznik++;
			return poprzedniRuchPrzeciwnika;
		}
		if (_licznik == 1) {
			_licznik++;
			return Ruch::Nozyce;
		}
		if (_licznik == 2) {
			_licznik++;
			return poprzedniRuchPrzeciwnika;
		}
		if (_licznik == 3) {
			_licznik++;
			return Ruch::Kamien;
		}	
		if (_licznik == 4) {
			_licznik++;
			return poprzedniRuchPrzeciwnika;
		}
		if (_licznik == 5) {
			_licznik++;
			return Ruch::Papier;
		}	
		if (_licznik == 6) {
			_licznik=0;
			return Ruch::Nozyce;
		}
	
	}
	
	void reset() {

	}
	virtual void przedstawSie() {
		std::cout << "Jakub Abramczyk";
	}
};


