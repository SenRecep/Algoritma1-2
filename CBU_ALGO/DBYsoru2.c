#define _CRT_SECURE_NO_WARNINGS
#define StringLenght_1 25
#define StringLenght_2 12
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma region Types

typedef struct {
	char* Plaque;
	char* Model;
	char* Color;
}Car;
typedef struct {
	unsigned short H;
	unsigned short M;
	unsigned short S;
}EntryTime;
typedef struct {
	Car* cars;
	EntryTime* times;
	size_t	Capacity;
	size_t Used;
	size_t UsableCapacity;
}ParkingRegistration;

#pragma endregion
#pragma region Headers
void Menu(ParkingRegistration*, Car*);
void CarAddMenu(ParkingRegistration* pR, Car* model);
void InitializingCarPark(ParkingRegistration*, int, int);
void InitializingCar(Car*);
char* AddCar(ParkingRegistration*);
void AddCars(ParkingRegistration*, Car*, int*);
void ListCar(ParkingRegistration*);
EntryTime GetCurrentTime();
void Free(ParkingRegistration*, Car*);
void FreeCar(Car*);
#pragma endregion
void main() {
#pragma region Fields
	Car model;
	Car* ptrmodel = &model;
	ParkingRegistration pR;
	ParkingRegistration* ptrPR = &pR;
#pragma endregion
	InitializingCarPark(ptrPR, 5, 1000);
	InitializingCar(ptrmodel);
	Menu(ptrPR, ptrmodel);
	Free(ptrPR, ptrmodel);
	exit(1);
}
#pragma region Methods
void Menu(ParkingRegistration* pR, Car* model) {
	while (1)
	{
		system("cls");
		printf("***************\n");
		printf("* 1-Arac Ekle *\n");
		printf("* 2-Listele   *\n");
		printf("* 3-Cikis     *\n");
		printf("***************\n");
		printf("Seciminizi yapiniz [1-3]:");
		char c[5] = "";
		gets(c);
		system("cls");
		switch (c[0])
		{
		case '1':
			CarAddMenu(pR, model);
			break;
		case '2':
			ListCar(pR);
			break;
		case '3':
			printf("Iyi gunler\n");
			return;
		}
		system("PAUSE");
	}

}

void CarAddMenu(ParkingRegistration* pR, Car* model) {
	char strcount[5];
	int count;
	printf("Kac araba eklemek istiyorsunuz?: ");
	gets(strcount);
	count = atoi(strcount);
	AddCars(pR, model, &count);
}

void InitializingCarPark(ParkingRegistration* pR, int usableCapacity, int Capacity) {
	pR->Capacity = Capacity;
	pR->Used = 0;
	pR->UsableCapacity = usableCapacity;
	pR->cars = (Car*)malloc(usableCapacity * sizeof(Car));
	pR->times = (EntryTime*)malloc(usableCapacity * sizeof(EntryTime));
}

char* AddCar(ParkingRegistration* pR, Car* car) {
	Car model; InitializingCar(&model);
	strcpy(model.Color, car->Color); strcpy(model.Plaque, car->Plaque); strcpy(model.Model, car->Model);
	if (pR->Used >= pR->Capacity)
		return "Uzgunuz Otopark tamamen dolu\n";
	if (pR->Used == pR->UsableCapacity)
	{
		pR->cars = (Car*)realloc(pR->cars, (++pR->UsableCapacity) * sizeof(Car));
		pR->times = (EntryTime*)realloc(pR->times, (pR->UsableCapacity) * sizeof(EntryTime));
	}
	pR->times[pR->Used] = GetCurrentTime();
	pR->cars[pR->Used++] = model;
	return "";
}

void AddCars(ParkingRegistration* pR, Car* model, int* count) {
	printf("Otoparkimiza Hosgeldiniz\n____________________________\nEn fazla Renk icin 24 Model icin 24 Plaka icin 11 karakter girisi yapiniz.\n\n");
	int loop = pR->Used + (*count);
	for (unsigned short i = pR->Used; i < loop; i++)
	{
		printf("\n%d.Arac bilgilerini giriniz:\n____________________________\n", i + 1);
		printf("Araba Renk:");
		gets_s(model->Color, StringLenght_1);
		printf("Araba Model:");
		gets_s(model->Model, StringLenght_1);
		printf("Araba Plaka:");
		gets_s(model->Plaque, StringLenght_2);
		char* res = AddCar(pR, model);
		if (strlen(res) > 0) {
			printf("\n%sSon eklediginiz arac sisteme eklenememistir.\n", res);
			break;
		}
	}
}

void InitializingCar(Car* model) {
	model->Color = (char*)malloc(sizeof(char) * StringLenght_1);
	model->Model = (char*)malloc(sizeof(char) * StringLenght_1);
	model->Plaque = (char*)malloc(sizeof(char) * StringLenght_2);
}

void ListCar(ParkingRegistration* pR) {
	printf("%31s%s\n", "", "Otoparkimiza Hosgeldiniz");
	printf("____________________________________________________________________________\n");
	printf("%-25s %-25s %-12s %s", "RENK", "MODEL", "PLAKA", "GIRIS SAATI\n");
	printf("____________________________________________________________________________\n");
	for (size_t i = 0; i < pR->Used; i++)
		printf("%-25s %-25s %-12s %d:%d:%d\n",
			pR->cars[i].Color,
			pR->cars[i].Model,
			pR->cars[i].Plaque,
			pR->times[i].H,
			pR->times[i].M,
			pR->times[i].S
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

void FreeCar(Car* car) {
	free(car->Color);
	free(car->Model);
	free(car->Plaque);
}

void Free(ParkingRegistration* model, Car* car) {
	FreeCar(car);
	free(model->cars);
	free(model->times);
	model->Capacity = model->UsableCapacity = model->Used = 0;
	model->cars = model->times = NULL;
}
#pragma endregion