#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NumberCount 10

#pragma region Types
typedef struct {
	int* array;
	size_t Used;
	size_t Size;
} Array;

typedef enum {
	ODD,
	EVEN
}OE;
#pragma endregion

#pragma region Headers
void InitializingArray(Array*, size_t);
void AddArray(Array*, int);
int GetElementByIndex(Array*, int);
void FreeArray(Array*);
void PrintArray(Array*);

int RandomNumber(int, int);
void NumberFill(Array*);

OE ODDorEVEN(int);

void PrintResult(Array*, Array*, Array*);
void DistributingNumbers(Array*, Array*, Array*);
void FREE(Array*, Array*, Array*);

#pragma endregion

void main()
{
	srand(time(NULL));
	Array Numbers, OddNumbers, EvenNumbers;
	Array* ptrNumbers = &Numbers,
		* ptrOddNumbers = &OddNumbers,
		* ptrEvenNumbers = &EvenNumbers;
	InitializingArray(ptrNumbers, NumberCount);
	InitializingArray(ptrOddNumbers, NumberCount / 5);
	InitializingArray(ptrEvenNumbers, NumberCount / 5);
	NumberFill(ptrNumbers);
	DistributingNumbers(ptrNumbers, ptrOddNumbers, ptrEvenNumbers);
	PrintResult(ptrNumbers, ptrOddNumbers, ptrEvenNumbers);
	FREE(ptrNumbers, ptrOddNumbers, ptrEvenNumbers);
	system("PAUSE");
}

#pragma region Methods
void PrintResult(Array* numbers, Array* odd, Array* even) {
	printf("Tum Sayilar\n_____________\n\n");
	PrintArray(numbers);
	printf("\nTek Sayilar\n_____________\n\n");
	PrintArray(odd);
	printf("\nCift Sayilar\n_____________\n\n");
	PrintArray(even);
}

void DistributingNumbers(Array* numbers, Array* odd, Array* even) {
	for (unsigned short i = 0; i < numbers->Size; i++) {
		int item = GetElementByIndex(numbers, i);
		if (ODDorEVEN(item) == ODD)
			AddArray(odd, item);
		else
			AddArray(even, item);
	}
}

void FREE(Array* ary1, Array* ary2, Array* ary3) {
	FreeArray(ary1);
	FreeArray(ary2);
	FreeArray(ary3);
}

void InitializingArray(Array* array, size_t Size) {
	array->array = (int*)malloc(Size * sizeof(int));
	array->Used = 0;
	array->Size = Size;
}

void AddArray(Array* array, int num) {
	if (array->Used == array->Size) {
		array->Size++;
		array->array = (int*)realloc(array->array, array->Size * sizeof(int));
	}
	array->array[array->Used++] = num;
}

int GetElementByIndex(Array* array, int index) {
	return *(array->array + index % array->Size);
}

void FreeArray(Array* array) {
	free(array->array);
	array->array = NULL;
	array->Used = array->Size = 0;
}

OE ODDorEVEN(int num) {
	return num % 2 == 0 ? EVEN : ODD;
}

void PrintArray(Array* array) {
	for (unsigned short i = 0; i < array->Size; i++)
		printf("%d\n", *(array->array + i));

}

void NumberFill(Array* array) {
	for (unsigned short i = 0; i < array->Size; i++)
		AddArray(array, RandomNumber(1, 101));

}

int RandomNumber(int min, int max) {
	max -= min;
	return (rand() % max) + min;
}
#pragma endregion
