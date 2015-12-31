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

void wypisz_cale(int T[9][9]);

void wypisz_do_pliku(int T[9][9]);

bool sprawdzaj_sprzecznosci_wiersz(int T[9][9], int wiersz);

bool sprawdzaj_sprzecznosci_kolumna(int T[9][9], int kolumna);

bool sprawdzaj_sprzecznsoci_kwadrat(int T[9][9], int wiersz_kwadrat, int kolumna_kwadratu);

bool sprawdzaj_sprzecznosci(int T[9][9]);

bool czy_mozna_wstawic_w_wiersz(int T[9][9], int wiersz, int cyfra);

bool czy_mozna_wstawic_w_kolumne(int T[9][9], int kolumna, int cyfra);

bool czy_mozna_wstawic_w_kwadrat(int T[9][9], int wiersz_kwadrat, int kolumna_kwadratu, int cyfra);

bool czy_mozna_wstawic(int T[9][9], int wiersz, int kolumna, int cyfra);

void analizuj_bT(int T[9][9], bool bT[9][9][9]);

void analizuj_wszystko(int T[9][9], bool bT[9][9][9], int ile_wolnych_wiersz[9], int ile_wolnych_kolumna[9], int ile_wolnych_kwadrat[3][3], bool mozna_wstawiac_w_wiersz[9][9], bool mozna_wstawiac_w_kolumne[9][9], bool mozna_wstawiac_w_kwadrat[3][3][9]);

void analizuj_ile_wolnych_wiersz(int T[9][9], int ile_wolnych_wiersz[9], int wiersz);

void analizuj_ile_wolnych_kolumna(int T[9][9], int ile_wolnych_kolumna[9], int kolumna);

void analizuj_ile_wolnych_kwadrat(int T[9][9], int ile_wolnych_kwadrat[3][3], int wiersz_kwadratu, int kolumna_kwadratu);

void analizuj_ile_wolnych(int T[9][9], int ile_wolnych_wiersz[9], int ile_wolnych_kolumna[9], int ile_wolnych_kwadrat[3][3]);

void analizuj_co_mozna_wstawic_w_wiersz(int T[9][9], bool mozna_wastawiac_w_wiersz[9][9], int kolumna);

void analizuj_co_mozna_wstawic_w_kolumne(int T[9][9], bool mozna_wstwic_w_kolumne[9][9], int kolumna);

void analizuj_co_mozna_wstawic_w_kwadrat(int T[9][9], bool mozna_wastawiac_w_kwadrat[3][3][9], int kolumna);

void rozwiazuj(int T[9][9], bool bT[9][9][9], int ile_wolnych_wiersz[9], int ile_wolnych_kolumna[9], int ile_wolnych_kwadrat[3][3], bool mozna_wstawiac_w_wiersz[9][9], bool mozna_wstawiac_w_kolumne[9][9], bool mozna_wstawiac_w_kwadrat[3][3][9]);

void brute_force(int T[9][9]);

int main()
{
	int wybor;
	bool czy_poprawne = true;
	fstream plik("plik_sudoku.txt",ios::in);
	int T[9][9];
	bool bT[9][9][9] = {true};
	int ile_wolnych_wiersz[9] = {0};
	int ile_wolnych_kolumna[9] = {0};
	int ile_wolnych_kwadrat[3][3] = {0};
	bool mozna_wstawiac_w_wiersz[9][9] ={true};
	bool mozna_wstawiac_w_kolumne[9][9] ={true};
	bool mozna_wstawiac_w_kwadrat[3][3][9] ={true};
	cout<<"czytac z konsoli(1), czy zpliku plik_sudoku.txt(1)?\n";
 	cout<<"podaj liczby wierszami odzielone spacj¹, 0 oznacza puste miejsce\n";
 	cin>>wybor;
 	if(wybor)
 	{
 		for(int i = 0; i < 9; ++i)
		{
			for(int j = 0; j < 9; ++j)
			{
				plik>>T[i][j];
				if(T[i][j]>9)
				{
					czy_poprawne=false;
				}
			}
		}
	}
	else
	{
 		for(int i = 0; i < 9; ++i)
		{
			cout<<"podaj wiersz: "<<i+1<<"\n";
			for(int j = 0; j < 9; ++j)
			{
				cin>>T[i][j];
				if(T[i][j]>9)
				{
					czy_poprawne=false;
				}
			}
		}
	}
	cout<<"\n";
	if(!czy_poprawne||sprawdzaj_sprzecznosci(T))
	{
		cout<<"sudoku niepoprawne\n";
		wypisz_cale(T);
		wypisz_do_pliku(T);
		system("pause");
		return 0;
	}
	else
	{
		cout<<"brak sprzecznosci\n";
	}
	wypisz_cale(T);
	analizuj_bT(T,bT);
	rozwiazuj(T, bT, ile_wolnych_wiersz, ile_wolnych_kolumna, ile_wolnych_kwadrat, mozna_wstawiac_w_wiersz, mozna_wstawiac_w_kolumne, mozna_wstawiac_w_kwadrat);
	system("pause");
	return 0;
}

void brute_force(int T[9][9])
{
	int index_i = -1, index_j = -1;
	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			if(!T[i][j])
			{
				index_i = i;
				index_j = j;
				goto za_forem;			
			}
		}
	}
	za_forem:
	if(index_i>-1)
	{
		for(int k = 1; k < 10; ++k)
		{
			if(czy_mozna_wstawic(T, index_i, index_j, k))
			{
				T[index_i][index_j] = k;
				brute_force(T);
				T[index_i][index_j] = 0;
			}
		}
	}
	else
	{
		cout<<"skoñczy³em!!!\n";
		wypisz_do_pliku(T);		
		wypisz_cale(T);
	}
	return;
}

void rozwiazuj(int T[9][9], bool bT[9][9][9], int ile_wolnych_wiersz[9], int ile_wolnych_kolumna[9], int ile_wolnych_kwadrat[3][3], bool mozna_wstawiac_w_wiersz[9][9], bool mozna_wstawiac_w_kolumne[9][9], bool mozna_wstawiac_w_kwadrat[3][3][9])
{
	analizuj_wszystko(T, bT, ile_wolnych_wiersz, ile_wolnych_kolumna, ile_wolnych_kwadrat, mozna_wstawiac_w_wiersz, mozna_wstawiac_w_kolumne, mozna_wstawiac_w_kwadrat);
	cout<<"rozwi¹zuje si³owo...\n";
	brute_force(T);// na razie tylko to dzia³a... :(
}

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
	fstream wynik("rozwiazane_sudoku.txt",ios::out);
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

bool sprawdzaj_sprzecznosci_wiersz(int T[9][9], int wiersz)
{
	int tab_wystapien[10] = {0};
	for(int i = 0; i < 9; ++i)
	{
		tab_wystapien[T[i][wiersz]]++;
	}
	for(int i = 1; i < 10; ++i)
	{
		if(tab_wystapien[i]>1)
		{
			return true;
		}
	}
	return false;
}

bool sprawdzaj_sprzecznosci_kolumna(int T[9][9], int kolumna)
{
	int tab_wystapien[10] = {0};
	for(int i = 0; i < 9; ++i)
	{
		tab_wystapien[T[kolumna][i]]++;
	}
	for(int i = 1; i < 10; ++i)
	{
		if(tab_wystapien[i]>1)
		{
			return true;
		}
	}
	return false;
}

bool sprawdzaj_sprzecznsoci_kwadrat(int T[9][9], int wiersz_kwadrat, int kolumna_kwadratu)
{
	int tab_wystapien[10] = {0};
	for(int i = wiersz_kwadrat*3; i < (wiersz_kwadrat*3)+3; ++i)
	{
		for(int j = kolumna_kwadratu*3; j < (kolumna_kwadratu*3)+3; ++j)
		{
			tab_wystapien[T[i][j]]++;
		}
	}
	for(int i = 1; i < 10; ++i)
	{
		if(tab_wystapien[i]>1)
		{
			return true;
		}
	}
	return false;
}

bool sprawdzaj_sprzecznosci(int T[9][9])
{
	for(int i = 0; i < 9; ++i)
	{
		if(sprawdzaj_sprzecznosci_wiersz(T,i)||sprawdzaj_sprzecznosci_kolumna(T,i))
		{
			return true;
		}
	}
	for(int i_ = 0; i_ < 3; ++i_)
	{
		for(int j_ = 0; j_ < 3; ++j_)
		{
			if(sprawdzaj_sprzecznsoci_kwadrat(T,i_,j_))
			{
				return true;
			}
		}
	}
	return false;
}

bool czy_mozna_wstawic_w_wiersz(int T[9][9], int wiersz, int cyfra)
{
	for(int i = 0; i < 9; ++i)
	{
		if(T[wiersz][i]==cyfra)
		{
			return false;
		}
	}
	return true;	
}

bool czy_mozna_wstawic_w_kolumne(int T[9][9], int kolumna, int cyfra)
{
	for(int i = 0; i < 9; ++i)
	{
		if(T[i][kolumna]==cyfra)
		{
			return false;
		}
	}
	return true;
}

bool czy_mozna_wstawic_w_kwadrat(int T[9][9], int wiersz_kwadrat, int kolumna_kwadratu, int cyfra)
{
	for(int i = wiersz_kwadrat*3; i < (wiersz_kwadrat*3)+3; ++i)
	{
		for(int j = kolumna_kwadratu*3; j < (kolumna_kwadratu*3)+3; ++j)
		{
			if(T[i][j]==cyfra)
			{
				return false;
			}
		}
	}
	return true;
}

bool czy_mozna_wstawic(int T[9][9], int wiersz, int kolumna, int cyfra)
{
	return (czy_mozna_wstawic_w_wiersz(T,wiersz,cyfra)&&czy_mozna_wstawic_w_kolumne(T,kolumna,cyfra)&&czy_mozna_wstawic_w_kwadrat(T,wiersz/3,kolumna/3,cyfra))?true:false;	
}

void analizuj_bT(int T[9][9], bool bT[9][9][9])
{
	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			if(T[i][j])
			{
				for(int k = 0; k < 9; ++k)
				{
					bT[i][j][k] = false;
				}
			}
			else
			{
				for(int k = 0; k < 9; ++k)
				{
					if(czy_mozna_wstawic(T,i,j,k+1))
					{
						bT[i][j][k]=true;
					}
				}
			}
		}
	}
}

void analizuj_wszystko(int T[9][9], bool bT[9][9][9], int ile_wolnych_wiersz[9], int ile_wolnych_kolumna[9], int ile_wolnych_kwadrat[3][3], bool mozna_wstawiac_w_wiersz[9][9], bool mozna_wstawiac_w_kolumne[9][9], bool mozna_wstawiac_w_kwadrat[3][3][9])
{
	analizuj_bT(T,bT);
	analizuj_ile_wolnych(T, ile_wolnych_wiersz, ile_wolnych_kolumna, ile_wolnych_kwadrat);
	for(int i = 0; i < 9; ++i)
	{
		for(int j = 0; j < 9; ++j)
		{
			if(T[i][j])
			{
				mozna_wstawiac_w_wiersz[i][T[i][j]-1] = false;
				mozna_wstawiac_w_kolumne[j][T[i][j]-1] = false;
			}
		}
	}
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			for(int k = 0; k < 9; ++k)
			{
				mozna_wstawiac_w_kwadrat[i][j][k] = czy_mozna_wstawic_w_kwadrat(T, i, j, k+1);
			}
		}
	}
}

void analizuj_ile_wolnych_wiersz(int T[9][9], int ile_wolnych_wiersz[9], int wiersz)
{
	for(int i = 0; i < 9; ++i)
	{
		if(!T[wiersz][i])
		{
			ile_wolnych_wiersz[wiersz]++;
		}
	}
}

void analizuj_ile_wolnych_kolumna(int T[9][9], int ile_wolnych_kolumna[9], int kolumna)
{
	for(int i = 0; i < 9; ++i)
	{
		if(!T[i][kolumna])
		{
			ile_wolnych_kolumna[kolumna]++;
		}
	}
}

void analizuj_ile_wolnych_kwadrat(int T[9][9], int ile_wolnych_kwadrat[3][3], int wiersz_kwadratu, int kolumna_kwadratu)
{
	for(int i = wiersz_kwadratu*3; i < (wiersz_kwadratu*3)+3; ++i)
	{
		for(int j = kolumna_kwadratu*3; j < (kolumna_kwadratu*3)+3; ++j)
		{
			if(!T[i][j])
			{
				ile_wolnych_kwadrat[wiersz_kwadratu][kolumna_kwadratu]++;
			}
		}
	}
}

void analizuj_ile_wolnych(int T[9][9], int ile_wolnych_wiersz[9], int ile_wolnych_kolumna[9], int ile_wolnych_kwadrat[3][3])
{
	for(int i = 0; i < 9; ++i)
	{
		analizuj_ile_wolnych_wiersz(T,ile_wolnych_wiersz,i);
		analizuj_ile_wolnych_kolumna(T,ile_wolnych_kolumna,i);
	}
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			analizuj_ile_wolnych_kwadrat(T,ile_wolnych_kwadrat,i,j);
		}
	}	
}

