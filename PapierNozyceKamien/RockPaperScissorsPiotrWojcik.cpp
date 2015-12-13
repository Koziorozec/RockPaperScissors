class Gracz2 : public Gracz {
public:
    Gracz2() {
    }
        virtual Ruch ruch(Ruch poprzedniRuchPrzeciwnika) {
            int x = (rand()%3);
            Ruch val = static_cast<Ruch>(x);
            return Ruch(x);
        }

       void reset() {

            }
       virtual void przedstawSie() {
            std::cout << "Piotr Wojcik";
            }
};
 
