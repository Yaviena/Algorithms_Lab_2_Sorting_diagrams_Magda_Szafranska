// Autor: Magda Szafranska, nr indeksu AHNS: 18345
// Informatyka NST, rok 2, sem. 3
// Algorytmy, laboratoria nr 2

using namespace std;

//---------------------------------------------------------------------------
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <random>
#include <fstream>

//---------------------------------------------------------------------------
int MIN(int A, int B)
{
	return A < B ? A : B;
}
//---------------------------------------------------------------------------
void SWAP(int& A, int& B)
{
	int T = A;
	A = B;
	B = T;
}
//---------------------------------------------------------------------------
void RandomTab(int N, int* T)
{
	srand(0);
	for (int i = 0; i < N; ++i) T[i] = rand() % N;
}
//---------------------------------------------------------------------------
void WriteTab(int N, int* T)
{
	printf("%i", T[0]);
	for (int i = 1; i < N; ++i) printf(", %i", T[i]);
	printf("\n");
}
//---------------------------------------------------------------------------
int MaxOfTab(int N, int* T)
{
	int M = T[0];
	for (int i = 1; i < N; ++i) if (M < T[i]) M = T[i];
	return M;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void BubbleSort(int N, int* T)
{
	bool Changed;
	do {
		Changed = false;
		for (int i = N - 2; i >= 0; --i)
			if (T[i] > T[i + 1]) {
				SWAP(T[i], T[i + 1]);
				Changed = true;
			}
	} while (Changed);
}
//---------------------------------------------------------------------------
void InsertionSort(int N, int* T)
{
	for (int i = 1; i < N; ++i) {
		int j = i;
		int V = T[i];
		while ((T[j - 1] > V) && (j > 0)) T[j--] = T[j - 1];
		T[j] = V;
	}
}
//---------------------------------------------------------------------------
void SelectionSort(int N, int* T)
{
	for (int i = 0; i < N - 1; ++i) {
		int m = i;
		for (int j = i + 1; j < N; ++j) if (T[j] < T[m]) m = j;
		SWAP(T[m], T[i]);
	}
}
//---------------------------------------------------------------------------
void QS(int I1, int I2, int* T)
{
	int i = I1;
	int j = I2;
	int V = T[(I1 + I2) / 2];
	do
	{
		while (T[i] < V) i++;
		while (V < T[j]) j--;
		if (i <= j) SWAP(T[i++], T[j--]);
	} while (i <= j);
	if (I1 < j) QS(I1, j, T);
	if (i < I2) QS(i, I2, T);
}

void QuickSort(int N, int* T)
{
	QS(0, N - 1, T);
}
//---------------------------------------------------------------------------
void CountingSort(int N, int* T)
{
	int M = MaxOfTab(N, T);

	int* P = new int[M];
	for (int i = 0; i < M; ++i) P[i] = 0;
	for (int i = 0; i < N; ++i) ++P[T[i]];
	for (int i = 0, j = 0; (i < N) && (j < M);)
		if (P[j] > 0) {
			T[i++] = j;
			P[j]--;
		}
		else j++;
	delete[] P;
}
//---------------------------------------------------------------------------
void MM(int I1, int K, int I2, int* T, int* P)
{
	for (int i = I1; i <= I2; ++i) P[i] = T[i];
	int i = I1;
	int j = K + 1;
	int q = I1;
	while ((i <= K) && (j <= I2)) {
		if (P[i] < P[j]) T[q++] = P[i++];
		else T[q++] = P[j++];
	}
	while (i <= K) T[q++] = P[i++];
}

void MS(int I1, int I2, int* T, int* P)
{
	if (I1 < I2) {
		int k = (I1 + I2) / 2;
		MS(I1, k, T, P);
		MS(k + 1, I2, T, P);
		MM(I1, k, I2, T, P);
	}
}

void MergeSort(int N, int* T)
{
	int* P = new int[N];
	MS(0, N - 1, T, P);
	delete[] P;
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	printf("<<< Test algorytmów sortowania tablcy liczb ca³kowitych >>>\n");
	if (argc != 2) {
		printf("Schemat wywo³ania programu: sort tab_size\n");
		printf("  tab_size - rozmiar tablicy\n");
		return 0;
	}

	int N = atoi(argv[1]);
	printf("N = %i\n", N);
	if (N <= 0) {
		printf("Nieprawid³owy rozmiar tablicy!\n");
		return 0;
	}

	// writing to the text file - a separate file to each of an algorithm
	fstream fileN1, fileN2, fileBubble, fileSelection, fileInsertion, fileMerge, fileQuick, fileCounting;
	fileN1.open("N1.txt", ios::out | ios::app);
	fileN2.open("N2.txt", ios::out | ios::app);
	fileBubble.open("BubbleSort.txt", ios::out | ios::app);
	fileSelection.open("SelectionSort.txt", ios::out | ios::app);
	fileInsertion.open("InsertionSort.txt", ios::out | ios::app);
	fileMerge.open("MergeSort.txt", ios::out | ios::app);
	fileQuick.open("QuickSort.txt", ios::out | ios::app);
	fileCounting.open("CountingSort.txt", ios::out | ios::app);

	int* T = new int[N];

	RandomTab(N, T);
	printf("T = "); WriteTab(MIN(N, 30), T);
	fileN1 << N << endl;
	fileN2 << N << endl;

	__int64 T1, T2, F;
	QueryPerformanceFrequency((LARGE_INTEGER*)&F);

	printf("Sortowanie b¹belkowe (ang. bubble sort)...", N);
	RandomTab(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T1);
	BubbleSort(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T2);
	printf("\t\tCzas [s] = %G\n", (T2 - T1) / (float)F);
	fileBubble << (T2 - T1) / (float)F << endl;

	printf("Sortowanie przez wybór (ang. selection sort)...", N);
	RandomTab(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T1);
	SelectionSort(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T2);
	printf("\t\tCzas [s] = %G\n", (T2 - T1) / (float)F);
	fileSelection << (T2 - T1) / (float)F << endl;

	printf("Sortowanie przez wstawianie (ang.insertion sort)...", N);
	RandomTab(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T1);
	InsertionSort(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T2);
	printf("\tCzas [s] = %G\n", (T2 - T1) / (float)F);
	fileInsertion << (T2 - T1) / (float)F << endl;

	printf("Sortowanie przez scalanie (ang. merge sort)...", N);
	RandomTab(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T1);
	MergeSort(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T2);
	printf("\t\tCzas [s] = %G\n", (T2 - T1) / (float)F);
	fileMerge << (T2 - T1) / (float)F << endl;

	printf("Sortowanie szybkie (ang. quick sort)...", N);
	RandomTab(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T1);
	QuickSort(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T2);
	printf("\t\t\tCzas [s] = %G\n", (T2 - T1) / (float)F);
	fileQuick << (T2 - T1) / (float)F << endl;

	printf("Sortowanie przez zliczanie (ang. counting sort)...", N);
	RandomTab(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T1);
	CountingSort(N, T);
	QueryPerformanceCounter((LARGE_INTEGER*)&T2);
	printf("\tCzas [s] = %G\n", (T2 - T1) / (float)F);
	fileCounting << (T2 - T1) / (float)F << endl;

	printf("T = "); WriteTab(MIN(N, 30), T);

    fileN1.close();
    fileN2.close();
    fileBubble.close();
    fileSelection.close();
    fileInsertion.close();
    fileMerge.close();
    fileQuick.close();
    fileCounting.close();

	delete[] T;
	return 0;
}
//---------------------------------------------------------------------------
