#include <iostream>
#include <string>

int main() {
    std::string sNum1;
    double dNum1, dNum2, dRes;
    char operatore = '+';
    bool error = false, invalidInput = true;

    while (true) {
        
        do {
            std::cout << "Inserisci il primo numero o 'q' se vuoi terminare l'esecuzione: "<< std::endl;
            std::cin >> sNum1;

            if (sNum1 == "q") {
                return 0;
            }

            try {
                dNum1 = std::stod(sNum1);
                invalidInput = false;
            }
            catch(const std::exception& e) {
                std::cerr << e.what() << '\n';
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
        }

        error = false;
        invalidInput = true;
    }
    
    return 0;
}