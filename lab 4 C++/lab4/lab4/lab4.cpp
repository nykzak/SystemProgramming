//10. Реализовать программно поиск первых 10 файлов с расширением *.doc в каталоге с:\ My Documents и во всех его подкаталогах. Создать в с:\ My Documents файл doc.dat. Записать в данный файл короткие имена всех найденных файлов и даты их последней модификации. Вывести содержания файла.

#include <iostream>
#include <windows.h>
using namespace std;
HANDLE hfile;	//doc.dat
int numf = 0;	//кол-во найденных файлов

//Рекурсивный поиск начиная с path
void SearchRec(char* path)
{
	WIN32_FIND_DATA fd;
	SYSTEMTIME time;
	DWORD wr;
	char tmp[512];
	char* pLast;		//указатель на конец пути
	HANDLE hFind;
	if (path[lstrlen(path) - 1] != L'\\')	//добавить в конец обратный слеш если нет
		lstrcat(path, "\\");
	pLast = path + lstrlen(path);			//указатель на конец пути
	//поиск в поддиректориях
	if (numf < 10)			//если нашли менее 10 файлов
	{
		lstrcat(path, "*.*");				//добавить к пути *.*
		hFind = FindFirstFile(path, &fd);	//поиск первого файла
		if (hFind != INVALID_HANDLE_VALUE)	//если найден
		{
			do
			{
				*pLast = '\0';				//очистить хвост пути
				if (fd.cFileName[0] == '.')	//если это перехо к наддиректории, то пропустить
					continue;
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)	//Есди это поддиректория
				{
					lstrcat(path, fd.cFileName);	//то добавить ее к пути
					SearchRec(path);				//и рекурсивно зайти в нее
				}
			} while (FindNextFile(hFind, &fd));		//Продолжить поиск
			FindClose(hFind);							//закрыть поиск
		}
		*pLast = '\0';								//очистить хвост пути
	}

	lstrcat(path, "*.doc");							//добавить к пути *.doc
	hFind = FindFirstFile(path, &fd);				//поиск первого файла
	if (hFind != INVALID_HANDLE_VALUE)
	{				//если найден
		do
		{
			*pLast = '\0';							//очистить хвост пути
			if (fd.cFileName[0] == '.')				//если это переход к наддиректории, то пропустить
				continue;
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)	//Если это файл
			{
				lstrcat(path, fd.cFileName);		//то добавить его к пути
				if (numf < 10)	//если нашли менее 10 файлов
				{
					FileTimeToSystemTime(&fd.ftLastWriteTime, &time);	//преобразовать зату последней модификации
					char* shortname;
					if (fd.cAlternateFileName[0])	//если короткое имя не пустое
						shortname = fd.cAlternateFileName;	//то выводить его
					else
						shortname = fd.cFileName;	//если пустое, то выводить обычное имя, оно не больше 8.3
					wsprintf(tmp, "%s - %02d.%02d.%04d\r\n", shortname, time.wDay, time.wMonth, time.wYear);	//сформировать строку с коротким именем и датой последней модификции
					WriteFile(hfile, tmp, lstrlen(tmp), &wr, NULL);	//записать ее в файл
					numf++;	//увеличить кол-во найденных файлов
				}
			}
		} while (FindNextFile(hFind, &fd));				//Продолжить поиск
		FindClose(hFind);								//закрыть поиск
	}
	*pLast = '\0';										//очистить хвост пути
}


int main()
{
	WIN32_FIND_DATA fd;
	DWORD rd;
	char path[MAX_PATH];
	setlocale(LC_ALL, "Russian");//русская локаль
	cout << "Лабораторная No4 - Сергей Павлов 70982 \n" << endl;
	HANDLE hFind = FindFirstFile("C:\\Users\\nykza\\Documents", &fd);	//поиск папки
	//если она не найдна или это не папка
	if (hFind == INVALID_HANDLE_VALUE || (hFind != INVALID_HANDLE_VALUE && (fd.dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY == 0)))
	{
		cout << "Папка C:\\Users\\nykza\\Documents не обнаружена" << endl;
		system("pause");
		return 0;
	}
	//создание выходного файла
	hfile = CreateFile("C:\\Users\\nykza\\Documents\\doc.dat", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	lstrcpy(path, "C:\\Users\\nykza\\Documents");
	SearchRec(path);	//Поиск файлов
	DWORD sz = GetFileSize(hfile, NULL);	//получить размер сформированного файла
	char* txt = new char[sz + 1];
	SetFilePointer(hfile, 0, NULL, SEEK_SET);	//прочитать его
	ReadFile(hfile, txt, sz, &rd, NULL);
	txt[sz] = 0;
	cout << txt;	//вывести
	CloseHandle(hfile);	//и закрыть
	delete txt;

	system("pause");
	return 0;
}