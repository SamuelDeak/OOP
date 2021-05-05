#include "console.h"

void Console::print(const std::vector <Produs>& produse) const {
	for (unsigned int i = 0; i < produse.size(); i++) {
		std::cout << "Nume: " << produse[i].GetNume() << '\n';
		std::cout << "Pret: " << produse[i].GetPret() << '\n';
		std::cout << "Producator: " << produse[i].GetProducator() << '\n';
		std::cout << "Tip: " << produse[i].GetTip() << '\n';
		std::cout << '\n';
	}
}

void Console::printCommands() {
	std::cout << "-----------------------------------" << "\n";
	std::cout << "Aplicatie gestiune magazin\n";
	std::cout << "1. Adaugare produs\n";
	std::cout << "2. Stergere produs\n";
	std::cout << "3. Modificare produs\n";
	std::cout << "4. Cautare produs\n";
	std::cout << "5. Afisare produs\n";
	std::cout << "6. Filtrare produs\n";
	std::cout << "7. Sortare produs\n";
	std::cout << "0. Exit\n";
	std::cout << '\n';
}

void Console::gestioneazaEroare(ValidatorException ex) {
	auto mesajeDeEroare = ex.GetMesaje();
	for (int i = 0; i < mesajeDeEroare.size(); i++) {
		std::cout << mesajeDeEroare[i] << "\n";
	}
}

void Console::start() {
	int cmd = 0;

	do {
		printCommands();

		std::cout << "Dati comanda: "; std::cin >> cmd; std::cout << '\n';

		if (cmd == 1) {
			std::string nume, producator, tip; int pret;
			std::cout << "Dati nume: "; std::cin >> nume;
			std::cout << "Dati producatorul: "; std::cin >> producator;
			std::cout << "Dati tipul produsului: "; std::cin >> tip;
			std::cout << "Dati pretul: "; std::cin >> pret;
			std::cout << '\n';
			try {
				service.AdaugaProdus(Produs(nume, tip, producator, pret));
			}
			catch (ValidatorException ex) {
				gestioneazaEroare(ex);
			}
		}
		
		if (cmd == 2) {
			std::string nume;
			std::cout << "Dati nume: "; std::cin >> nume;
			try {
				service.StergeProdus(nume);
			}
			catch (ValidatorException ex) {
				gestioneazaEroare(ex);
			}
		}

		if (cmd == 3) {
			std::string numeVechi, numeNou, producatorNou, tipNou; int pretNou;
			std::cout << "Dati nume vechi: "; std::cin >> numeVechi;
			std::cout << "Dati nume nou: "; std::cin >> numeNou;
			std::cout << "Dati pretul nou: "; std::cin >> pretNou;
			std::cout << "Dati producatorul nou: "; std::cin >> producatorNou;
			std::cout << "Dati tipul nou: "; std::cin >> tipNou;
			std::cout << '\n';
			try {
				service.EditeazaProdus(numeVechi, Produs(numeNou, producatorNou, tipNou, pretNou));
			}
			catch (ValidatorException ex) {
				gestioneazaEroare(ex);
			}
		}

		if (cmd == 4) {
			std::string nume;
			std::cout << "Dati numele produsului: "; std::cin >> nume;
			const int i = service.FindByNume(nume);
			if (i != -1) {
				std::cout << "Pret: " << service.GetAll()[i].GetPret() << '\n';
				std::cout << "Producator: " << service.GetAll()[i].GetProducator() << '\n';
				std::cout << "Tip: : " << service.GetAll()[i].GetTip() << '\n';
			}
			else std::cout << "Nu exista acest produs!\n";
			std::cout << '\n';
		}

		if (cmd == 5) print(service.GetAll());

		if (cmd == 6) {
			std::cout << "1. Dupa pret\n";
			std::cout << "2. Dupa tip\n";
			std::cout << "3. Dupa producator\n";
			std::cout << '\n';
			std::cout << "Dati comanda: "; std::cin >> cmd; std::cout << '\n';

			if (cmd == 1) {
				int pret = 0;
				std::cout << "Dati pretul: "; std::cin >> pret; std::cout << '\n';
				print(service.FiltreazaDupaPret(pret));
			}

			if (cmd == 2) {
				std::string nume;
				std::cout << "Dati nume: "; std::cin >> nume; std::cout << '\n';
				print(service.FiltreazaDupaNume(nume));
			}

			if (cmd == 3) {
				std::string producator;
				std::cout << "Dati producatorul: "; std::cin >> producator; std::cout << '\n';
				print(service.FiltreazaDupaProducator(producator));
			}
		}

		if (cmd == 7) {
			std::cout << "1. Dupa nume\n";
			std::cout << "2. Dupa pret\n";
			std::cout << "3. Dupa nume si tip\n";
			std::cout << '\n';
			std::cout << "Dati comanda: "; std::cin >> cmd; std::cout << '\n';

			if (cmd == 1) print(service.SorteazaDupaNume());
			if (cmd == 2) print(service.SorteazaDupaPret());
			if (cmd == 3) print(service.SorteazaDupaNumeSiTip());
		}
	} while (cmd);
}
