#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int GetRandom(int, int);
void DiziYazdir(int*, int);
void DiziDoldur(int*);
void DiziAyristir(int*, int*, int*,int*,int*);


int maifn()
{
	srand(time(0));
	int dizi[10], diziTek[10], diziCift[10];
	int* diziPtr, * cDiziPtr, * tDiziPtr;
	diziPtr = dizi;
	cDiziPtr = diziCift;
	tDiziPtr = diziTek;
	int a = 0, b = 0;
	DiziDoldur(diziPtr);
	DiziAyristir(diziPtr, cDiziPtr, tDiziPtr,&a,&b);
	printf("Dizi\n");
	DiziYazdir(diziPtr, 10);
	printf("Ciftler\n");
	DiziYazdir(cDiziPtr, a);
	printf("Tekler\n");
	DiziYazdir(tDiziPtr, b);
	return 0;
}


int GetRandom(int max, int min)
{
	return (rand() % (max + 1) + min);
}

void DiziYazdir(int* dizi, int elemanSayisi)
{
	for (int i = 0; i < elemanSayisi; i++)
		printf("%d\n", *(dizi + i));
}

void DiziDoldur(int * p) {
	for (int i = 0; i < 10; i++)
		*(p + i) = GetRandom(100, 1);
}

void DiziAyristir(int* sayilar, int* ciftsayilar, int* teksayilar,int*a,int *b ) {
	for (int g = 0; g < 10; g++)
	{
		int sayi = *(sayilar + g);
		if (sayi % 2 == 0)
			*(ciftsayilar + (*a)++) = sayi;
		else
			*(teksayilar + (*b)++) = sayi;
	}
}