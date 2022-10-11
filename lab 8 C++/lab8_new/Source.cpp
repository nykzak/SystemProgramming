#include <windows.h>
#include <iostream>
#include <iomanip>
using namespace std;
SYSTEM_INFO mySys;
BYTE *base;		//база выделени€ пам€ти
int commited = 0;	//кол-во переданных страниц
DWORD FilterFunction()
{
	VirtualAlloc(base + commited*mySys.dwPageSize, mySys.dwPageSize, MEM_COMMIT, PAGE_READWRITE);
	//увеличиваем кол-во переданных страниц
	commited++;
	cout << "¬иртуальна€ пам€ть добавлена" << endl;

	return EXCEPTION_CONTINUE_EXECUTION;	//продолжить выполнение
}
int main()
{
	char *mystr = "Hello world!";
	srand(GetTickCount());		//инициализаци€ генератора случайных чисел
	setlocale(LC_ALL, "Russian");//русска€ локаль
								 //определ€ютс€ гранул€рность выделени€ и размер страницы виртуальной пам€ти;
	GetSystemInfo(&mySys);
	int arrsize = (rand() % 2000 + 1000) & 0xfffffffe;	//—лучайный размер массива, четное число

						// –езервируетс€ регион адресного пространства минимально допустимого размера
	base = (BYTE*)VirtualAlloc(NULL, mySys.dwAllocationGranularity, MEM_RESERVE, PAGE_READWRITE);
	//одной странице этого региона передаетс€ физическа€ пам€ть
	VirtualAlloc(base + commited*mySys.dwPageSize, mySys.dwPageSize, MEM_COMMIT, PAGE_READWRITE);
	//увеличиваем кол-во переданных страниц
	commited++;
	if (base != NULL)	//если выделение прошло успешно
	{
		cout << "Ѕаза = " << hex << "0x" << (int)base << endl;
		//отлавливаем исключение 
		__try
		{
			char *pchar = (char*)base;
			char *src = mystr;
			char c;
			do
			{
				c = *(src++);
				*(pchar++) = c;
			} while (c);
			cout << "«апись строки закончилась. ”казатель = " << hex << "0x" << (int)pchar << endl;
			int *arr = (int*)pchar;
			int *begarr = arr;
			arr += arrsize - 2;
			*(arr++) = arrsize;
			arr++;
			cout << "ћассив с мусором создан. ≈го размер " << dec << *(arr - 2) << ". ”казатель = " << hex << "0x" << (int)arr << endl;
			pchar = (char*)arr;
			src = (char*)base;
			cout << "—трока: ";
			do
			{
				c = *(src++);
				*(pchar++) = c;
				cout << c;
			} while (c);
			cout << endl << "«апись строки закончилась. ”казатель = " << hex << "0x" << (int)pchar << endl;

			int *q = begarr;
			arr = (int*)pchar;
			for (int i = 0; i < arrsize / 2; i++)
			{
				*(arr++) = *(q++);
			}
			cout << "«апись первой половины массива закончилась. ”казатель = " << hex << "0x" << (int)arr << endl;


			pchar = (char*)arr;
			src = (char*)base;
			do
			{
				c = *(src++);
				*(pchar++) = c;

			} while (c);
			cout << "«апись строки закончилась. ”казатель = " << hex << "0x" << (int)pchar << endl;
			arr = (int*)pchar;
			for (int i = 0; i < arrsize / 2; i++)
			{
				*(arr++) = *(q++);
			}
			cout << "«апись второй половины массива закончилась. ”казатель = " << hex << "0x" << (int)arr << endl;
		}
		//если происходит попытка записи за пределами переданных страниц, происходит исключение
		__except (FilterFunction())	//вызываетс€ функци€ фильтра, котора€ добавл€ет пам€ти.
		{
		}
		//после окончани€ записи всех данных, считать все данные из виртуальной пам€ти с помощью
		//указателей и вывести указанные данные на экран.
		//считать и вывести первую строку
		char *pchar = (char*)base;
		char z;
		do
		{
			z = *(pchar++);
			cout << z;
		} while (z);
		cout << endl;
		//считать массив
		int *arr = (int*)pchar;
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
		for (int i = 0; i < arrsize/2; i++)
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
			if (i == arrsize/2 - 2)	//в ней есть размер, вывести
				cout << dec << a << endl;
		}

		//освобождение региона
		VirtualFree(base, mySys.dwAllocationGranularity, MEM_DECOMMIT);
	}
	system("pause");
	return 0;
}
