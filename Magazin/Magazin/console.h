#pragma once

#include "service.h"
#include <iostream>

class Console {
	Service& service;

public:
	/*
		Functie de creare UI
		service - service produse
		postconditii: obiect de tip console
	*/
	Console(Service& service) noexcept : service{ service } {};
	Console(const Console& ui) = delete;

	/*
		Functie de tiparire lista de produse
		produse - lista de produse
	*/
	void print(const std::vector <Produs>& produse) const;

	/*
		afiseaza comenzile
	*/
	void printCommands();

	/*
		Afiseaza erorile din exceptia aruncata de validator
	*/
	void gestioneazaEroare(ValidatorException ex);

	// Functie de pornire UI
	void start();
};
