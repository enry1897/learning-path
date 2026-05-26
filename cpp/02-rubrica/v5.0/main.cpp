#include <algorithm>
#include <fstream>
#include <ios>
#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <vector>
using json = nlohmann::ordered_json;

struct date {
	int day;
  	int month;
  	int year;
};

struct contact {
	std::string name;
  	std::string surname;
  	std::string cell;
  	std::optional<std::string> mail;
  	std::optional<std::string> address;
  	std::optional<std::string> notes;
  	std::optional<date> birthday;
};

void to_json(json &j, const date &d) {
  	j["day"] = d.day;
  	j["month"] = d.month;
  	j["year"] = d.year;
}

void from_json(const json &j, date &d) {
  	d.day = j["day"];
  	d.month = j["month"];
  	d.year = j["year"];
}

void to_json(json &j, const contact &c) {
  	j["name"] = c.name;
  	j["surname"] = c.surname;
  	j["cell"] = c.cell;
  	if (c.mail.has_value()) {
		j["mail"] = c.mail.value();
  	}
  	if (c.address.has_value()) {
		j["address"] = c.address.value();
  	}
  	if (c.notes.has_value()) {
		j["notes"] = c.notes.value();
  	}
  	if (c.birthday.has_value()) {
		j["birthday"] = c.birthday.value();
  	}
}

void from_json(const json &j, contact &c) {
  	c.name = j["name"];
  	c.surname = j["surname"];
  	c.cell = j["cell"];
  	if (j.contains("mail")) {
		c.mail = j["mail"];
  	}
  	if (j.contains("address")) {
		c.address = j["address"];
  	}
  	if (j.contains("notes")) {
		c.notes = j["notes"];
  	}
  	if (j.contains("birthday")) {
		c.birthday = j["birthday"];
  	}
}

bool isValidName(std::string s) {
  	for (int i = 0; i < s.length(); i++) {
		if (!std::isalpha(s[i])) {
	  		return false;
		}
 	}
  	return true;
}

bool isValidNumber(std::string s) {
  	int countDigit = 0;
  	for (int i = 0; i < s.length(); i++) {
		if (!std::isdigit(s[i])) {
	  	return false;
		}
		countDigit++;
  }
  if (countDigit > 14) {
	return false;
  }

  return true;
}

void formattingInput(std::string &s) {
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
}

bool checkYear(date d) {
	if (d.year < 1900 || d.year > 2026) {
		std::cout << "Anno inserito errato" << std::endl;
		return false;
	}
	return true;
}

bool checkMonth(date d) {
	if (d.month < 1 || d.month > 12) {
		std::cout << "Mese inserito errato" << std::endl;
		return false;
	}
	return true;
}

bool checkDay(date d) {
	bool leapYear;

	if (d.day <= 0) {
		std::cout << "Giorno inserito errato" << std::endl;
		return false;
	}

	if ((d.year % 4 == 0 && !(d.year % 100 == 0)) || d.year % 400 == 0) {
		leapYear = true;
	}
	else {
		leapYear = false;
	}

	if (d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11) {
		if (d.day > 30) {
			std::cout << "Giorno inserito errato" << std::endl;
			return false;
		}
	}
	else if (leapYear && d.month == 2 && d.day > 29) {
		std::cout << "Giorno inserito errato" << std::endl;
		return false;
	}
	else if (!leapYear && d.month == 2 && d.day > 28) {
		std::cout << "Giorno inserito errato" << std::endl;
		return false;
	}
	else if (d.day > 31) {
		std::cout << "Giorno inserito errato" << std::endl;
		return false;
	}

	return true;
}

void addContact(std::vector<contact> &contacts, std::string filename) {
	contact currentContact;
	std::string optionalCommand, name, surname, cellNum, mail, address, notes;
	date birthday;
	bool invalidOptionalCommand = true;
	
	do {
		std::cout << "Inserisci il nome:" << std::endl;
		std::cin >> name;
	} while (!isValidName(name));

	formattingInput(name);
	name[0] = std::toupper(name[0]);

	currentContact.name = name;

	do {
		std::cout << "Inserisci il cognome:" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, surname);
	} while (!isValidName(surname));

	formattingInput(surname);
	surname[0] = std::toupper(surname[0]);

	currentContact.surname = surname;

	do {
		std::cout << "Inserisci numero di telefono:" << std::endl;
		std::cin >> cellNum;
	} while (!isValidNumber(cellNum));

	currentContact.cell = cellNum;

	do {
		std::cout << "Campi opzionali disponibili:" << std::endl;
					
		if(!currentContact.mail.has_value()){
			std::cout << "mail" << std::endl;
		}
		if (!currentContact.address.has_value()){
		std::cout << "address" << std::endl;
		}
		if (!currentContact.birthday.has_value()) {
			std::cout << "birthday" << std::endl;
		}
		if (!currentContact.notes.has_value()) {
			std::cout << "notes" << std::endl;
		}

		std::cout << "done -> salva contatto\n" << std::endl;

		do {
			invalidOptionalCommand = true;
			std::cout << "Inserisci campo da aggiugnere" << std::endl;
			std::cin >> optionalCommand;
			formattingInput(optionalCommand);

			if (optionalCommand == "mail") {
				std::cout << "Aggiugni mail:" << std::endl;
				std::cin >> mail;
				currentContact.mail = mail;
			}
			else if (optionalCommand == "address") {
				std::cout << "Aggiungi indirizzo:" << std::endl;
				std::cin.ignore();
				std::getline(std::cin, address);
				currentContact.address = address;
			}
			else if (optionalCommand == "birthday") {
				std::cout << "Inserisci data del compleanno:" << std::endl;
				do {	
					std::cout << "Inserisci anno in numero:" << std::endl;
					std::cin >> birthday.year;
				} while (!checkYear(birthday));
				do {
					std::cout << "Inserisci mese in numero:" << std::endl;
					std::cin >> birthday.month;
				} while (!checkMonth(birthday));
				do {
					std::cout << "Inserisci giorno in numero:" << std::endl;
					std::cin >> birthday.day;
				} while (!checkDay(birthday));
				currentContact.birthday = birthday;
			}
			else if (optionalCommand == "notes") {
				std::cout << "Inserisci eventuali note" << std::endl;
				std::cin.ignore();
				std::getline(std::cin, notes);
				currentContact.notes = notes;
			}
			else if (optionalCommand == "done") {
				std::cout << "Nessun'altro campo aggiunto" << std::endl;
			}
			else {
				std::cout << "Inserire commando valido" << std::endl;
				invalidOptionalCommand = false;
			}
		} while (!invalidOptionalCommand);		
	} while (optionalCommand != "done");

	// Aggiungta del nuovo contatto
	contacts.push_back(currentContact);

	// Da vector a json
	json jWrite = contacts;

	// Da json a file
	std::ofstream newFile(filename);
	newFile << jWrite.dump(4);
}

void printContact(contact c) {
	std::cout << "Nome: " << c.name << std::endl;
	std::cout << "Cognome: " << c.surname << std::endl;
	std::cout << "Numero di telefono: " << c.cell<< std::endl;
	if(c.mail.has_value()){
		std::cout << "mail: " << c.mail.value() << std::endl;
	}
	if (c.address.has_value()){
		std::cout << "address: " << c.address.value() << std::endl;
	}
	if (c.birthday.has_value()) {
		std::cout << "birthday (gg/mm/yyyy): " << c.birthday->day << "/" << c.birthday->month << "/" << c.birthday->year << std::endl;
	}
	if (c.notes.has_value()) {
		std::cout << "notes: " << c.notes.value() << std::endl;
	}
}

void saveToFile(std::vector<contact> &contacts, std::string filename) {
    // Da vector a json
	json jWrite = contacts;

	// Da json a file
	std::ofstream newFile(filename);
	newFile << jWrite.dump(4);
}

void removeContact(std::vector<contact> &contacts, std::string filename) {
    int countSameContact = 0, index = 0;
	std::string name, surname;
    std::vector<int> indexToModify;

    std::cout << "Inserisci nome contatto da eliminare" << std::endl;
    std::cin >> name;

    std::cout << "Inserisci cognome contatto da eliminare" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, surname);

    for(contact c : contacts) {
		if (c.name == name && c.surname == surname) {
			countSameContact++;
            indexToModify.push_back(index);
		}
        index++;
	}

	if (indexToModify.size() == 0) {
		std::cout << "Nessun contatto esistente con questo nome" << std::endl;
	}
	else if (indexToModify.size() == 1) {
		char confirm;
		std::cout << "Vuoi eliminare questo contatto [y/n]:" << std::endl;
		printContact(contacts[indexToModify[0]]);

		do {
			std::cin >> confirm;
		} while (confirm != 'y' && confirm != 'n');
		
		if (confirm == 'y') {
			contacts.erase(std::remove_if(contacts.begin() + index, contacts.end(), [&](const contact& c) {return (c.name == name && c.surname == surname);}), contacts.end());
            saveToFile(contacts, filename);
        }
	}
	else if (indexToModify.size() >= 2) {
		int numSameContact = 0, selectedContactToRemove;
		char confirm;

		std::cout << "Ci sono più contatti con lo stesso nome e cognome. Quale vuoi eliminare indicalo con il numero" << std::endl;

		for (int i = 0; i < indexToModify.size(); i++) {
			numSameContact++;
			std::cout << numSameContact << ")";
			printContact(contacts[indexToModify[i]]);
			std::cout << std::endl;
		}

		do {
			std::cout << "Quale dei contatti vuoi eliminare (in numero):" << std::endl;
			std::cin >> selectedContactToRemove;
		} while (selectedContactToRemove > numSameContact  || selectedContactToRemove <= 0);

		std::cout << "Vuoi eliminare questo contatto [y/n]:" << std::endl;
		printContact(contacts[indexToModify[selectedContactToRemove - 1]]);

		do {
			std::cin >> confirm;
		} while (confirm != 'y' && confirm != 'n');
		
		if (confirm == 'y') {
			contacts.erase(std::remove_if(contacts.begin() + index, contacts.end(), [&](const contact& c) {return (c.name == name && c.surname == surname && c.cell == contacts[indexToModify[selectedContactToRemove - 1]].cell);}), contacts.end());
            saveToFile(contacts, filename);
        }
	}
}

void listContact(std::vector<contact> &contacts, std::string filename) {
	char lastLetter = '\0';

	std::sort(contacts.begin(), contacts.end(), [](const contact& a, const contact& b) {return a.name < b.name || (a.name == b.name && a.surname < b.surname);});

	for (contact c : contacts) {
		if (c.name[0] != lastLetter) {
			lastLetter = c.name[0];
			std::cout << "--- " << lastLetter << " ---" << std::endl;
		}
		printContact(c);
        std::cout << std::endl;
	}
}

void searchContact(std::vector<contact> &contacts, std::string filename) {
    char searchedLetter;
    int countContactWithSearchedLetter = 0;

    std::cout << "Quale lettera vuoi cercare:" << std::endl;

    do {
        std::cin >> searchedLetter;
        searchedLetter = std::tolower(searchedLetter);
        if (searchedLetter < 'a' || searchedLetter > 'z') {
            std::cout << "Inserire un carattere valido tra a e z" << std::endl;
        }
    } while (searchedLetter < 'a' || searchedLetter > 'z');

    for (contact c : contacts) {
        if (std::tolower(c.name[0]) == searchedLetter) {
            printContact(c);
            std::cout << std::endl;
            countContactWithSearchedLetter++;
        }
    }     

    if (countContactWithSearchedLetter == 0) {
        std::cout << "Non esistono contatti che iniziano con quella lettera" << std::endl;
    }
}

void editOptionalField(std::optional<std::string> &field, std::string fieldName) {
    std::string newField, commandModifyRemove;

    if(!field.has_value()) {
        std::cout << "Aggiungi il campo" << fieldName << ": " << std::endl;
        
        if (field == "notes"){
            std::cin.ignore();
            std::getline(std::cin, newField);
        }
        else {
            std::cin >> newField;       
        }
        field = newField;
    }
    else {
        do {
            std::cout << "Cosa vuoi fare rimuovere (remove) il campo o modificarlo (modify):" << std::endl;
            std::cin >> commandModifyRemove;

            if (commandModifyRemove == "remove") {
                field = std::nullopt;
            }
            else if (commandModifyRemove == "modify") {
                std::cout << "Come vuoi modificare il campo: " << std::endl;
                if (fieldName != "notes") {
                    std::cin >> newField;
                }
                else {
                    std::cin.ignore();
                    std::getline(std::cin, newField);
                }
                field = newField;
            }
        } while (commandModifyRemove != "remove" && commandModifyRemove != "modify");
    }
}

void editBirthday(std::optional<date> &field) {
    std::string newField, commandModifyRemove;
    date tempDate;

    if(!field.has_value()) {
        std::cout << "Inserisci data del compleanno:" << std::endl;
		do {	
			std::cout << "Inserisci anno in numero:" << std::endl;
			std::cin >> tempDate.year;
		} while (!checkYear(tempDate));
		do {
			std::cout << "Inserisci mese in numero:" << std::endl;
			std::cin >> tempDate.month;
		} while (!checkMonth(tempDate));
		do {
			std::cout << "Inserisci giorno in numero:" << std::endl;
			std::cin >> tempDate.day;
		} while (!checkDay(tempDate));

        field = tempDate;
    }
    else {
        do {
            std::cout << "Cosa vuoi fare rimuovere (remove) il campo o modificarlo (modify):" << std::endl;
            std::cin >> commandModifyRemove;

            if (commandModifyRemove == "remove") {
                field = std::nullopt;
            }
            else if (commandModifyRemove == "modify") {
                do {	
			        std::cout << "Inserisci anno in numero da modificare:" << std::endl;
			        std::cin >> tempDate.year;
		        } while (!checkYear(tempDate));
		        do {
		        	std::cout << "Inserisci mese in numero da modificare:" << std::endl;
		        	std::cin >> tempDate.month;
		        } while (!checkMonth(tempDate));
		        do {
		        	std::cout << "Inserisci giorno in numero da modificare:" << std::endl;
		        	std::cin >> tempDate.day;
		        } while (!checkDay(tempDate));

                field = tempDate;
            }
        } while (commandModifyRemove != "remove" && commandModifyRemove != "modify");
    }
}

void modifyContact(contact &c) {
    std::string modifyCommand, modifyRemove, mail;
    bool isValidCommand;
    
    do {
        std::cout << "Cosa vuoi modificare:" << std::endl;
        std::cout << "Nome: " << c.name << std::endl;
        std::cout << "Cognome: " << c.surname << std::endl;
        std::cout << "Numero di telefono: " << c.cell << std::endl;
        if(c.mail.has_value()){
	        std::cout << "mail: " << c.mail.value() << std::endl;
        }
        if (c.address.has_value()){
	        std::cout << "address: " << c.address.value() << std::endl;
	    }
        if (c.birthday.has_value()) {
	        std::cout << "birthday (gg/mm/yyyy): " << c.birthday->day << "/" << c.birthday->month << "/" << c.birthday->year << std::endl;
        }
        if (c.notes.has_value()) {
	        std::cout << "notes: " << c.notes.value() << std::endl;
        }

        std::cin >> modifyCommand;
        if (modifyCommand == "name") {
            std::cout << "Inserisci nuovo nome:" << std::endl;
            std::cin >> c.name;
        }
        else if (modifyCommand == "surname") {
            std::cout << "Inserisci nuovo cognome:" << std::endl;
            std::cin >> c.surname;
        }
        else if (modifyCommand == "cell") {
            std::cout << "Inserisci nuovo numero di telefono" << std::endl;
            std::cin >> c.cell;
        }
        else if (modifyCommand == "mail") {
            editOptionalField(c.mail, "mail");
        }
        else if (modifyCommand == "address") {
            editOptionalField(c.address, "address");
        }
        else if (modifyCommand == "notes") {
            editOptionalField(c.notes, "notes");
        }
        else if (modifyCommand == "birthday") {
            editBirthday(c.birthday);
        }
        else {
            std::cout << "Comando di modifica errato." << std::endl;
        }
    } while (modifyCommand != "done");
}

void editContact(std::vector<contact> &contacts, std::string filename) {
    int countSameContact = 0, index = 0;
	std::string name, surname;
    std::vector<int> indexToModify;

    std::cout << "Inserisci nome contatto da modificare" << std::endl;
    std::cin >> name;

    std::cout << "Inserisci cognome contatto da modificare" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, surname);

    for(contact c : contacts) {
		if (c.name == name && c.surname == surname) {
			countSameContact++;
            indexToModify.push_back(index);
		}
        index++;
	}

    if (countSameContact == 0) {
		std::cout << "Nessun contatto esistente con questo nome" << std::endl;
	}
	else if (countSameContact == 1) {
		char confirm;
		std::cout << "Vuoi modificare questo contatto [y/n]:" << std::endl;
		printContact(contacts[indexToModify[0]]);

		do {
			std::cin >> confirm;
		} while (confirm != 'y' && confirm != 'n');

        modifyContact(contacts[indexToModify[0]]);
	}
	else if (countSameContact >= 2) {
		int numSameContact = 0, selectedContactToModify;
		char confirm;

		std::cout << "Ci sono più contatti con lo stesso nome e cognome. Quale vuoi eliminare indicalo con il numero" << std::endl;

		for (int i = 0; i < indexToModify.size(); i++) {
			numSameContact++;
			std::cout << numSameContact << ")";
			printContact(contacts[indexToModify[i]]);
			std::cout << std::endl;
		}

		do {
			std::cout << "Quale dei contatti vuoi modificare (in numero):" << std::endl;
			std::cin >> selectedContactToModify;
		} while (selectedContactToModify > numSameContact  || selectedContactToModify <= 0);

		std::cout << "Vuoi modificare questo contatto [y/n]:" << std::endl;
		printContact(contacts[indexToModify[selectedContactToModify - 1]]);

		do {
			std::cin >> confirm;
		} while (confirm != 'y' && confirm != 'n');
		
		if (confirm == 'y') {
			modifyContact(contacts[indexToModify[selectedContactToModify - 1]]);
		}
	}

	// Da vector a json
	json jWrite = contacts;

	// Da json a file
	std::ofstream newFile(filename);
	newFile << jWrite.dump(4);
}

int main() {
	std::string filename = "memory.json";
  	std::vector<contact> contacts;
	contact currentContact;
  	std::string command, name, surname, cellNum, mail, address, birthday, notes, optionalCommand;

	std::ifstream originalFile(filename);
	if(originalFile.is_open() && originalFile.peek() != EOF) {
    	json jRead = json::parse(originalFile);
    	contacts = jRead.get<std::vector<contact>>();
	}

  	std::cout << "Benvenuto nella tua rubrica!\n Comandi disponibili:\n\tadd\t→\taggiungi un contatto alla rubrica\n\tremove\t→\trimuovi un contatto dall'elenco\n\tlist\t→\tmostra i contatti salvati in rubrica\n\tsearch\t→\tcerca i contatti in base alla lettera\n\tedit\t→\tmodifica i contatti che hai in rubrica\n\tquit\t→\tesci dal programma" << std::endl;

  	while (true) {	
		std::cout << "Inserisci comando:" << std::endl;
		std::cin >> command;
		std::transform(command.begin(), command.end(), command.begin(), [](unsigned char c) { return std::tolower(c); });

		if (command == "quit") {
			return 0;
		}
		else if (command == "add") {
			addContact(contacts, filename);
		}
        else if (command == "remove") {
            removeContact(contacts, filename);
        }
        else if (command == "list") {
            listContact(contacts, filename);
        }
        else if (command == "search") {
            searchContact(contacts, filename);
        }
        else if (command == "edit") {
            editContact(contacts, filename);
        }
		else {
			std::cout << "Comando non riconosciuto. Riprova." << std::endl;
		}
    }

  return 0;
}