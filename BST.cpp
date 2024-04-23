#include <iostream>
#include <iomanip>
using namespace std;

struct wezel {
	int wartosc;
	wezel* prawy_adres;
	wezel* lewy_adres;
};

void stworz_drzewo(wezel*& korzen);
void wstaw(wezel*& adres, int podana_wartosc);
void wysokosc_drzewa(wezel* korzen, int licznik, int& wysokosc);
wezel* szukaj(wezel* adres, int szukana_wartosc);
void usun_wezel(wezel*& korzen, int& wysokosc);
void szukaj_usun(wezel*& adres, int szukana_wartosc, wezel*& temp, bool& przypisz, int& iteracja);
wezel* szukacz(wezel* adres, wezel* lewy, wezel* prawy, int& usun_adres);
void wyswietl(wezel* adres, int& licznik, int znacznik, int pierwszy);
void usun_drzewo(wezel* adres);



int main()
{
	int wartosc = 0, wysokosc = 0, licznik = 0, pierwszy = 0, znacznik = 0, wybor = 0;
	wezel* korzen = NULL;
	bool przypisz = 0;
	stworz_drzewo(korzen);
	system("cls");
	for (;;)
	{
		cout << endl;
		wyswietl(korzen, licznik, znacznik, pierwszy);
		licznik = 0;
		cout << endl << endl << "===== MENU ===== " << endl << "1. Pokaz wysokosc drzewa" << endl << "2. Usun wezel" << endl << "3. Wstaw element" << endl << "4. Szukaj elementu" << endl << "5. Wyjdz" << endl;
		cin >> wybor;
		switch (wybor)
		{
		case 1:
		{
			wysokosc_drzewa(korzen, licznik, wysokosc);
			system("cls");
			cout << "Wysokosc drzewa to: " << wysokosc << endl;
			break;
		}
		case 2:
		{
			system("cls");
			usun_wezel(korzen, wysokosc);
			break;
		}
		case 3:
		{
			system("cls");
			cout << "Podaj wartosc, ktora chcesz wstawic: ";
			cin >> wartosc;
			wstaw(korzen, wartosc);
			break;
		}
		case 4:
		{
			system("cls");
			cout << "Podaj szukana wartosc: ";
			cin >> wartosc;
			cout << "Adres wezla o wartosci " << wartosc << " to: " << szukaj(korzen, wartosc)<<endl;
			break;
		}
		case 5:
		{
			usun_drzewo(korzen);
			return 0;
			break;
		}
		default:
			system("cls");
			break;
		}
	}
	usun_drzewo(korzen);
	return 0;
}
void stworz_drzewo(wezel*& korzen)
{
	int podana_wartosc = 0, licznik = 0, wysokosc = 0;
	cout << "Podaj element: ";
	cin >> podana_wartosc;
	while (podana_wartosc != 0)
	{
		wstaw(korzen, podana_wartosc);
		cout << "Podaj nastepny element: ";
		cin >> podana_wartosc;
		licznik = 0;
	}
}
void wstaw(wezel*& adres, int podana_wartosc)
{
	if (adres == NULL)
	{
		wezel* nowy = new wezel;
		(*nowy).wartosc = podana_wartosc;
		(*nowy).prawy_adres = NULL;
		(*nowy).lewy_adres = NULL;
		adres = nowy;
	}
	else if ((*adres).wartosc <= podana_wartosc)
	{
		wstaw((*adres).prawy_adres, podana_wartosc);
	}
	else
	{
		wstaw((*adres).lewy_adres, podana_wartosc);
	}
}
wezel* szukaj(wezel* adres, int szukana_wartosc)
{
	if ((*adres).wartosc == szukana_wartosc)
	{
		return adres;
	}
	else if ((*adres).wartosc <= szukana_wartosc)
	{
		if ((*adres).prawy_adres == NULL)
		{
			cout << "Nie znaleziono szukanej wartosci" << endl;
			return NULL;
		}

		else
			szukaj((*adres).prawy_adres, szukana_wartosc);
	}
	else
	{
		if ((*adres).lewy_adres == NULL)
		{
			cout << "Nie znaleziono szukanej wartosci" << endl;
			return NULL;
		}
		else
			szukaj((*adres).lewy_adres, szukana_wartosc);
	}
}
void usun_wezel(wezel*& korzen, int& wysokosc)
{
	int wartosc_do_usuniecia = 0, licznik = 0, iteracja = 0;
	wezel* temp = NULL;
	bool przypisz = 0;
	if ((*korzen).prawy_adres == NULL && (*korzen).lewy_adres == NULL)
	{
		usun_drzewo(korzen);
		korzen = NULL;
		cout << "Usunales cale drzewo, stworz nowe" << endl;
		stworz_drzewo(korzen);
	}
	else
	{
		cout << "Podaj wartosc wezla, ktory chcesz usunac: ";
		cin >> wartosc_do_usuniecia;
		if (szukaj(korzen, wartosc_do_usuniecia) != NULL)
		{
			szukaj_usun(korzen, wartosc_do_usuniecia, temp, przypisz, iteracja);
			wysokosc = 0;
			wysokosc_drzewa(korzen, licznik, wysokosc);
		}
		else
			cout << "Nie ma takiego wezla" << endl;
	}

}
void szukaj_usun(wezel*& adres, int wartosc_do_usuniecia, wezel*& temp, bool& przypisz, int& iteracja)
{
	iteracja++;
	if ((*adres).wartosc == wartosc_do_usuniecia)
	{
		if ((*adres).lewy_adres == NULL && (*adres).prawy_adres == NULL)
		{
			temp = NULL;
			delete adres;
		}
		else if ((*adres).lewy_adres != NULL && (*adres).prawy_adres == NULL)
		{
			temp = (*adres).lewy_adres;
			if (iteracja == 1) //w przypadku usuniecia korzenia
			{
				adres = temp;
			}
			else
				delete adres;
		}
		else if ((*adres).lewy_adres == NULL && (*adres).prawy_adres != NULL)
		{
			temp = (*adres).prawy_adres;
			if (iteracja == 1) //w przypadku usuniecia korzenia
			{
				adres = temp;
			}
			else
				delete adres;
		}
		else
		{
			int usun_adres = 0;
			temp = szukacz((*adres).prawy_adres, (*adres).lewy_adres, (*adres).prawy_adres, usun_adres);
			if (iteracja == 1) //w przypadku usuniecia korzenia
			{
				adres = temp;
			}
			else
				delete adres;
		}
		przypisz = 1;
	}
	else if ((*adres).wartosc < wartosc_do_usuniecia)
	{
		szukaj_usun((*adres).prawy_adres, wartosc_do_usuniecia, temp, przypisz, iteracja);
		if (przypisz == 1)
		{
			(*adres).prawy_adres = temp;
			przypisz = 0;
		}
	}
	else if ((*adres).wartosc > wartosc_do_usuniecia)
	{
		szukaj_usun((*adres).lewy_adres, wartosc_do_usuniecia, temp, przypisz, iteracja);
		if (przypisz == 1)
		{
			(*adres).lewy_adres = temp;
			przypisz = 0;
		}
	}
}
wezel* szukacz(wezel* adres, wezel* lewy, wezel* prawy, int& usun_adres)
{
	wezel* temp;
	if ((*adres).lewy_adres == NULL)
	{
		(*adres).lewy_adres = lewy;
		if (adres != prawy)//warunek eliminujący przypadek kiedy funkcja wywoła sie tylko 1 raz
		{
			(*adres).prawy_adres = prawy;
		}
		usun_adres = 1;
		return adres;
	}
	else
	{
		temp = szukacz((*adres).lewy_adres, lewy, prawy, usun_adres);
		if (usun_adres == 1)
		{
			(*adres).lewy_adres = NULL;
			usun_adres = 0;
		}

		return temp;
	}


}
void wysokosc_drzewa(wezel* adres, int licznik, int& wysokosc)
{
	licznik++;
	if ((*adres).prawy_adres != NULL)
	{
		wysokosc_drzewa((*adres).prawy_adres, licznik, wysokosc);
	}
	if ((*adres).lewy_adres != NULL)
	{
		wysokosc_drzewa((*adres).lewy_adres, licznik, wysokosc);
	}
	licznik--;
	if (licznik > wysokosc)
	{
		wysokosc = licznik;
	}
}
void wyswietl(wezel* adres, int& licznik, int znacznik, int pierwszy)
{

	if (adres == NULL)
	{
		--licznik;
		return;
	}
	if (pierwszy == 0)
	{
		cout << setw(2) << (*adres).wartosc;
		pierwszy++;
	}
	else
	{
		if (znacznik == 1)
			cout << char(192) << "------- " << setw(2) << (*adres).wartosc;
		else
			cout << " ------- " << setw(2) << (*adres).wartosc;
	}
	znacznik = 0;

	wyswietl((*adres).prawy_adres, ++licznik, znacznik, pierwszy);

	cout << endl;
	for (int i = 0; i < licznik; i++)
		cout << "           ";

	cout << "  ";
	znacznik = 1;

	wyswietl((*adres).lewy_adres, ++licznik, znacznik, pierwszy);

	znacznik = 0;
	licznik--;
	cout << " ";


}
void usun_drzewo(wezel* adres)
{
	if ((*adres).prawy_adres != NULL && (*adres).lewy_adres == NULL)
	{
		usun_drzewo((*adres).prawy_adres);
	}
	if ((*adres).prawy_adres == NULL && (*adres).lewy_adres != NULL)
	{
		usun_drzewo((*adres).lewy_adres);
	}
	if ((*adres).prawy_adres != NULL && (*adres).lewy_adres != NULL)
	{
		usun_drzewo((*adres).prawy_adres);
		usun_drzewo((*adres).lewy_adres);
	}
	if ((*adres).prawy_adres == NULL && (*adres).lewy_adres == NULL)
	{
		delete adres;
	}
}
