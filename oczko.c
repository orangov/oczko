#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

#ifdef _WIN32
#include <Windows.h> //wersja Windows
#include <conio.h>
#include <ctype.h>
#else
#include <unistd.h> //wersja linux
#endif


typedef enum 
{
    GRAJ = 1,
    STATYSTYKI = 2,
    ZASADY = 3,
    PUNKTACJA = 4,
    WYJDZ = 5
} TMenu;

TMenu menu();


void inicjalizacjaTalii(int*);
const char* kolorKarty(int);
int wartoscKarty(int);
const char* figuraKarty(int);
void rekaGracza(int*, int);
int losuj(int, int*, int*);
int wykonajRuch();
int sumaKart(int*, int);
void ktoWygral(int, int);
void podsumowanieGry(int*, int, int*, int);
void statusGry(int*, int , int* , int);
void wyswietlZasady();
void wyswietlP();

bool wczytajPlik();

int t[4]; 

int main()
{
	
	system("cls||clear");

	//TODO przeniesc prototyp dodawania statystyk po meczu
	//reset statystyk??
	//po wyborze w menu cos typu nacisnij cokolwiek aby wrocic do menu
	//to samo po zakonczonej grze
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
			//	system("cls||clear");
				inicjalizacjaTalii(talia);
				liczbaKartg = 0;
				sumag = 0;
				liczbaKartb = 0;
				sumab = 0;
				ruch=1;
				//reka poczatkowa	
				losuj(liczbaKartg, talia, kartyGracza);			
				liczbaKartg ++;
				
				losuj(liczbaKartb, talia, kartyBankiera);
				liczbaKartb ++;
				
				//----------------ruch gracza--------------------
				do
				{	
					if (ruch==1)
					{
						losuj(liczbaKartg, talia, kartyGracza);			
						liczbaKartg ++;
						system("cls||clear");
						statusGry(kartyGracza, liczbaKartg, kartyBankiera, liczbaKartb);
						if (sumaKart(kartyGracza, liczbaKartg)<21)
							ruch = wykonajRuch();
					}
					else
					{
						system("cls||clear");
						printf("Podano zla wartosc \n");
						statusGry(kartyGracza, liczbaKartg, kartyBankiera, liczbaKartb);
						ruch = wykonajRuch();
					}
				}while(ruch != 2 && sumaKart(kartyGracza, liczbaKartg)<21);
				
				//-----------------ruch bankiera---------------
				int koniec=1;
				if(sumaKart(kartyGracza, liczbaKartg)<=21)
				{
					do
					{
						if(sumaKart(kartyBankiera, liczbaKartb)<15)
						{
							system("cls||clear");
							statusGry(kartyGracza, liczbaKartg, kartyBankiera, liczbaKartb);
							printf("---Ruch Bankiera---");
							#ifdef _WIN32
							Sleep(800);
							#else
							usleep(800000);
							#endif
							losuj(liczbaKartb, talia, kartyBankiera);
							liczbaKartb ++;
						}
						
						
						else if(sumaKart(kartyBankiera, liczbaKartg)<=18)
							if(sumaKart(kartyBankiera, liczbaKartb) < sumaKart(kartyGracza, liczbaKartg))
							{
								system("cls||clear");
								statusGry(kartyGracza, liczbaKartg, kartyBankiera, liczbaKartb);
								printf("---Ruch Bankiera---");
								#ifdef _WIN32
								Sleep(800);
								#else
								usleep(800000);
								#endif
								losuj(liczbaKartb, talia, kartyBankiera);
								liczbaKartb ++;
							}
							
							else
								koniec = 0 ;
						
					}while(sumaKart(kartyBankiera, liczbaKartb)<18 && koniec);
				}
				podsumowanieGry(kartyGracza, liczbaKartg, kartyBankiera, liczbaKartb);
			break;
			case STATYSTYKI:
				system("cls||clear");
				if (!wczytajPlik())
				{
					printf("Blad wczytywania danych\n");
					return 1;
				}
					printf("Liczba rozegranych meczy: %d\nZwyciestwa Gracza: %d (%.2f%%)\nZwyciestwa Bankiera: %d (%.2f%%)\nLiczba remisow: %d (%.2f%%)\n ", t[0], t[1], 100.00*t[1]/t[0], t[2], 100.00*t[2]/t[0], t[3], 100.00*t[3]/t[0] ); 
			break;
			case ZASADY: wyswietlZasady(); break;
			case PUNKTACJA: 
				wyswietlP();
				printf("Press Any Key to Continue\n");
				_getch();
				break;
			case WYJDZ: break;
		}
	}while (opcje != WYJDZ);


return 0;
}
bool wczytajPlik()
{
	FILE *f = fopen("stats.txt","rt");
    if (f == NULL)
    {
        printf("Blad otwarcia pliku\n");
        return 1;
    }
    int a;
    int b;
    int c;
    int d;
    if (fscanf(f,"%d%d%d%d", &t[0], &t[1], &t[2], &t[3])==4)	
	{

		return true;
    }
}

int losuj(int liczbaKart, int* talia, int* kartyGracza)
{
	int karta = rand()%52+1; 
	
	if (talia[karta-1] != 0)
	{
		kartyGracza[liczbaKart] = karta;
		talia[karta-1] = 0;

		return karta;
	}

	losuj(liczbaKart, talia, kartyGracza);
}
void inicjalizacjaTalii(int* talia)
{
	for (int i=1; i<=52; i++)
		talia[i-1] = i;
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
void podsumowanieGry(int* kartyGracza, int liczbaKartg, int* kartyBankiera, int liczbaKartb)
{
	system("cls");
	int sumag = sumaKart(kartyGracza, liczbaKartg);
	int sumab = sumaKart(kartyBankiera, liczbaKartb);		
	statusGry(kartyGracza, liczbaKartg, kartyBankiera, liczbaKartb);
	
	
	
	if (sumag == 22 && liczbaKartg == 2 || sumab == 22 && liczbaKartb == 2)
		
		if (sumab == 22 && sumab == 22)

		{
			printf("---PODWOJNE PERSKIE OCZKO---");
			printf("---REMIS---\n");
			printf("----------------------\n");
		}
		else if (sumag == 22)
		{
			printf("---PERSKIE OCZKO---\n");
			printf("---WYGRYWASZ---\n");
			printf("----------------------\n");
		}
		else
		{
			printf("---PERSKIE OCZKO---\n");
			printf("---WYGRYWA BANKIER---\n");
			printf("----------------------\n");
		}
		
	else 
		ktoWygral(sumag, sumab);
}
void statusGry(int* kartyGracza, int liczbaKartg, int *kartyBankiera, int liczbaKartb)
{
	
	printf("----------------------\n");
	printf("---Karty BANKIERA---\n");
	rekaGracza(kartyBankiera, liczbaKartb);
	printf("Liczba punktow: %d\n", sumaKart(kartyBankiera, liczbaKartb));
	printf("----------------------\n");
	printf("---Karty GRACZA---\n");
	rekaGracza(kartyGracza, liczbaKartg);
	printf("Liczba punktow: %d\n", sumaKart(kartyGracza, liczbaKartg));
	printf("----------------------\n");
}


void ktoWygral(int sumag, int sumab)
{
	if (sumag<=21)
		if (sumab>21)
		{
			printf("---WYGRYWASZ---\n");
			printf("----------------------\n");
			return;
		}
		else if (sumab<=21)
			if(sumag > sumab)
			{
				printf("---WYGRYWASZ---\n");
				printf("----------------------\n");
				return;
			}
			else if (sumag < sumab)
			{
				printf("---WYGRYWA BANKIER---\n");
				printf("----------------------\n");
				return;
			}
	if(sumag>21)
	{
		printf("---WYGRYWA BANKIER---\n");
		printf("----------------------\n");
		return;
	}
	else
	{
		printf("---REMIS---\n");
		printf("----------------------\n");
		return;
	}
}

void wyswietlZasady()
{
	system("cls||clear");
	printf("----------------ZASADY-----------------\n");
	printf("Gra polega na tym, aby osiagnac wartosc liczbowa posiadanych kart jak nalblizsza (ale nie wieksza) 21.\n");
	printf("Gracz otrzymuje kolejne karty z talii dotad, az zadecyduje, ze nie chce wiecej kart, lub otrzyma wynik 21 lub wiekszy.\n");
	printf("Bankier musi dobierac karty do momentu, az jego liczba punktow bedzie wieksza lub rowna 15.\n");
	printf("Jezeli bankier po dobraniu karty ma 18 punktow lub wiecej, nie moze dobrac wiecej kart.\n");
	printf("Suma wieksza lub rowna 22 oznacza przegrana. Wyjatkiem jest perskie oczko (dwa asy).\nPerskie oczko oznacza wygrana.\n");
	printf("Jezeli zaden z graczy nie otrzyma wyniku 21, wygrywa ten, kto byl najblizej wartosci.\n");
	printf("-----------------\n");

}
void wyswietlP()
{
	system("cls||clear");
	printf("---PUNKTACJA---\n");
	printf("2 do 10 - tyle pkt. co numer karty\nwalet - 2 pkt.\ndama - 3 pkt.\nkrol - 5 pkt.\nas - 11 pkt.\n");
	printf("-----------------\n");
}

int wykonajRuch()
{
	printf("---WYKONAJ RUCH---\n");
	printf("1. Dobierz karte\n");
	printf("2. Pasuj\n");
	int wybor;
	scanf("%d", &wybor);
	return wybor;
}

TMenu menu()
{
	printf("MENU:\n");
	printf("1. Graj\n");
	printf("2. Statystyki\n");
	printf("3. Zasady\n");
	printf("4. Punktacja\n");
	printf("5. Wyjscie\n");
	int opcje;
	scanf("%d", &opcje);
	return opcje;
}
