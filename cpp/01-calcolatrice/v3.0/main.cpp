#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>

struct operation{
    double Num1;
    char oper;
    double Num2;
    double Res;
};

int main() {
    std::string filename = "history.csv";
    std::string sNum1, memoryLine;
    int index;
    double dNum1, dNum2, dRes;
    char operatore = '+';
    bool error = false, invalidInput = true, validRes = false;
    std::vector<operation> operations;

    std::ifstream file(filename);
    while (std::getline(file, memoryLine))
    {
        double tempN1, tempN2, tempRes;
        char tempOper;
        std::stringstream ss(memoryLine);
        std::string sN1, sOper, sN2, sRes;
        std::getline(ss, sN1, ',');
        std::getline(ss, sOper, ',');
        std::getline(ss, sN2, ',');
        std::getline(ss, sRes, ',');
        tempN1 = std::stod(sN1);
        tempOper = sOper[0];
        tempN2 = std::stod(sN2);
        tempRes = std::stod(sRes);
        operations.push_back({tempN1, tempOper, tempN2, tempRes});
    }
    

    std::cout << "Benvenuto nella calcolatrice!\n   Comandi disponibili:\n\thistory\t→\tmostra le ultime 10 operazioni\n\tclear\t→\tcancella la storia\n\tans\t→\tusa l'ultimo risultato\n\tans N\t→\tusa il risultato N dalla storia\n\tq\t→\tesci"<< std::endl;

    while (true) {
        
        do {
            std::cout << "Inserisci numero o comando:"<< std::endl;
            std::getline(std::cin, sNum1);
            std::transform(sNum1.begin(), sNum1.end(), sNum1.begin(), [](unsigned char c) {return std::tolower(c); });

            if (sNum1 == "q") {
                return 0;
            }
            else if (sNum1 == "history") {
                if (operations.empty())
                {
                    std::cout << "Nessuna operazione in memoria." << std::endl;
                }
                
                int iHistoryPosition = 0;
                for (std::vector<operation>::iterator it = operations.begin(); it != operations.end(); it++) {
                    iHistoryPosition++;
                    std::cout << iHistoryPosition << ": " << it->Num1 << " " << it->oper << " " << it->Num2 << " = " << it->Res << std::endl;
                }
            }
            else if (sNum1 == "clear") {
                operations.clear();
                std::ofstream file(filename, std::ios::trunc);
                std::cout << "Storia cancellata.\n" << std::endl; 
            }
            else if (sNum1.find("ans ") != std::string::npos) {
                index = std::stoi(sNum1.substr(4));
                if (index >= 1 && index <= operations.size()) {
                    dNum1 = operations.at(index-1).Res;
                    invalidInput = false;
                }
                else {
                    std::cout << "Operazione non trovata in memoria\n" << std::endl;
                }
            }
            else if (sNum1 == "ans" && validRes) {
                dNum1 = dRes;
                invalidInput = false;
            }
            else if (sNum1 == "ans" && validRes == false) {
                std::cout << "Non è presente nessun risultato immagazzinato." << std::endl;
            }
            else {
                try {
                    dNum1 = std::stod(sNum1);
                    invalidInput = false;
                }
                catch(const std::exception& e) {
                    std::cerr << e.what() << '\n';
                    std::cout << "Input non valido. Inserisci un numero o un comando valido." << std::endl;
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
            std::cout << "Il risultato dell'operazione: " << dNum1 << " " << operatore << " " << dNum2 << " è " << dRes << std::endl;
            std::ofstream file(filename, std::ios::app);
            file << dNum1 << "," <<  operatore << "," << dNum2 << "," << dRes << "\n";
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