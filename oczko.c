#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
/* ------PUNKTACJA-------
	DWOJKA = 2,
	TROJKA = 3,
	CZWORKA = 4,
	PIATKA = 5,
	SZOSTKA = 6,
	SIODEMKA = 7,
	OSEMKA = 8,
	DZIEWIATKA = 9,
	DZIESIATKA = 10,
	WALET = 2,
	DAMA = 3,
	KROL = 4,
	AS = 11
*/

/*
	--------ZASADY---------
	Gracz dobiera karty, jesli przekroczy 21 przegrywa;
	Bankier dobiera karty po graczu, jeżeli ma poniżej 15 punktów musi dobierać, jeżeli ma 18 lub więcej
	nie może dobierać więcej kart.
	Dwa asy = insta win
	punktacja
	2 do 10 - tyle co numer karty
	walet 2
	dama 3
	krol 5
	as 11





*/

typedef enum 
{
    GRAJ = 1,
    STATYSTYKI = 2,
    ZASADY = 3,
    WYJDZ = 4
} TMenu;

TMenu menu();

void inicjalizacjaTalii(int*);
const char* kolorKarty(int);
int wartoscKarty(int);
const char* figuraKarty(int);
void wyjmijKarte(int*, int);
void rekaGracza(int*, int);
int losuj(int, int*, int*);
int wykonajRuch();
int sumaKart(int*, int);
void ktoWygral(int, int);
bool sprawdzOczko();

void wyswietlZasady();


int main()
{

	//todo PRZEJRZYSTY INTERFEJST

	//STATYSTYKI??
	//MOZE GETCH?
	//opcja PUNKTACJA???
	srand(time( NULL ));
	int kartyGracza[10];
	int kartyBankiera[10];
	int talia[52];
	int ruch;
	int liczbaKartg = 0;
	int liczbaKartb = 0;
	int sumag, sumab;
	TMenu opcje;
	
	do{
		
		opcje = menu();
		
		switch (opcje)
		{
			case GRAJ:
				system("cls");
				inicjalizacjaTalii(talia);
				liczbaKartg = 0;
				sumag = 0;
				liczbaKartb = 0;
				sumab = 0;
				ruch=1;
				//ruch gracza
				do
				{	
					if (ruch==1)
					{
						losuj(liczbaKartg, talia, kartyGracza);			
						liczbaKartg ++;
						rekaGracza(kartyGracza, liczbaKartg);
						printf("Liczba punktow: %d\n", sumaKart(kartyGracza, liczbaKartg));
						if (sumaKart(kartyGracza, liczbaKartg)<21)
							ruch = wykonajRuch();
					}
					else
					{
						system("cls");
						printf("Podano zla wartosc \n");
						rekaGracza(kartyGracza, liczbaKartg);
						printf("Liczba punktow: %d\n", sumaKart(kartyGracza, liczbaKartg));
						ruch = wykonajRuch();
					}
				}while(ruch != 2 && sumaKart(kartyGracza, liczbaKartg)<21);
				int koniec=1;
				//ruch bankiera
				if(sumaKart(kartyGracza, liczbaKartg)<=21)
				{
					do
					{
						if(sumaKart(kartyBankiera, liczbaKartb)<15)
						{
							losuj(liczbaKartb, talia, kartyBankiera);
							liczbaKartb ++;
							rekaGracza(kartyBankiera, liczbaKartb);
							printf("BANKIER: Liczba punktow: %d\n", sumaKart(kartyBankiera, liczbaKartb));
						}
						
						
						else if(sumaKart(kartyBankiera, liczbaKartg)<18)
							if(sumaKart(kartyBankiera, liczbaKartb) < sumaKart(kartyGracza, liczbaKartg))
							{
								losuj(liczbaKartb, talia, kartyBankiera);
								liczbaKartb ++;
								rekaGracza(kartyBankiera, liczbaKartb);
							}
							
							else
								koniec = 0 ;
	
					}while(sumaKart(kartyBankiera, liczbaKartb)<18 && koniec);
				}
				//podsumowanie gry
				sumag = sumaKart(kartyGracza, liczbaKartg);
				sumab = sumaKart(kartyBankiera, liczbaKartb);
				if (sumag == 22 && liczbaKartg == 2 || sumab == 22 && liczbaKartb == 2)
					if (sumag == 22)
					{
						printf("---PERSKIE OCZKO---\n");
						printf("---WYGRYWA GRACZ---\n");
					}
					else if (sumab == 22)
					{
						printf("---PERSKIE OCZKO---\n");
						printf("---WYGRYWA BANKIER---\n");
					}
					else
					{
						printf("---PODWOJNE OCZKO---");
						printf("---REMIS---\n");
					}
				else 
					ktoWygral(sumag, sumab);
		
			break;
			case STATYSTYKI: break;
			case ZASADY: wyswietlZasady(); break;
			case WYJDZ: break;
		}
	}while (opcje != WYJDZ);


return 0;
}

int losuj(int liczbaKart, int* talia, int* kartyGracza)
{
	int karta = rand()%52+1; 
	if(karta >=1 && karta<=52)
	{
		kartyGracza[liczbaKart] = karta;
		if (talia[karta-1] != 0)
		{
			
			talia[karta-1] = 0;
	
			return karta;
		}
	}
		losuj(liczbaKart, talia, kartyGracza);
}
void inicjalizacjaTalii(int* talia)
{
	for (int i=1; i<=52; i++)
		talia[i-1] = i;
}

void wyjmijKarte(int* talia, int karta)
{
	
	
}
const char* kolorKarty(int karta)
{
	
	if(karta>=1 && karta<=13)
		return "pik";
	if(karta>=14 && karta<=26)
		return "kier";
	if(karta>=27 && karta<=39)
		return "karo";
	if(karta>=40 && karta<=52)
		return "trefl";
}
int wartoscKarty(int karta)
{
	if(karta>=1 && karta<=13)
		return karta;
	if(karta>=14 && karta<=26)
		return karta - 13;
	if(karta>=27 && karta<=39)
		return karta - 26;
	if(karta>=40 && karta<=52)
		return karta - 39;
}

const char* figuraKarty(int karta)
{
	
	if(karta==1)
		return "as";
	if(karta==11)
		return "walet";
	if(karta==12)
		return "dama";
	if(karta == 13)
		return "krol";
	
}
int sumaKart(int* rekaGracza, int liczbaKart)
{
	int suma = 0;
	for (int i=0; i<liczbaKart; i++)
	{
		int wartosc = wartoscKarty(rekaGracza[i]);
		
		if(wartosc>=2 && wartosc<=10)
			suma = suma+wartosc;
		else if (wartosc==1)
			suma = suma+11;
		else if (wartosc==11)
			suma = suma+2;
		else if (wartosc==12)
			suma = suma+3;
		else if (wartosc==13)
			suma = suma+4;
	}
	return suma;
	
}
void rekaGracza(int* rekaGracza, int liczbaKart)
{ 	
	printf("---Karty---\n");
	for (int i=0; i<liczbaKart; i++)
	{
		int wartosc = wartoscKarty(rekaGracza[i]);
		if(wartosc>=2 && wartosc<=10)
			printf("%d ", wartosc);
		else if(wartosc==1 || wartosc>=11 && wartosc<=13)
			printf("%s ", figuraKarty(wartosc));
		printf("%s\n", kolorKarty(rekaGracza[i]));
	}
}
bool sprawdzOczko()
{
//	
//	int g1, g2, b1, b2,
//	g1 = wartoscKarty(rekaGracza[0]);
//	g2 = wartoscKarty(rekaGracza[1]);
//	
	
}

void ktoWygral(int sumag, int sumab)
{
	printf("sumaGracza: %d,| sumaBankiera: %d, \n", sumag, sumab);
	if (sumag<=21)
		if (sumab>21)
		{
			printf("---WYGRYWA GRACZ---\n");
			return;
		}
		else if (sumab<=21)
			if(sumag > sumab)
			{
				printf("---WYGRYWA GRACZ---\n");
				return;
			}
			else if (sumag < sumab)
			{
				printf("---WYGRYWA BANKIER---\n");
				return;
			}
	if(sumag>21)
	{
		printf("---WYGRYWA BANKIER---\n");
		return;
	}
	else
	{
		printf("---REMIS---\n");
		return;
	}
}

void wyswietlZasady()
{
	printf("--------ZASADY---------\n");
	printf("Gracz dobiera karty, jesli przekroczy 21 przegrywa;\n");
	printf("Bankier dobiera karty po graczu, jeżeli ma poniżej 15 punktów musi dobierać, jeżeli ma 18 lub więcej\n");
	printf("nie może dobierać więcej kart.\n");
	printf("Dwa asy = insta win\n");
	printf("punktacja\n");
	printf("2 do 10 - tyle co numer karty\n");
	printf("walet 2\n");
	printf("dama 3\n");
	printf("krol 5\n");
	printf("as 11\n");
}
/*
void ruchBankiera(int* bankier, int gracz)
{
	do
	{
		if(*bankier<15)
		{
			losuj(bankier);
			printf("BANKIER ma %d pkt\n", *bankier);
		}
		else if(*bankier <18)
			if (*bankier < gracz)
		{
				losuj(bankier);
				printf("BANKIER ma %d pkt\n", *bankier);
		}	
	}while(*bankier<18);
} 
*/
int wykonajRuch()
{
	printf("---Wykonaj ruch---\n");
	printf("1. Dobierz karte\n");
	printf("2. Pasuj\n");
	int wybor;
	scanf("%d", &wybor);
	return wybor;
}

TMenu menu()
{
	printf("Menu:\n");
	printf("1. Graj\n");
	printf("2. Statystyki\n");
	printf("3. Zasady\n");
	printf("4. Wyjscie\n");
	int opcje;
	scanf("%d", &opcje);
	return opcje;
}
