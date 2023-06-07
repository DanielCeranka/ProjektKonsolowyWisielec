#pragma once

#include <iostream>
#include <string>

using namespace std;

void info();

class WisielecGra {
protected:
	string haslo;
	string odpowiedz;
	int pomylki = 0;
	char znak;
public:
	void zgadnijLitere();
	bool czyKoniecGry(int, string);
	void wypiszStanGry(int);
	string zakodujOdp();
	void Gra();
};

class Gracz {
private:
	string nick;
	friend class WisielecGra;
public:
	int iluGraczy();
	void zapiszWynikDoPliku(string, int);
	string daneGracza();
	virtual string wpiszHaslo();
	Gracz();
};

class CzlowiekGracz :public Gracz {
public:
	string wpiszHaslo();
};

class KomputerGracz :public Gracz {
public:
	string wpiszHaslo();
};