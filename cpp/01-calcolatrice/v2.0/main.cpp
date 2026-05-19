#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

struct operation{
    double Num1;
    char oper;
    double Num2;
    double Res;
};

int main() {
    std::string sNum1;
    int index;
    double dNum1, dNum2, dRes;
    char operatore = '+';
    bool error = false, invalidInput = true, validRes = false;
    std::vector<operation> operations;

    while (true) {
        
        do {
            std::cout << "Inserisci il primo numero o 'q' se vuoi terminare l'esecuzione o'ans' se vuoi usare il risultato più vecchio : "<< std::endl;
            std::getline(std::cin, sNum1);
            std::transform(sNum1.begin(), sNum1.end(), sNum1.begin(), [](unsigned char c) {return std::tolower(c); });

            if (sNum1 == "q") {
                return 0;
            }
            else if (sNum1 == "history") {
                int iHistoryPosition = 0;
                for (std::vector<operation>::iterator it = operations.begin(); it != operations.end(); it++) {
                    iHistoryPosition++;
                    std::cout << iHistoryPosition << ": " << it->Num1 << " " << it->oper << " " << it->Num2 << " = " << it->Res << "\n";
                }
            }
            else if (sNum1 == "clear") {
                operations.clear();
            }
            else if (sNum1.find("ans ") != std::string::npos) {
                index = std::stoi(sNum1.substr(4));
                if (index >= 1 && index <= operations.size()) {
                    dNum1 = operations.at(index-1).Res;
                    invalidInput = false;
                }
                else {
                    std::cout << "Operazione non trovata in memoria\n";
                }
            }
            else if (sNum1 == "ans" && validRes) {
                dNum1 = dRes;
                invalidInput = false;
            }
            else if (sNum1 == "ans" && validRes == false) {
                std::cout << "Non è presente nessun risultato immagazzinato.\n";
            }
            else {
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
        std::cin.ignore();

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
            std::cout << "Il risultato dell'operazione: " << dNum1 << " " << operatore << " " << dNum2 << " è " << dRes << "\n" << std::endl;
            validRes = true;
            operations.push_back({dNum1, operatore, dNum2, dRes});
            if (operations.size() > 10) {
                operations.erase(operations.begin());
            }
            
        }

        error = false;
        invalidInput = true;
    }
    
    return 0;
}