#define _CRT_SECURE_NO_WARNINGS
#define Otopark_Kapasite 1000
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma region Yapilar
typedef struct {
	char Plaka[12];
	char Model[20];
	char Renk[20];
}Araba;

typedef struct {

	Araba Araba;
	char GirisSaat[9];

}Kayit;

typedef struct {
	int KullanilanKapasite;
	Kayit Kayitlar[Otopark_Kapasite];
}Otopark;
#pragma endregion

#pragma region Headerlar
void AracEkle(Otopark);
char* SaatiAl();
void AraclariListele(Otopark);
#pragma endregion

int mainc()
{
	Otopark otopark; otopark.KullanilanKapasite = 0;
	AracEkle(otopark);
	system("PAUSE");
	return 0;
}

#pragma region Metotlar

char* SaatiAl()
{
	time_t theTime = time(NULL);
	struct tm* aTime = localtime(&theTime);
	char Time[9];
	sprintf(Time, "%d:%d:%d", aTime->tm_hour, aTime->tm_min, aTime->tm_sec);
	return Time;
}

void AracEkle(Otopark otopark)
{
	for (int i = 0; i < 5; i++)
	{
		Araba araba;
		printf("%d nolu aracin girisini yapiniz.\n", i + 1);
		printf("Plakanizi giriniz: ");
		gets(araba.Plaka);
		printf("Modeli giriniz: ");
		gets(araba.Model);
		printf("Rengi giriniz: ");
		gets(araba.Renk);
		Kayit kayit;
		kayit.Araba = araba;
		strcpy(kayit.GirisSaat, SaatiAl());
		otopark.Kayitlar[otopark.KullanilanKapasite++] = kayit;
		//1 580 855 545
		//4zxk78
	}
	AraclariListele(otopark);
}
void AraclariListele(Otopark otopark)
{
	system("cls");
	printf("***************************** ARAC LISTESI ****************************\n");
	printf("* %-12s %-20s %-20s %-9s  *\n", "PLAKA", "MODEL", "RENK", "GIRIS SAATI");
	printf("***********************************************************************\n");

	for (size_t i = 0; i < otopark.KullanilanKapasite; i++)
	{
		Araba araba = otopark.Kayitlar[i].Araba;
		char* saat = otopark.Kayitlar[i].GirisSaat;
		printf("* %-12s %-20s %-20s %-9s    *\n", araba.Plaka, araba.Model, araba.Renk, saat);
	}
	printf("***********************************************************************\n");
}
#pragma endregion



