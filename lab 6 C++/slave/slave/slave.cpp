#include <windows.h>
#include <math.h>
#include <iostream>
#include <iomanip>
using namespace std;
int main(int argc, char *argv[])
{
	int ppid = -1;		//pid �������� MASTER
	setlocale(LC_ALL, "Russian");
	if (argc < 3 || argc>4)			//���� � ��������� ������ �� 3 ��� 4 ���������
	{					//������� ���������
		cout << "������ �������:" << endl;
		cout << "slave.exe m n [ppid]" << endl;
		system("pause");
		return -1;
	}
	int m = atof(argv[1]);
	int n = atof(argv[2]);
	double **A;
	srand(GetTickCount());	//������������� ���������� ��������� �����
	cout << "�������� ������ A" << endl;
	//����� �������
	A = new double*[m];	//�������� ������� A
	for (int i = 0; i < m; i++)
	{
		A[i] = new double[n];	//������� ��������� ������ �������
		for (int j = 0; j < n; j++)						//������������ � ������� ������ �� �����
		{
			A[i][j] = (rand() % 1000) / 10.0;
			cout << setw(5) << A[i][j];			//������� ��������� �������
		}
		cout << endl;
	}
	if (argc == 4)	//���� ���� ������������� ������������� ��������
	{
		ppid = atoi(argv[3]);		//�������� ������������� �������� MASTER �� ��������� ������
		if (!ppid)						//���� 0 ��� ������
		{								//������� ���������
			cout << "������������ �������� ��������������." << endl;
			system("pause");
			return -1;
		}
	}
	if (ppid != -1)	//���� ���� ������������� ������������� ��������
	{
		cout << "��������� �������� ����� Master" << endl;
		cout << "ID master.exe " << ppid << endl;	//������� ������������� �������� MASTER
	}
	else
	{
		cout << "��������� �������� ���� �� ����" << endl;
	}
	for (int i = 0; i < m; i++)
	{
		int fl = 1;
		//���������� ��������� �����
		while (fl)	//���������� ���� ���� ����������
		{
			fl = 0;		//�������� ����

			for (int j = 0; j < n - 1; j++)
			{
				if (A[i][j] < A[i][j + 1])		//���� ��������� ������� ������ ������ ��������� 
				{
					//�������� �� �������
					double tmp = A[i][j];
					A[i][j] = A[i][j + 1];
					A[i][j + 1] = tmp;
					fl = 1;			//���������� ����
				}

			}
		}
	}
	cout << "��������������� ������ A" << endl;
	//����� �������
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)						//������������ � ������� ������ �� �����
		{
			cout << setw(5) << A[i][j];			//������� ��������� �������
		}
		cout << endl;
	}
	system("pause");
	return 0;
}