#include <windows.h>
#include <math.h>
#include <iostream>
#include <iomanip>
using namespace std;
int main(int argc, char *argv[])
{
	int ppid = -1;		//pid процесса MASTER
	setlocale(LC_ALL, "Russian");
	if (argc < 3 || argc>4)			//если в командной строке не 3 или 4 параметра
	{					//вывести подсказку
		cout << "Формат команды:" << endl;
		cout << "slave.exe m n [ppid]" << endl;
		system("pause");
		return -1;
	}
	int m = atof(argv[1]);
	int n = atof(argv[2]);
	double **A;
	srand(GetTickCount());	//Инициализация генератора случайных чисел
	cout << "Исходный массив A" << endl;
	//вывод матрицы
	A = new double*[m];	//создание массива A
	for (int i = 0; i < m; i++)
	{
		A[i] = new double[n];	//создать очередную строку матрицы
		for (int j = 0; j < n; j++)						//сформировать и вывести строку на экран
		{
			A[i][j] = (rand() % 1000) / 10.0;
			cout << setw(5) << A[i][j];			//вывести очередной элемент
		}
		cout << endl;
	}
	if (argc == 4)	//если есть идентификатор родительского процесса
	{
		ppid = atoi(argv[3]);		//Подучить ифентификатор процесса MASTER из командной строки
		if (!ppid)						//если 0 или ошибка
		{								//вывести сообщение
			cout << "Недопустимое значение идентификатора." << endl;
			system("pause");
			return -1;
		}
	}
	if (ppid != -1)	//если есть идентификатор родительского процесса
	{
		cout << "Программа запущена через Master" << endl;
		cout << "ID master.exe " << ppid << endl;	//Вывести идентификатор процесса MASTER
	}
	else
	{
		cout << "Программа запущена сама по себе" << endl;
	}
	for (int i = 0; i < m; i++)
	{
		int fl = 1;
		//Сортировка пузырьком строк
		while (fl)	//Продолжать пока флаг установлен
		{
			fl = 0;		//сбросить флаг

			for (int j = 0; j < n - 1; j++)
			{
				if (A[i][j] < A[i][j + 1])		//Если очередной элемент строки меньше следующго 
				{
					//поменять их местами
					double tmp = A[i][j];
					A[i][j] = A[i][j + 1];
					A[i][j + 1] = tmp;
					fl = 1;			//установить флаг
				}

			}
		}
	}
	cout << "Отсортированный массив A" << endl;
	//вывод матрицы
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)						//сформировать и вывести строку на экран
		{
			cout << setw(5) << A[i][j];			//вывести очередной элемент
		}
		cout << endl;
	}
	system("pause");
	return 0;
}