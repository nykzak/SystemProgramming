#include<windows.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <Lmcons.h>



using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    char buffer[256];
    char lang[MAX_PATH];
    char currDirect[MAX_PATH];
    char winpath[MAX_PATH + 3];
    char sys[MAX_PATH];
    unsigned long size = 256;
    const int BUFSIZE = 100;
    char bufferZ[BUFSIZE];
    int n;
    char dd[4];

    DWORD verLang = sizeof(lang);
    TCHAR name[UNLEN + 1];
    DWORD sizeS = UNLEN + 1;
    DWORD nS = GetLogicalDriveStrings(BUFSIZE, bufferZ);
    DWORD i = 0;
    TIME_ZONE_INFORMATION tZone;
    SYSTEMTIME lt = { 0 };
    DWORD dr = GetLogicalDrives();
    ULARGE_INTEGER free;
    TCHAR Drive[] = ("A:\\");

    GetComputerName(buffer, &size);
    VerLanguageName(GetUserDefaultLangID(), lang, verLang);
    GetLocalTime(&lt);
    GetTimeZoneInformation(&tZone);
    GetCurrentDirectory(sizeof(currDirect), currDirect);
    GetUserName((TCHAR*)name, &sizeS);
    GetWindowsDirectory(winpath, sizeof(winpath));
    GetSystemDirectory(sys, sizeof(sys));




    cout << "Лабораторная No3 - Сергей Павлов 70982 \n" << endl;

    cout << "Hello, " << name << endl; // Имя пользователя 
    
    printf("%s\n", buffer); //имя компьютера
    printf("Локальное время: %02d:%02d:%02d",
        lt.wHour, lt.wMinute, lt.wSecond); //локальное время 
    cout << "   |  Часовой пояс: "<< tZone.Bias / 60 * (-1)<< endl; // Временной пояс
    cout << "Язык пользователя: " << lang << endl; //Язык компьютера заданный пользователям
    cout << currDirect << endl; //Текущая директория проекта
    cout << winpath << endl; // Директория ОС
    cout << sys << endl; // Директория системы 
  


    while (i < nS) { //Вывод типа диска 
        int t = GetDriveType(&bufferZ[i]);
        switch (t) {
        case 0:
            cout << &bufferZ[i] << " Тип диска " << "DRIVE_UNKNOWN " << t << endl; //Тип дисков
            break;
        case 1:
            cout << &bufferZ[i] << " Тип диска " << "DRIVE_NO_ROOT_DIR " << t << endl; 
            break;
        case 2:
            cout << &bufferZ[i] << " Тип диска " << "DRIVE_REMOVABLE " << t << endl; 
            break;
        case 3:
            cout << &bufferZ[i] << " Тип диска " << "DRIVE_FIXED " << t << endl;
            break;
        case 4:
            cout << &bufferZ[i] << " Тип диска " << "DRIVE_REMOTE " << t << endl;
            break;
        case 5:
            cout << &bufferZ[i] << " Тип диска " << "DRIVE_CDROM " << t << endl;
            break;
        case 6:
            cout << &bufferZ[i] << " Тип диска " << "DRIVE_RAMDISK " << t << endl;
            break;
        default:
            cout << "С вашим диском что-то не так"<< endl;
        }
        
        i += strlen(&bufferZ[i]) + 1;
    }
  
    for (int i = 0; i < 26; i++) // Доступные диски и свободное место в байтах
    {
        n = ((dr >> i) & 0x00000001);
        if (n == 1 && dr & (1 << i))
        {
            Drive[0] = ('A') + i;
            GetDiskFreeSpaceEx(Drive, &free, NULL, NULL);
            dd[0] = char(65 + i); dd[1] = ':'; dd[2] = '\\'; dd[3] = 0;
            cout << "Доступные диски : " << dd << " | Свободного места в байтах : " << free.QuadPart << endl;
        }
    }



    system("pause");
    return 0;
}











