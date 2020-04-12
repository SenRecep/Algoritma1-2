#pragma region Definitions
#define _CRT_SECURE_NO_WARNINGS
#define Number_Of_Cars_To_Be_Added_First 5
#define MaximumCapasity 1000
#define StringLenght_1 25
#define StringLenght_2 12  
#pragma endregion

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma region Types

typedef struct {
	char Plaque[StringLenght_2];
	char Model[StringLenght_1];
	char Color[StringLenght_1];
}Car;
typedef struct {
	unsigned short H;
	unsigned short M;
	unsigned short S;
}EntryTime;
typedef struct {
	Car car;
	EntryTime time;

}ParkingRegistration;

typedef struct {
	ParkingRegistration ParkingRegistrations[MaximumCapasity];
	size_t Used;
}CarPark;

#pragma endregion
#pragma region Headers
void Menu(CarPark);
CarPark CarAddMenu(CarPark);
CarPark AddCar(CarPark, Car);
CarPark AddCars(CarPark, int);
void ListCar(CarPark);
EntryTime GetCurrentTime();
#pragma endregion
void main() {
	CarPark cp; cp.Used = 0;
	Menu(cp);
	exit(1);
}
#pragma region Methods
void Menu(CarPark cP) {
	while (1)
	{
		system("cls");
		printf("***************\n");
		printf("* 1-Arac Ekle *\n");
		printf("* 2-Listele   *\n");
		printf("* 3-Cikis     *\n");
		printf("***************\n");
		printf("Toplam Arac Sayisi: %d\n", cP.Used);
		printf("Seciminizi yapiniz [1-3]: ");
		char c[5] = "";
		gets(c);
		system("cls");
		switch (c[0])
		{
		case '1':
			cP = CarAddMenu(cP);
			break;
		case '2':
			ListCar(cP);
			break;
		case '3':
			printf("Iyi gunler\n");
			return;
		}
		system("PAUSE");
	}

}

CarPark CarAddMenu(CarPark cP) {
	char strcount[5];
	int count;
	printf("Kac araba eklemek istiyorsunuz?: ");
	gets(strcount);
	count = atoi(strcount);
	cP = AddCars(cP, count);
	return cP;
}

CarPark AddCar(CarPark cP, Car model) {
	if (cP.Used >= MaximumCapasity)
		printf("Uzgunuz Otopark tamamen dolu\nSon eklediginiz arac sisteme eklenememistir.");
	else
	{
		ParkingRegistration pr;
		pr.car = model;
		pr.time = GetCurrentTime();
		cP.ParkingRegistrations[cP.Used++] = pr;
	}
	return cP;
}

CarPark AddCars(CarPark cP, int count) {
	printf("Otoparkimiza Hosgeldiniz\n____________________________\nEn fazla Renk icin 24 Model icin 24 Plaka icin 11 karakter girisi yapiniz.\n\n");
	int loop = cP.Used + count;
	if (loop == 0) loop = Number_Of_Cars_To_Be_Added_First;
	for (unsigned short i = cP.Used; i < loop; i++)
	{
		Car model;
		printf("\n%d.Arac bilgilerini giriniz:\n____________________________\n", i + 1);
		printf("Araba Renk:");
		gets(model.Color);
		printf("Araba Model:");
		gets(model.Model);
		printf("Araba Plaka:");
		gets(model.Plaque);
		cP = AddCar(cP, model);
	}
	return cP;
}

void ListCar(CarPark carpark) {
	printf("%31s%s\n", "", "Otoparkimiza Hosgeldiniz");
	printf("____________________________________________________________________________\n");
	printf("%-25s %-25s %-12s %s", "RENK", "MODEL", "PLAKA", "GIRIS SAATI\n");
	printf("____________________________________________________________________________\n");
	for (size_t i = 0; i < carpark.Used; i++)
		printf("%-25s %-25s %-12s %d:%d:%d\n",
			carpark.ParkingRegistrations[i].car.Color,
			carpark.ParkingRegistrations[i].car.Model,
			carpark.ParkingRegistrations[i].car.Plaque,
			carpark.ParkingRegistrations[i].time.H,
			carpark.ParkingRegistrations[i].time.M,
			carpark.ParkingRegistrations[i].time.S
		);
}

EntryTime GetCurrentTime() {
	time_t _time = time(NULL);
	struct tm* _tm = localtime(&_time);
	EntryTime Etime;
	Etime.H = _tm->tm_hour;
	Etime.M = _tm->tm_min;
	Etime.S = _tm->tm_sec;
	return Etime;
}
#pragma endregion