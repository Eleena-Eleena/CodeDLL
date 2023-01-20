#include <Windows.h>
#include <stdio.h>
#include <math.h>

#define n 100000
#define PATHDll L"DLL.dll"
#define PATHUser L"D:\\Study\\Myxin\\С\\CodeDLL\\x64\\Debug\\users.csv"
#define PATHSearchUser L"D:\\Study\\Myxin\\С\\CodeDLL\\x64\\Debug\\searchusers.csv"
#define PATHSearchUserIvan L"D:\\Study\\Myxin\\С\\CodeDLL\\x64\\Debug\\searchusersivan.csv"
#define COUNT 50000 * sizeof(WCHAR)

BOOL WINAPI DllMain(HINSTANCE hIntsDll, DWORD dwReason, LPVOID IpReserved)
{
	BOOL bAllWentWell = TRUE;
	switch (dwReason)
	{case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	if (bAllWentWell)
		return TRUE;
	else
		return FALSE;
}
//extern "C" __declspec(dllimport) int Summ(int a, int b);

extern "C" __declspec(dllimport) void CleanBuffer(LPWSTR buffer);
extern "C" __declspec(dllimport) void CleanBuffer1();
extern "C" __declspec(dllimport) BOOL Containts(wchar_t param1, wchar_t param2);
extern "C" __declspec(dllimport) int Search(int k, LPWSTR search);
extern "C" __declspec(dllimport) float SearchSrYear(int number);
extern "C" __declspec(dllimport) float SearchSrYearInan(int number);
extern "C" __declspec(dllimport) LPWSTR AddBuffer(LPWSTR buffer);
extern "C" __declspec(dllimport) int ReadFileCSV();
extern "C" __declspec(dllimport) int add(LPWSTR buffer1, LPWSTR addbuffer2, int d, char ch);
extern "C" __declspec(dllimport) void WriteFileCSV(int k);
extern "C" __declspec(dllimport) void WriteFileCSV1(int k, float SrYI);

struct user
{
	LPWSTR surname;
	LPWSTR name;
	LPWSTR othername;
	LPWSTR year;
};


struct user arrusers[n];
struct user buf[n];
void CleanBuffer(LPWSTR buffer)
{
	int a = wcslen(buffer);
	for (int i = 0; i < a; i++)
	{
		buffer[i] = '\0';
	}
}
void CleanBuffer1()
{
	int num = 100;
	for (int i = 0; i < num; i++)
	{
		buf[i].surname = (LPWSTR)'\0';
		buf[i].name = (LPWSTR)'\0';
		buf[i].othername = (LPWSTR)'\0';
		buf[i].year = (LPWSTR)'\0';
	}
}

BOOL Containts(wchar_t param1, wchar_t param2)
{
	if (param1 == param2)
	{
		return TRUE;
	}
	return FALSE;
}
int Search(int k, LPWSTR search)
{
	int j = 0;
	int ll = 0;
	CleanBuffer((LPWSTR)buf);
	int r = wcslen(search);

	for (int i = 0; i < k; i++)
	{
		int m = 0;
		int l = wcslen(arrusers[i].surname);
		for (int t = 0; t < l; t++)
		{
			wchar_t w = (wchar_t)search[m];
			wchar_t ww = (wchar_t)(arrusers[i].surname[t]);
			if (Containts(w, ww))
			{
				m++;
				continue;
			}
			else if (m == r)
			{
				break;
			}
			else
			{
				m = 0;
			}
		}
		if (r == m)
		{
			buf[j] = arrusers[i];
			j++;
			ll++;
		}
	}
	return ll;
}
float SearchSrYear(int number)
{
	int y = 0;
	float sr = 0;
	CleanBuffer1();
	for (int i = 0; i < number; i++)
	{
		buf[i] = arrusers[i];
	}
	for (int i = 0; i < number; i++)
	{
		y += _wtoi(buf[i].year);
	}
	sr = (float)y / number;
	return sr;
}
float SearchSrYearInan(int number)
{
	int y = 0;
	float sr = 0;
	for (int i = 0; i < number; i++)
	{
		y += _wtoi(buf[i].year);
	}
	sr = (float)y / number;
	return sr;
}
LPWSTR AddBuffer(LPWSTR buffer)
{
	LPWSTR b = (LPWSTR)calloc(COUNT, sizeof(WCHAR));
	int a = wcslen(buffer);
	for (int i = 0; i < a; i++)
	{
		b[i] = buffer[i];
	}
	return b;
}
int ReadFileCSV()
{
	HANDLE hFile = CreateFileW(PATHUser,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	OVERLAPPED olf = { 0 };
	olf.Offset = 0;
	DWORD ActualCount = 0;
	LPWSTR BufferRead = (LPWSTR)calloc(COUNT, sizeof(WCHAR));
	LPWSTR Buffer = (LPWSTR)calloc(COUNT, sizeof(WCHAR));
	char* surname = (char*)"";
	char* name = (char*)"";
	char* othername = (char*)"";
	char* year = (char*)"";
	int j = 0, k = 0;

	if (!ReadFile(hFile, BufferRead, COUNT, &ActualCount, &olf))
	{
		MessageBox(NULL, L"Произошла ошибка", L"Ошибка", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"Чтение данных завершено", L"Результат", MB_OK);
		int a = wcslen(BufferRead);


		for (int i = 0; i < a; i++)
		{
			if (BufferRead[i] == NULL || BufferRead[i] == ' ' || BufferRead[i] == 65279 || BufferRead[i] == '\r')
			{
				continue;
			}
			else if (BufferRead[i] == ';' || BufferRead[i] == '\n')
			{
				if (surname == "")
				{
					surname = (char*)AddBuffer(Buffer);
					CleanBuffer(Buffer);
					j = 0;
				}
				else if (name == "")
				{
					name = (char*)AddBuffer(Buffer);
					CleanBuffer(Buffer);
					j = 0;
				}
				else if (othername == "")
				{
					othername = (char*)AddBuffer(Buffer);
					CleanBuffer(Buffer);
					j = 0;
				}
				else if (year == "")
				{
					year = (char*)AddBuffer(Buffer);
					CleanBuffer(Buffer);
					struct user user = { (LPWSTR)surname, (LPWSTR)name, (LPWSTR)othername, (LPWSTR)year };
					arrusers[k] = user;
					surname = (char*)"", name = (char*)"", othername = (char*)"", year = (char*)"";
					k++;
					j = 0;
				}
			}
			else
			{
				Buffer[j] = BufferRead[i];
				j++;
			}
		}
	}
	olf.Offset = ActualCount;
	CloseHandle(hFile);
	return k;
}
int add(LPWSTR buffer1, LPWSTR addbuffer2, int d, char ch)
{
	int a = wcslen(addbuffer2);
	for (int i = 0; i < a; i++)
	{
		buffer1[d] = addbuffer2[i];
		d++;
	}
	buffer1[d] = ch;
	d++;
	return d;
}
void WriteFileCSV(int k)
{
	HANDLE hFile = CreateFile(PATHSearchUser,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	OVERLAPPED olf = { 0 };
	olf.Offset = 0;
	LPWSTR mesinfo = (LPWSTR)malloc(COUNT);
	char* mes = (char*)"";
	LPWSTR mesinfo1 = (LPWSTR)malloc(COUNT);
	DWORD number = 0;
	DWORD ActualCount = 0;
	int d = 0;
	for (int i = 0; i < k; i++)
	{
		mes = (char*)buf[i].surname;
		d = add(mesinfo, (LPWSTR)mes, d, ';');
		mes = (char*)buf[i].name;
		d = add(mesinfo, (LPWSTR)mes, d, ';');
		mes = (char*)buf[i].othername;
		d = add(mesinfo, (LPWSTR)mes, d, ';');
		mes = (char*)buf[i].year;
		d = add(mesinfo, (LPWSTR)mes, d, '\n');
	}
	number = d * 2;
	LPCTSTR Bufferwrite = mesinfo;
	WriteFile(hFile, Bufferwrite, number, &ActualCount, &olf);

	LPWSTR BufferRead = (LPWSTR)calloc(COUNT, sizeof(WCHAR));
	if (!ReadFile(hFile, BufferRead, COUNT, &ActualCount, &olf))
	{
		MessageBox(NULL, L"Произошла ошибка", L"Ошибка", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"Добавление прошло успешно", L"Результат", MB_OK);
	}
	olf.Offset = ActualCount;
	CloseHandle(hFile);
}
void WriteFileCSV1(int k, float SrYI)
{
	HANDLE hFile = CreateFile(PATHSearchUserIvan,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	OVERLAPPED olf = { 0 };
	olf.Offset = 0;
	LPWSTR mesinfo = (LPWSTR)malloc(COUNT);
	char* mes = (char*)"";
	LPWSTR mesinfoI = (LPWSTR)malloc(COUNT);
	LPWSTR mesinfo1 = (LPWSTR)malloc(COUNT);
	DWORD number = 0;
	DWORD ActualCount = 0;
	int d = 0;
	for (int i = 0; i < k; i++)
	{
		mes = (char*)buf[i].surname;
		d = add(mesinfo, (LPWSTR)mes, d, ';');
		mes = (char*)buf[i].name;
		d = add(mesinfo, (LPWSTR)mes, d, ';');
		mes = (char*)buf[i].othername;
		d = add(mesinfo, (LPWSTR)mes, d, ';');
		mes = (char*)buf[i].year;
		d = add(mesinfo, (LPWSTR)mes, d, '\n');
	}
	swprintf(mesinfoI, COUNT, L"Средний возраст Ивановых: %f", SrYI);
	d = add(mesinfo, mesinfoI, d, '\n');
	number = d * 2;
	LPCTSTR Bufferwrite = mesinfo;
	WriteFile(hFile, Bufferwrite, number, &ActualCount, &olf);

	LPWSTR BufferRead = (LPWSTR)calloc(COUNT, sizeof(WCHAR));
	if (!ReadFile(hFile, BufferRead, COUNT, &ActualCount, &olf))
	{
		MessageBox(NULL, L"Произошла ошибка", L"Ошибка", MB_OK);
	}
	else
	{
		MessageBox(NULL, L"Добавление прошло успешно", L"Результат", MB_OK);
	}
	olf.Offset = ActualCount;
	CloseHandle(hFile);
}


