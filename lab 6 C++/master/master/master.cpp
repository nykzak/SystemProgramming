#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	char *name="Slave.exe";		//��� SLAVE
	char cmd[256];				//��������� ������ ��� ������� SLAVE
	STARTUPINFO si;				//��������� ��� ������� ��������
	PROCESS_INFORMATION pi;
	DWORD procid;				//�������������� ����� ��������
	setlocale(LC_ALL,"Russian");
	srand(GetTickCount());	//������������� ���������� ��������� �����
	if(argc>2)			//���� �� 0 � �� 1 �������� � ��������� ������
	{
	
		cout << "������ �������:" << endl;	//������� ���������
		cout << "master.exe [���_slave]" << endl;
		cout << "������: master.exe slave.exe" << endl;
		system("pause");
		return -1;
	}
	//�������� ������������� ��������. 
	procid = GetCurrentProcessId();

	if (argc == 2)
	{
		name = argv[1];	//���� � ��������� ������ ������������ ��� SLAVE, �������� ���
		lstrcpy(cmd, name);
		wsprintf(cmd, "%s 5 6 %d", name, procid);		//������������ ��������� ������ ��� ������� �������� SLAVE

	}
	else
	{//���� �������� �� �������
		int m = rand() % 10 + 2;	//�������� � �������� ���������� ��� ��������������� �����
		int n = rand() % 10 + 2;
		wsprintf(cmd, "%s %d %d %d", name,m,n, procid);		//������������ ��������� ������ ��� ������� �������� SLAVE
	}

	cout << "������������� �������� ��������: " << (int)procid << endl;
	cout << "�������� ������� " << cmd << "..." << endl;
	//�������
	memset(&si,0,sizeof(si));
	//� ��������� ����� ��������� si
	si.cb=sizeof(si);
	//�������� ��������
	if(!CreateProcess(NULL,cmd,NULL,NULL,TRUE,CREATE_NEW_CONSOLE|NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi))
	{			//��� ������ ������� ���������
	cout << "�� ������� ��������� ������� " << name << endl;
		system("pause");
		return -1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	cout << "������� " << name << " ��������, ���������� master" << endl;
	system("pause");
	return 0;
}