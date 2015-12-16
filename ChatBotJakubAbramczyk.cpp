#include <iostream>
#include <string>
#include <ctime>

int main()
{
    std::cout << "Jestem MAX" << std::endl;
    std::string odpowiedz[] = {
        "Witaj, jaka pogoda?",
        "Czesc, co slychac ? ",
        "Elo, jak tam ?",
        "Dzien dobry, jak sie czujesz",
        "Siema, co tam ?"
    };

    std::string odpowiedz1[] = {
        "To fajnie, powiesz coś o sobie ?",
        "U mnie tez spoko, co robisz ?",
        "to miło, a co dzis robiłeś?",
        
    };

    std::string sInput = "";
    std::string sodpowiedz = "";
    std::string sodpowiedz1 = "";
    
    while(1) {
       
        std::getline(std::cin, sInput);
         if (sInput == "Papa"){
            std::cout << "Do widzenia" << std::endl;
            break;    
        }
        else if (sInput == "spoko"){std::cout << ">";
            int nSelection = rand() % 3;
            sodpowiedz1 = odpowiedz1[nSelection];
            std::cout << sodpowiedz1 << std::endl;
        }
        else {std::cout << ">";
            int nSelection = rand() % 5;
            sodpowiedz == odpowiedz[nSelection];
            std::cout << sodpowiedz << std::endl;
        }
    }

    return 0;
}
