#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string sNum1;
    double dNum1, dNum2, dRes;
    char operatore = '+';
    bool error = false, invalidInput = true, validRes = false;

    while (true) {
        
        do {
            std::cout << "Inserisci il primo numero o 'q' se vuoi terminare l'esecuzione o'ans' se vuoi usare il risultato più vecchio : "<< std::endl;
            std::cin >> sNum1;

            std::transform(sNum1.begin(), sNum1.end(), sNum1.begin(), [](unsigned char c) {return std::tolower(c); });

            if (sNum1 == "q") {
                return 0;
            }
            else if (sNum1 == "ans" && validRes) {
                dNum1 = dRes;
                invalidInput = false;
            }
            else if (sNum1 == "ans" && validRes == false) {
                std::cout << "Non è presente nessun risultato immagazzinato.\n";
            }
            else
            {
                try {
                    dNum1 = std::stod(sNum1);
                    invalidInput = false;
                }
                catch(const std::exception& e) {
                    std::cerr << e.what() << '\n';
                }
            }

        } while (invalidInput == true);        
        
        do {
            std::cout << "Inserisci operazione:"<< std::endl;
            std::cin >> operatore;
        } while (operatore != '+' && operatore != '-' && operatore != '/' && operatore != '*');

        std::cout << "Inserisci il secondo numero"<< std::endl;
        std::cin >> dNum2;

        if (operatore == '+') {
            dRes = dNum1 + dNum2;
        }
        else if (operatore == '-') {
            dRes = dNum1 - dNum2;
        }
        else if (operatore == '/') {
            if(dNum2 == 0) {
                std::cout << "Impossibile"<< std::endl;
                error = true;
            }
            else {
                dRes = dNum1 / dNum2;
            }
        }
        else if (operatore == '*') {
            dRes = dNum1 * dNum2;
        }

        if (error == false) {
            std::cout << "Il risultato dell'operazione " << operatore << " è " << dRes << "\n" << std::endl;
            validRes = true;
        }

        error = false;
        invalidInput = true;
    }
    
    return 0;
}