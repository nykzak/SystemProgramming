#include <iostream>
#include <Windows.h>
using namespace std;
int* a, n;
double avg;
CRITICAL_SECTION cs;	//для синхронизации доступа к массиву
DWORD WINAPI worker(PVOID)
{
	int sum = 0;
	EnterCriticalSection(&cs);	//зайти в критическую секцию
	//найти максимальное значение
	int max = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] > max)
			max = a[i];
	}
	cout << "Максимальное значение: " << max << endl;
	int nn = 0;	//количество просуммированных элементов
	//найти среднее значение элементов массива
	for (int i = 0; i < n; i++)
	{
		if (a[i] != max)	//исключаем максимальный элемент
		{
			sum += a[i];
			Sleep(12);	//после каждого суммирования элементов "спать" 12 мсек.
			nn++;
		}
	}
	LeaveCriticalSection(&cs);	//покинуть критическую секцию
	avg = (double)sum / (double)nn;
	cout << "Среднее арифметическое массива без максимального = " << avg << endl;
	return 0;
	
}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите размер массива: ";
	cin >> n;
	srand(GetTickCount());	//инициализация генератора случайных чисел
							//создать массив целых чисел, размерность вводит пользователь
	a = new int[n];
	cout << "Массив:" << endl;
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 100;	//Значения элементов генерируются случайным образом
		cout << a[i] << " ";	//и вывести массив
	}
	InitializeCriticalSection(&cs);	//создать критическую секцию

	cout << endl;
	DWORD idThread; // Для CreateThread
					//Создать и запустить поток worker
	HANDLE hworker = CreateThread(NULL, 0, worker, NULL, 0, &idThread);
	EnterCriticalSection(&cs);	//зайти в критическую секцию
	//Отсорировать массив "пузырьком"
	bool fl = true;		//устанавливаем флаг перестановок
	while (fl)		//пока были перестановки, продолжаем                       
	{
		fl = false;								//сбрасываем признак перестановки
		for (int i = 0; i < n - 1; i++)		//цикл по массиву
		{
			if (a[i] > a[i + 1])	//сравнение соседних элементов
			{			//если они не упорядочены по возрастанию
				fl = true;		//то установить признак перестановки
				int t = a[i];
				a[i] = a[i + 1];		//обменять их местами
				a[i + 1] = t;
			}

		}
	}
	//и вывести содержимое массива на экран
	cout << "Отсортированный массив:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	LeaveCriticalSection(&cs);	//покинуть критическую секцию
	cout << endl;
	//Дождаться завершения потока worker
	WaitForSingleObject(hworker, INFINITE);
	DeleteCriticalSection(&cs);	//удалить критическую секцию, после завершения worker она не нужна
	//Подстчитать количество элементов в массиве, значение которых больше среднего значения элементов массива
	//и вывести его на консоль
	int nb = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] > avg)
			nb++;
	}
	cout << "Количество элементов в массиве, значение которых больше среднего значения элементов массива: " << nb << endl;

	system("pause");
	return 0;
}