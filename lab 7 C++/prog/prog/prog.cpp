#include <iostream>
#include <Windows.h>
using namespace std;
int* a, n;
double avg;
DWORD WINAPI worker(PVOID)
{
	int sum = 0;
	//найти среднее значение элементов массива
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
		Sleep(12);	//после каждого суммирования элементов "спать" 12 мсек.
	}
	avg = (double)sum / (double)n;
	cout << endl;
	//cout << "Произошёл рассинхрон , поток worker закончил свою подсчёты после комментария об завершение программы :" << endl;
	cout << "Среднее арифметическое массива = " << avg << endl;
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
	cout << endl;
	DWORD idThread; // Для CreateThread
	//Создать и запустить поток worker
	HANDLE hworker = CreateThread(NULL, 0, worker, NULL, 0, &idThread);
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
	cout << endl;
	//WaitForSingleObject(hworker, INFINITE);
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