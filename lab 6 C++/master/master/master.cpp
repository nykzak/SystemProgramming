#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
using namespace std;
int main(int argc,char *argv[])
{
	char *name="Slave.exe";		//Имя SLAVE
	char cmd[256];				//Командная строка для запуска SLAVE
	STARTUPINFO si;				//Структузы для запуска процесса
	PROCESS_INFORMATION pi;
	DWORD procid;				//Идентификактор этого процесса
	setlocale(LC_ALL,"Russian");
	srand(GetTickCount());	//Инициализация генератора случайных чисел
	if(argc>2)			//Если не 0 и не 1 параметр в командной строке
	{
	
		cout << "Формат команды:" << endl;	//вывести подсказку
		cout << "master.exe [имя_slave]" << endl;
		cout << "Пример: master.exe slave.exe" << endl;
		system("pause");
		return -1;
	}
	//Получить идентификатор процесса. 
	procid = GetCurrentProcessId();

	if (argc == 2)
	{
		name = argv[1];	//Если в командной строке присутствует имя SLAVE, заменить его
		lstrcpy(cmd, name);
		wsprintf(cmd, "%s 5 6 %d", name, procid);		//Сформировать командную строку для запуска процесса SLAVE

	}
	else
	{//Если параметр не передан
		int m = rand() % 10 + 2;	//Передать в качестве параметров два сгенерированных числа
		int n = rand() % 10 + 2;
		wsprintf(cmd, "%s %d %d %d", name,m,n, procid);		//Сформировать командную строку для запуска процесса SLAVE
	}

	cout << "Идентификатор текущего процесса: " << (int)procid << endl;
	cout << "Запускаю процесс " << cmd << "..." << endl;
	//очистка
	memset(&si,0,sizeof(si));
	//и заполение полей структуры si
	si.cb=sizeof(si);
	//Создание процесса
	if(!CreateProcess(NULL,cmd,NULL,NULL,TRUE,CREATE_NEW_CONSOLE|NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi))
	{			//при ошибке вывести сообщение
	cout << "Не удается запустить процесс " << name << endl;
		system("pause");
		return -1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	cout << "Процесс " << name << " завершен, завершение master" << endl;
	system("pause");
	return 0;
}