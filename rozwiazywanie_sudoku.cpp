#include<iostream>
#include<fstream>
#include<windows.h>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

void wypisz_cale(int T[9][9])
{
	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			cout<<T[i][j];
			if(j==2||j==5)
			{
				cout<<" | ";
			}
			else
			{
				cout<<" ";
			}
		}
		cout<<"\n";
		if(i==2||i==5)
		{
			for(int j = 0; j < 21; ++j)
			{
				cout<<"_";
			}
			cout<<"\n";
		}
	}
}

void wypisz_do_pliku(int T[9][9])
{
	fstream wynik("rozwiazane _sudoku.txt",ios::out);
	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			wynik<<T[i][j];
			if(j==2||j==5)
			{
				wynik<<" | ";
			}
			else
			{
				wynik<<" ";
			}
		}
		wynik<<"\n";
		if(i==2||i==5)
		{
			for(int j = 0; j < 21; ++j)
			{
				wynik<<"_";
			}
			wynik<<"\n";
		}
	}
	wynik.close();
}

bool sprawdzaj_sprzecznosci(int T[9][9])
{
	for(int i = 0; i < 9; ++i)
	{
		if(sprawdzaj_sprzecznosci_wiersz(T,i)||sprawdzaj_sprzecznosci_kolumna(T,i)||sprawdzaj_sprzecznosci_kwadrat(T,i))
		{
			return true;
		}
	}
	return false;
}

bool sprawdzaj_sprzecznosci_wiersz(int T[9][9], int wiersz)
{
	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			if(T[j][wiersz]==T[i][wiersz]&&i!=j&&T[j][wiersz])
			{
				return true;
			}
		}
	}
	return false;
}

bool sprawdzaj_sprzecznosci_kolumna(int T[9][9], int wiersz)
{
	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			if(T[kolumna][j]==T[kolumna][i]&i!=j&&[kolumna]T[j])
			{
				return true;
			}
		}
	}
	return false;
}

bool sprawdzaj_sprzecznsoci_kwadrat(int T[9][9], int wiersz)
{
	
}

void analizuj_bT( int T[9][9], bool bT[9][9][9])
{
	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			if(T[i][j])
			{
				for(int k = 0; k < 9; ++k)
				{
					
				}
			}
		}
	}
}

int main()
{
	fstream plik("plik_sudoku.txt",ios::in);
	int T[9][9];
	bool bT[9][9][9] = {true};
	cout<<"podaj liczby wierszami odz, \n 0 oznacza puste miejsce\n";
	bool czy_poprawne = true;
	for(int i = 0; i < 9; ++i)
	{
		cout<<"podaj wiersz: "<<i+1<<"\n";
		for(int j = 0; j < 9; ++j)
		{
			//cin>>T[i][j];
			plik>>T[i][j];
			if(!T[i][j])
			{
				czy_poprawne=false;
			}
		}
	}
	cout<<"\n";
	if(!czy_poprawne||sprawdzaj_sprzecznosci(T))
	{
		cout<<"sudoku niepoprawne";
	}
	else
	{
		
	}
	wypisz_cale(T);
	wypisz_do_pliku(T);
	system("pause");
	return 0;
}

