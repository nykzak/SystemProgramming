#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");//русская локаль
	int ikey;
	//выбираем корневой ключ
	cout << "Лабораторная No5 - Сергей Павлов 70982 \n" << endl;
	cout << "Выберите корневой ключ:" << endl;
	cout << "1 - HKEY_CLASSES_ROOT" << endl;
	cout << "2 - HKEY_CURRENT_CONFIG" << endl;
	cout << "3 - HKEY_CURRENT_USER" << endl;
	cout << "4 - HKEY_LOCAL_MACHINE" << endl;
	cout << "5 - HKEY_USERS" << endl;
	cin >> ikey;
	HKEY root;
	//сопоставляем введенному числу корневой ключ
	switch (ikey)
	{
	case 1:
		root = HKEY_CLASSES_ROOT;
		break;
	case 2:
		root = HKEY_CURRENT_CONFIG;
		break;
	case 3:
		root = HKEY_CURRENT_USER;
		break;
	case 4:
		root = HKEY_LOCAL_MACHINE;
		break;
	case 5:
		root = HKEY_USERS;
		break;
	default:
		root = NULL;
		break;
	}
	if (root != NULL)	//если номер ключа введен верно
	{
		char key[256];
		cin.get();
		cout << "Введите ключ реестра: ";
		cin.getline(key, 256);		//ввод ключа
		HKEY hkey;

		//открытие ключа реестра
		if (!RegOpenKeyEx(HKEY_CLASSES_ROOT, key, NULL, KEY_QUERY_VALUE, &hkey) || 
			!RegOpenKeyEx(HKEY_CURRENT_USER, key, NULL, KEY_QUERY_VALUE, &hkey) || 
			!RegOpenKeyEx(HKEY_LOCAL_MACHINE, key, NULL, KEY_QUERY_VALUE, &hkey) || 
			!RegOpenKeyEx(HKEY_USERS, key, NULL, KEY_QUERY_VALUE, &hkey) ||
			!RegOpenKeyEx(HKEY_CURRENT_CONFIG, key, NULL, KEY_QUERY_VALUE, &hkey))
		{
			DWORD nval=0, maxvalnamelen, maxvallen, cchValueName, dwType, cbdata;
			//Запросить информацию об открытом ключе
			RegQueryInfoKey(hkey, NULL, NULL, NULL, NULL, NULL, NULL, &nval, &maxvalnamelen, &maxvallen, NULL, NULL);
			if (nval > 0)	//если в ключе есть переменные
			{
				char *ValueName = new char[maxvalnamelen];	//выделеяем память	под имена
				BYTE *value = new BYTE[maxvallen];			//и значения
				cout << setfill('0');
				for (int idx = 0; idx < nval; idx++)		//вывод значений
				{
					cbdata = maxvallen;				//инициализировать длины полей
					cchValueName = maxvalnamelen;
					//запрос информации об очередной переменной
					RegEnumValue(hkey, idx, ValueName, &cchValueName, NULL, &dwType, value, &cbdata);
					//вывести ее имя
					cout << "Имя: " << ValueName << endl;
					char *typenam;
					//определить тип
					switch (dwType)
					{
					case REG_BINARY:
						typenam = "REG_BINARY";
						break;
					case REG_FULL_RESOURCE_DESCRIPTOR:
						typenam = "REG_FULL_RESOURCE_DESCRIPTOR";
						break;
					case REG_DWORD:
						typenam = "REG_DWORD";
						break;
					case REG_EXPAND_SZ:
						typenam = "REG_EXPAND_SZ";
						break;
					case REG_SZ:
						typenam = "REG_SZ";
						break;
					case REG_LINK:
						typenam = "REG_LINK";
						break;
					case REG_MULTI_SZ:
						typenam = "REG_MULTI_SZ";
						break;
					case REG_NONE:
						typenam = "REG_NONE";
						break;
					case REG_QWORD:
						typenam = "REG_QWORD";
						break;
					default:
						typenam = "Неизвестный";
						break;
					}
					//вывести тип
					cout << "Тип: " << dwType << "(" << typenam << ")" << endl;
					cout << "Значение: ";
					//вывести значение в зависимости от типа
					switch (dwType)
					{
					case REG_SZ:
					case REG_EXPAND_SZ:		//строки просто выводим
						cout << value << endl;
						break;
					case REG_DWORD:			//двоичные
					{
						unsigned int *d = (unsigned int*)value;
						cout << *d << " (0x" << hex << *d << dec << ")" << endl;
						break;
					}
					case REG_QWORD:			//двоичные
					{
						__int64  *d = (__int64*)value;
						cout << *d << " (0x" << hex << *d << dec << ")" << endl;
						break;
					}
					default:		//а все остальные представляем как 16-ричные данные
					{
						for (int i = 0; i < cbdata; i++)
						{
							cout << setw(2) << hex << (int)value[i] << dec <<  " ";
						}
						cout << endl;
					}
					}

					cout << "--------------------------------------------------------------------------" << endl;
				}
				delete ValueName;	//освободить память
				delete value;

			}
			else
				cout << "В данном ключе нет переменных." << endl;
			RegCloseKey(hkey);	//закрыть ключ реестра
		}
		else
		{
			cout << "Не удается открыть указанный ключ реестра" << endl;
		}

	}
	system("pause");
	return 0;
}