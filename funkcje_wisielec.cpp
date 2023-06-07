#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

#include "funkcje_wisielec.h"

using namespace std;

void info() {
	cout << "|===================================================|\n";
	cout << "| Oto konsolowa gra wisielec, autor: Daniel Ceranka |\n";
	cout << "|===================================================|\n\n";
}//funkcja z podstawowymi informacjami

void WisielecGra::Gra() {
	Gracz G;
	if (G.iluGraczy() == 1) {
		CzlowiekGracz C;
		haslo = C.wpiszHaslo();
		odpowiedz = zakodujOdp();
		C.nick = C.daneGracza();
		while (czyKoniecGry(pomylki, odpowiedz) != 1) {
			wypiszStanGry(pomylki);
			zgadnijLitere();
		}
		C.zapiszWynikDoPliku(C.nick, 6 - pomylki);
	}
	else {
		KomputerGracz K;
		haslo = K.wpiszHaslo();
		odpowiedz = zakodujOdp();
		K.nick = K.daneGracza();
		while (czyKoniecGry(pomylki, odpowiedz) != 1) {
			wypiszStanGry(pomylki);
			zgadnijLitere();
		}
		K.zapiszWynikDoPliku(K.nick, 6 - pomylki);
	}
}//funkcja laczy pozostale w calosc i prowadzi rozgrywke

Gracz::Gracz() {
	nick = "brak";
}// konstruktor domyslny klasy Gracz

void WisielecGra::zgadnijLitere() {
	int pom = 1;
	cout << "|===================================================|\n\n\n";
	cout << endl << " " << odpowiedz << endl;
	cout << "\nPodaj znak: ";
	cin >> znak;
	if (getchar() != '\n') {
		while (getchar() != '\n') {
			;
		}
		cout << "\nBledne wyrazenie.\n";
		return;
	}
	znak = tolower(znak);
	for (int i = 0; i < haslo.length(); ++i) {
		if (znak == haslo[i]) {
			odpowiedz[i] = znak;
			pom = 0;
			cout << "\nPoprawna odpowiedz.\n\n\n";
		}
	}
	if(pom == 1){
			cout << "\nBledna odpowiedz.\n\n\n";
			pomylki++;
	}
}//funkcja pyta gracza o wpisanie litery i sprawdza jej poprawnosc

void WisielecGra::wypiszStanGry(int pomylki) {
	if (pomylki == 0) {
		cout << "    +---+\n";
		cout << "    |   |\n";
		cout << "        |\n";
		cout << "        |\n";
		cout << "        |\n";
		cout << "  ______|\n\n";
	}
	if (pomylki == 1) {
		cout << "    +---+\n";
		cout << "    |   |\n";
		cout << "    O   |\n";
		cout << "        |\n";
		cout << "        |\n";
		cout << "  ______|\n\n";
	}
	if (pomylki == 2) {
		cout << "    +---+\n";
		cout << "    |   |\n";
		cout << "    O   |\n";
		cout << "    |   |\n";
		cout << "        |\n";
		cout << "  ______|\n\n";
	}
	if (pomylki == 3) {
		cout << "    +---+\n";
		cout << "    |   |\n";
		cout << "    O   |\n";
		cout << "   /|   |\n";
		cout << "        |\n";
		cout << "  ______|\n\n";
	}
	if (pomylki == 4) {
		cout << "    +---+\n";
		cout << "    |   |\n";
		cout << "    O   |\n";
		cout << "   /|\\  |\n";
		cout << "        |\n";
		cout << "  ______|\n\n";
	}
	if (pomylki == 5) {
		cout << "    +---+\n";
		cout << "    |   |\n";
		cout << "    O   |\n";
		cout << "   /|\\  |\n";
		cout << "   /    |\n";
		cout << "  ______|\n\n";
	}
	if (pomylki == 6) {
		cout << "    +---+\n";
		cout << "    |   |\n";
		cout << "    O   |\n";
		cout << "   /|\\  |\n";
		cout << "   / \\  |\n";
		cout << "  ______|\n\n";
	}
}//funkcja wypisuje biezacy stan gry

bool WisielecGra::czyKoniecGry(int pomylki, string odpowiedz) {
	if (pomylki == 6) {
		wypiszStanGry(pomylki);
		cout << "\nKoniec gry, przegrana :(\n";
		cout << "\nHaslo to: " << haslo << endl;
		return 1;
	}
	else if (odpowiedz == haslo) {
		cout << "\nKoniec gry, wygrana!\n";
		cout << "\nHaslo to: " << haslo << endl;
		cout << "\nIlosc punktow: " << 6 - pomylki << endl;

		return 1;
	}
	else {
		return 0;
	}
}//funkcja sprawdza czy gra sie nie zakonczyla

int Gracz::iluGraczy() {
	string wybor;
	cout << "Ilosc graczy, wybierz: -> 1(gra na dwoch graczy), -> 2(gra z komputerem): ";
	cin >> wybor;

	while (1) {
		bool wyborLiczba = true;
		int liczba;

		for (int i = 0; i < wybor.length(); i++){
			if (!isdigit(wybor[i])) {
				wyborLiczba = false;
			}
		}

		if (wyborLiczba == true) {
			liczba = stoi(wybor);
			if (liczba < 1 || liczba > 2) {
				cout << "Bledny wybor, wybierz jeszcze raz: ";
				while (getchar() != '\n') {
					;
				}
			}
			else {
				return liczba;
			}
		}
		else {
			cout << "Nie podano liczby naturalnej, wybierz jeszcze raz: ";
			while (getchar() != '\n') {
				;
			}
		}
		cin >> wybor;
	}
}//funkcja wywuje zapytanie i ilosc graczy i zwraca odpowiedna liczbe

void Gracz::zapiszWynikDoPliku(string nazwaGracza, int wynik)
{
	ofstream plik("wyniki.txt", ios::app);

	if (plik.is_open()){
		plik << "nick: " << nazwaGracza << ", wynik: " << wynik << endl;
		plik.close();
		cout << "\nWynik zapisano pomyslnie." << endl;
	}
	else{
		cerr << "Nie udalo sie otworzyc pliku do zapisu wyniku." << endl;
	}
}//funkcja zapisuje wynik do pliku

string Gracz::daneGracza() {
	string nazwa;
	cout << "\n\nPodaj nick gracza: ";
	cin >> nazwa;
	return nazwa;
}//funkcja zwraca dane gracza

string Gracz::wpiszHaslo() {
	cout << "Wpisywanie hasla\n";
	return 0;
}//funkcja wirtualna dla wpisywania hasla

string KomputerGracz::wpiszHaslo() {
	srand((unsigned)time(NULL));
	ifstream plik("hasla.txt");
	if (!plik.is_open()) {
		cerr << "B³¹d podczas otwierania pliku" << endl;
		return "";
	}
	
	string linia;

	int iloscLini = 0;
	while (getline(plik, linia)) {
		iloscLini++;
	}

	plik.clear();
	plik.seekg(0, ios::beg);

	int ktoryWiersz = 0;
	ktoryWiersz = rand() % (iloscLini + 1);

	for (int i = 0; i < ktoryWiersz; ++i) {
		if (!getline(plik, linia)) {
			cerr << "Nie mo¿na odczytaæ wiersza o podanym indeksie" << endl;
			return "";
		}
	}


	plik.close();

	return linia;
}//funkcja losuje haslo do zgadniecia dla gracza

string CzlowiekGracz::wpiszHaslo() {
	string haslo;
	char z;

	cout << "\nPodaj haslo do zgadniecia dla osoby grajacej: ";

	while ((z = _getch()) != '\r') {
		if (z == '\b') {
			if (!haslo.empty()) {
				haslo.pop_back();
				cout << "\b \b";
			}
		}
		else {
			haslo.push_back(z);
			cout << '*';
		}
	}
	return haslo;
}//funkcja pozwala drugiemu graczowi na wpisanie hasla

string WisielecGra::zakodujOdp() {
	odpowiedz = haslo;
	for (int i = 0; i < haslo.length(); ++i) {
		haslo[i] = tolower(haslo[i]);
		odpowiedz[i] = '-';
	}
	return odpowiedz;
}//funkcja koduje haslo do zgadniecia