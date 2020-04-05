#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma region Yapýlar
typedef enum {
	Bos,
	Dolu
}DoluBos;

typedef struct {
	char* Plaka;
	char* Model;
	char* Renk;
}Araba;

typedef struct {

	Araba Araba;
	char* GirisSaat;

}Kayit;

typedef struct {
	int MaxKapasite;
	int KullanilabilirKapasite;
	int KullanilanKapasite;
	Kayit* Kayitlar;
}Otopark;
#pragma endregion

#pragma region Headerlar
void AracEkle(Otopark*);
char* SaatiAl();
DoluBos KapasiteKontrol(Otopark*);
void AraclariListele(Otopark*);
Otopark OtoparkOlustur(int, int);
void OtoparkTemizle(Otopark*);
#pragma endregion

int mainl()
{
	Otopark otopark = OtoparkOlustur(1000, 5);
	AracEkle(&otopark);
	AraclariListele(&otopark);
	OtoparkTemizle(&otopark);
	system("PAUSE");
	return 0;
}

#pragma region Metotlar

char* SaatiAl()
{
	time_t theTime = time(NULL);
	struct tm* aTime = localtime(&theTime);
	char* Time;
	Time = (char*)malloc(sizeof(char) * 9);
	sprintf(Time, "%d:%d:%d", aTime->tm_hour, aTime->tm_min, aTime->tm_sec);
	return Time;
}
DoluBos KapasiteKontrol(Otopark* otopark)
{
	if (otopark->KullanilanKapasite >= otopark->MaxKapasite)
	{
		return Dolu;
	}
	if (otopark->KullanilabilirKapasite == otopark->KullanilanKapasite)
	{
		otopark->KullanilabilirKapasite++;
		otopark->Kayitlar = (Kayit*)realloc(otopark->Kayitlar, sizeof(Kayit) * otopark->KullanilabilirKapasite);
	}
	return Bos;
}
void AracEkle(Otopark* otopark)
{
	for (int i = 0; i < otopark->KullanilabilirKapasite; i++)
	{
		Araba araba;
		araba.Plaka = (char*)malloc(12 * sizeof(char));
		araba.Model = (char*)malloc(20 * sizeof(char));
		araba.Renk = (char*)malloc(20 * sizeof(char));
		printf("%d nolu aracin girisini yapiniz.\n", i + 1);
		printf("Plakanizi giriniz: ");
		scanf("%s", araba.Plaka);
		printf("Modeli giriniz: ");
		scanf("%s", araba.Model);
		printf("Rengi giriniz: ");
		scanf("%s", araba.Renk);
		Kayit kayit;
		kayit.Araba = araba;
		kayit.GirisSaat = SaatiAl();
		if (KapasiteKontrol(otopark) == Bos)
			otopark->Kayitlar[otopark->KullanilanKapasite++] = kayit;
		else
			printf("Uzgunuz otopark doludur.\n");
	}
}
void AraclariListele(Otopark* otopark)
{
	system("cls");
	printf("*************************** ARAC LISTESI **************************\n");
	printf("%-12s %-20s %-20s %s\n", "PLAKA", "MODEL", "RENK", "GIRIS SAATI");
	printf("*******************************************************************\n");

	for (size_t i = 0; i < otopark->KullanilanKapasite; i++)
	{
		Araba araba = otopark->Kayitlar[i].Araba;
		char* saat = otopark->Kayitlar[i].GirisSaat;
		printf("%-12s %-20s %-20s %s\n", araba.Plaka, araba.Model, araba.Renk, saat);
	}
}
Otopark OtoparkOlustur(int maxKapasite, int kullanilabilirKapasite)
{
	Otopark otopark;
	otopark.MaxKapasite = maxKapasite;
	otopark.KullanilabilirKapasite = kullanilabilirKapasite;
	otopark.KullanilanKapasite = 0;
	otopark.Kayitlar = (Kayit*)malloc(kullanilabilirKapasite * sizeof(Kayit));
	return otopark;
}
void OtoparkTemizle(Otopark* otopark)
{
	free(otopark->Kayitlar);
	otopark->Kayitlar = NULL;
	otopark->KullanilabilirKapasite = otopark->KullanilanKapasite = otopark->MaxKapasite = 0;
}
#pragma endregion