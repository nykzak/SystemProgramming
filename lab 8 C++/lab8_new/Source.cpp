#include <windows.h>
#include <iostream>
#include <iomanip>
using namespace std;
SYSTEM_INFO mySys;
BYTE *base;		//���� ��������� ������
int commited = 0;	//���-�� ���������� �������
DWORD FilterFunction()
{
	VirtualAlloc(base + commited*mySys.dwPageSize, mySys.dwPageSize, MEM_COMMIT, PAGE_READWRITE);
	//����������� ���-�� ���������� �������
	commited++;
	cout << "����������� ������ ���������" << endl;

	return EXCEPTION_CONTINUE_EXECUTION;	//���������� ����������
}
int main()
{
	char *mystr = "Hello world!";
	srand(GetTickCount());		//������������� ���������� ��������� �����
	setlocale(LC_ALL, "Russian");//������� ������
								 //������������ ������������� ��������� � ������ �������� ����������� ������;
	GetSystemInfo(&mySys);
	int arrsize = (rand() % 2000 + 1000) & 0xfffffffe;	//��������� ������ �������, ������ �����

						// ������������� ������ ��������� ������������ ���������� ����������� �������
	base = (BYTE*)VirtualAlloc(NULL, mySys.dwAllocationGranularity, MEM_RESERVE, PAGE_READWRITE);
	//����� �������� ����� ������� ���������� ���������� ������
	VirtualAlloc(base + commited*mySys.dwPageSize, mySys.dwPageSize, MEM_COMMIT, PAGE_READWRITE);
	//����������� ���-�� ���������� �������
	commited++;
	if (base != NULL)	//���� ��������� ������ �������
	{
		cout << "���� = " << hex << "0x" << (int)base << endl;
		//����������� ���������� 
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
			cout << "������ ������ �����������. ��������� = " << hex << "0x" << (int)pchar << endl;
			int *arr = (int*)pchar;
			int *begarr = arr;
			arr += arrsize - 2;
			*(arr++) = arrsize;
			arr++;
			cout << "������ � ������� ������. ��� ������ " << dec << *(arr - 2) << ". ��������� = " << hex << "0x" << (int)arr << endl;
			pchar = (char*)arr;
			src = (char*)base;
			cout << "������: ";
			do
			{
				c = *(src++);
				*(pchar++) = c;
				cout << c;
			} while (c);
			cout << endl << "������ ������ �����������. ��������� = " << hex << "0x" << (int)pchar << endl;

			int *q = begarr;
			arr = (int*)pchar;
			for (int i = 0; i < arrsize / 2; i++)
			{
				*(arr++) = *(q++);
			}
			cout << "������ ������ �������� ������� �����������. ��������� = " << hex << "0x" << (int)arr << endl;


			pchar = (char*)arr;
			src = (char*)base;
			do
			{
				c = *(src++);
				*(pchar++) = c;

			} while (c);
			cout << "������ ������ �����������. ��������� = " << hex << "0x" << (int)pchar << endl;
			arr = (int*)pchar;
			for (int i = 0; i < arrsize / 2; i++)
			{
				*(arr++) = *(q++);
			}
			cout << "������ ������ �������� ������� �����������. ��������� = " << hex << "0x" << (int)arr << endl;
		}
		//���� ���������� ������� ������ �� ��������� ���������� �������, ���������� ����������
		__except (FilterFunction())	//���������� ������� �������, ������� ��������� ������.
		{
		}
		//����� ��������� ������ ���� ������, ������� ��� ������ �� ����������� ������ � �������
		//���������� � ������� ��������� ������ �� �����.
		//������� � ������� ������ ������
		char *pchar = (char*)base;
		char z;
		do
		{
			z = *(pchar++);
			cout << z;
		} while (z);
		cout << endl;
		//������� ������
		int *arr = (int*)pchar;
		for (int i = 0; i < arrsize; i++)
		{
			int a = *(arr++);
			if (i == arrsize - 2)	//������� ��� ������
				cout << dec << a << endl;
		}
		//������� � ������� ������ ������
		pchar = (char*)arr;
		do
		{
			z = *(pchar++);
			cout << z;
		} while (z);
		cout << endl;
		//������� ������ �������� �������
		arr = (int*)pchar;
		for (int i = 0; i < arrsize/2; i++)
		{
			int a = *(arr++);
		}
		//������� � ������� ������ ������
		pchar = (char*)arr;
		do
		{
			z = *(pchar++);
			cout << z;
		} while (z);
		cout << endl;
		//������� ������ �������� �������
		arr = (int*)pchar;
		for (int i = 0; i < arrsize / 2; i++)
		{
			int a = *(arr++);
			if (i == arrsize/2 - 2)	//� ��� ���� ������, �������
				cout << dec << a << endl;
		}

		//������������ �������
		VirtualFree(base, mySys.dwAllocationGranularity, MEM_DECOMMIT);
	}
	system("pause");
	return 0;
}