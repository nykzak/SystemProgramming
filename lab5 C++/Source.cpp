#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");//������� ������
	int ikey;
	//�������� �������� ����
	cout << "������������ No5 - ������ ������ 70982 \n" << endl;
	cout << "�������� �������� ����:" << endl;
	cout << "1 - HKEY_CLASSES_ROOT" << endl;
	cout << "2 - HKEY_CURRENT_CONFIG" << endl;
	cout << "3 - HKEY_CURRENT_USER" << endl;
	cout << "4 - HKEY_LOCAL_MACHINE" << endl;
	cout << "5 - HKEY_USERS" << endl;
	cin >> ikey;
	HKEY root;
	//������������ ���������� ����� �������� ����
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
	if (root != NULL)	//���� ����� ����� ������ �����
	{
		char key[256];
		cin.get();
		cout << "������� ���� �������: ";
		cin.getline(key, 256);		//���� �����
		HKEY hkey;

		//�������� ����� �������
		if (!RegOpenKeyEx(HKEY_CLASSES_ROOT, key, NULL, KEY_QUERY_VALUE, &hkey) || 
			!RegOpenKeyEx(HKEY_CURRENT_USER, key, NULL, KEY_QUERY_VALUE, &hkey) || 
			!RegOpenKeyEx(HKEY_LOCAL_MACHINE, key, NULL, KEY_QUERY_VALUE, &hkey) || 
			!RegOpenKeyEx(HKEY_USERS, key, NULL, KEY_QUERY_VALUE, &hkey) ||
			!RegOpenKeyEx(HKEY_CURRENT_CONFIG, key, NULL, KEY_QUERY_VALUE, &hkey))
		{
			DWORD nval=0, maxvalnamelen, maxvallen, cchValueName, dwType, cbdata;
			//��������� ���������� �� �������� �����
			RegQueryInfoKey(hkey, NULL, NULL, NULL, NULL, NULL, NULL, &nval, &maxvalnamelen, &maxvallen, NULL, NULL);
			if (nval > 0)	//���� � ����� ���� ����������
			{
				char *ValueName = new char[maxvalnamelen];	//��������� ������	��� �����
				BYTE *value = new BYTE[maxvallen];			//� ��������
				cout << setfill('0');
				for (int idx = 0; idx < nval; idx++)		//����� ��������
				{
					cbdata = maxvallen;				//���������������� ����� �����
					cchValueName = maxvalnamelen;
					//������ ���������� �� ��������� ����������
					RegEnumValue(hkey, idx, ValueName, &cchValueName, NULL, &dwType, value, &cbdata);
					//������� �� ���
					cout << "���: " << ValueName << endl;
					char *typenam;
					//���������� ���
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
						typenam = "�����������";
						break;
					}
					//������� ���
					cout << "���: " << dwType << "(" << typenam << ")" << endl;
					cout << "��������: ";
					//������� �������� � ����������� �� ����
					switch (dwType)
					{
					case REG_SZ:
					case REG_EXPAND_SZ:		//������ ������ �������
						cout << value << endl;
						break;
					case REG_DWORD:			//��������
					{
						unsigned int *d = (unsigned int*)value;
						cout << *d << " (0x" << hex << *d << dec << ")" << endl;
						break;
					}
					case REG_QWORD:			//��������
					{
						__int64  *d = (__int64*)value;
						cout << *d << " (0x" << hex << *d << dec << ")" << endl;
						break;
					}
					default:		//� ��� ��������� ������������ ��� 16-������ ������
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
				delete ValueName;	//���������� ������
				delete value;

			}
			else
				cout << "� ������ ����� ��� ����������." << endl;
			RegCloseKey(hkey);	//������� ���� �������
		}
		else
		{
			cout << "�� ������� ������� ��������� ���� �������" << endl;
		}

	}
	system("pause");
	return 0;
}