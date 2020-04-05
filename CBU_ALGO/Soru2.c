#define _CRT_SECURE_NO_WARNINGS
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
void InitializingCarPark(ParkingRegistration*, int, int);
char* AddCar(ParkingRegistration*);
void AddCars(ParkingRegistration*, Car*);
void InitializingCar(Car*);
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
	AddCars(ptrPR, ptrmodel);
	ListCar(ptrPR);
	Free(ptrPR, ptrmodel);
	system("PAUSE");
	exit(1);
}
#pragma region Methods
void InitializingCarPark(ParkingRegistration* pR, int usableCapacity, int Capacity) {
	pR->Capacity = Capacity;
	pR->Used = 0;
	pR->UsableCapacity = usableCapacity;
	pR->cars = (Car*)malloc(usableCapacity * sizeof(Car));
	pR->times = (EntryTime*)malloc(usableCapacity * sizeof(EntryTime));
}

char* AddCar(ParkingRegistration* pR, Car* car) {
	Car model;
	InitializingCar(&model);
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

void AddCars(ParkingRegistration* pR, Car* model) {
	printf("Otoparkimiza Hosgeldiniz\n________________________\n");
	for (unsigned short i = 0; i < pR->UsableCapacity; i++)
	{
		printf("%d.Arac bilgilerini giriniz:\n____________________________\n", i + 1);
		printf("Araba Renk:");
		scanf("%s", model->Color);
		printf("Araba Model:");
		scanf("%s", model->Model);
		printf("Araba Plaka:");
		scanf("%s", model->Plaque);
		char* res = AddCar(pR, model);
		if (strlen(res) > 0) {
			printf("%s\n", res);
			break;
		}
	}
}

void InitializingCar(Car* model) {
	model->Color = (char*)malloc(sizeof(char) * 25);
	model->Model = (char*)malloc(sizeof(char) * 25);
	model->Plaque = (char*)malloc(sizeof(char) * 12);

}

void ListCar(ParkingRegistration* pR) {
	system("cls");
	printf("%30s%s\n", "", "Otoparkimiza Hosgeldiniz");
	printf("____________________________________________________________________________\n");
	printf("%-25s %-25s %-12s %s", "RENK", "MODEL", "PLAKA", "GIRIS SAATI\n");
	printf("____________________________________________________________________________\n");
	for (size_t i = 0; i < pR->Used; i++)
	{
		printf("%-25s %-25s %-12s %d:%d:%d\n",
			pR->cars[i].Color,
			pR->cars[i].Model,
			pR->cars[i].Plaque,
			pR->times[i].H,
			pR->times[i].M,
			pR->times[i].S
		);
	}
}

EntryTime GetCurrentTime() {
	time_t theTime = time(NULL);
	struct tm* aTime = localtime(&theTime);
	EntryTime Etime;
	Etime.H = aTime->tm_hour;
	Etime.M = aTime->tm_min;
	Etime.S = aTime->tm_sec;
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