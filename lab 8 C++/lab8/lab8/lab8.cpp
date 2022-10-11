#include <windows.h>
#include <iostream>
#include <iomanip>
using namespace std;
SYSTEM_INFO mySys;
BYTE* base;		//база выделения памяти
int commited = 0;	//кол-во переданных страниц
DWORD FilterFunction()
{
	VirtualAlloc(base + commited * mySys.dwPageSize, mySys.dwPageSize, MEM_COMMIT, PAGE_READWRITE);
	//увеличиваем кол-во переданных страниц
	commited++;
	cout << "Виртуальная память добавлена" << endl;
	return EXCEPTION_CONTINUE_EXECUTION;	//продолжить выполнение
}
int main()
{
	const wchar_t* typenam = L"Hello world!";
	srand(GetTickCount());		//инициализация генератора случайных чисел
	setlocale(LC_ALL, "Russian");//русская локаль
								 //определяются гранулярность выделения и размер страницы виртуальной памяти;
	GetSystemInfo(&mySys);
	int arrsize = (rand() % 2000 + 1000) & 0xfffffffe;	//Случайный размер массива, четное число

						// Резервируется регион адресного пространства минимально допустимого размера
	base = (BYTE*)VirtualAlloc(NULL, mySys.dwAllocationGranularity, MEM_RESERVE, PAGE_READWRITE);
	//одной странице этого региона передается физическая память
	VirtualAlloc(base + commited * mySys.dwPageSize, mySys.dwPageSize, MEM_COMMIT, PAGE_READWRITE);
	//увеличиваем кол-во переданных страниц
	commited++;
	if (base != NULL)	//если выделение прошло успешно
	{
		cout << "База = " << hex << "0x" << (int)base << endl;
		//отлавливаем исключение 
		__try
		{
			char* pchar = (char*)base;
			const wchar_t* src = typenam;
			char c;
			do
			{
				c = *(src++);
				*(pchar++) = c;
			} while (c);
			cout << "Запись строки закончилась. Указатель = " << hex << "0x" << (int)pchar << endl;
			int* arr = (int*)pchar;
			int* begarr = arr;
			arr += arrsize - 2;
			*(arr++) = arrsize;
			arr++;
			cout << "Массив с мусором создан. Его размер " << dec << *(arr - 2) << ". Указатель = " << hex << "0x" << (int)arr << endl;
			pchar = (char*)arr;
			src = (char*)base;
			cout << "Строка: ";
			do
			{
				c = *(src++);
				*(pchar++) = c;
				cout << c;
			} while (c);
			cout << endl << "Запись строки закончилась. Указатель = " << hex << "0x" << (int)pchar << endl;

			int* q = begarr;
			arr = (int*)pchar;
			for (int i = 0; i < arrsize / 2; i++)
			{
				*(arr++) = *(q++);
			}
			cout << "Запись первой половины массива закончилась. Указатель = " << hex << "0x" << (int)arr << endl;


			pchar = (char*)arr;
			src = (char*)base;
			do
			{
				c = *(src++);
				*(pchar++) = c;

			} while (c);
			cout << "Запись строки закончилась. Указатель = " << hex << "0x" << (int)pchar << endl;
			arr = (int*)pchar;
			for (int i = 0; i < arrsize / 2; i++)
			{
				*(arr++) = *(q++);
			}
			cout << "Запись второй половины массива закончилась. Указатель = " << hex << "0x" << (int)arr << endl;
		}
		//если происходит попытка записи за пределами переданных страниц, происходит исключение
		__except (FilterFunction())	//вызывается функция фильтра, которая добавляет памяти.
		{
		}
		//после окончания записи всех данных, считать все данные из виртуальной памяти с помощью
		//указателей и вывести указанные данные на экран.
		//считать и вывести первую строку
		char* pchar = (char*)base;
		char z;
		do
		{
			z = *(pchar++);
			cout << z;
		} while (z);
		cout << endl;
		//считать массив
		int* arr = (int*)pchar;
		for (int i = 0; i < arrsize; i++)
		{
			int a = *(arr++);
			if (i == arrsize - 2)	//вывести его размер
				cout << dec << a << endl;
		}
		//считать и вывести вторую строку
		pchar = (char*)arr;
		do
		{
			z = *(pchar++);
			cout << z;
		} while (z);
		cout << endl;
		//считать первую половину массива
		arr = (int*)pchar;
		for (int i = 0; i < arrsize / 2; i++)
		{
			int a = *(arr++);
		}
		//считать и вывести третью строку
		pchar = (char*)arr;
		do
		{
			z = *(pchar++);
			cout << z;
		} while (z);
		cout << endl;
		//считать вторую половину массива
		arr = (int*)pchar;
		for (int i = 0; i < arrsize / 2; i++)
		{
			int a = *(arr++);
			if (i == arrsize / 2 - 2)	//в ней есть размер, вывести
				cout << dec << a << endl;
		}

		//освобождение региона
		VirtualFree(base, mySys.dwAllocationGranularity, MEM_DECOMMIT);
	}
	system("pause");
	return 0;
}
