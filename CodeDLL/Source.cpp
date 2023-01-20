#include <Windows.h>
#include <stdio.h>
#include <math.h>

#define n 100000
#define PATHDll L"DLL.dll"
#define PATHUser L"D:\\Study\\Myxin\\С\\CodeDLL\\x64\\Debug\\users.csv"
#define PATHSearchUser L"D:\\Study\\Myxin\\С\\CodeDLL\\x64\\Debug\\searchusers.csv"
#define COUNT 50000 * sizeof(WCHAR)

typedef int(_cdecl* MyFunReadFile)();
typedef int(_cdecl* MyFunSeachSur)(int, LPWSTR);
typedef void(_cdecl* MyFunWrite)(int);
typedef void(_cdecl* MyFunWrite1)(int, float);
typedef float(_cdecl* MyFunSrY)(int);
typedef float(_cdecl* MyFunSrYInan)(int);


int WINAPI WinMain(HINSTANCE hIntstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	HINSTANCE hMyDll;
	if ((hMyDll = LoadLibrary(PATHDll)) == NULL) return 1;
	MyFunReadFile myfunread = (MyFunReadFile)GetProcAddress(hMyDll, "ReadFileCSV");
	int lenght = myfunread();
	int lenght1 = lenght;
	LPWSTR search = calloc(COUNT, sizeof(WCHAR));
	search = L"Яш";
	MyFunSeachSur myfunSearch = (MyFunSeachSur)GetProcAddress(hMyDll, "Search");
	lenght = myfunSearch(lenght, search);
	MyFunWrite myfunWrite = (MyFunWrite)GetProcAddress(hMyDll, "WriteFileCSV");
	myfunWrite(lenght);
	MyFunSrY myfunsry = (MyFunSrY)GetProcAddress(hMyDll, "SearchSrYear");
	float SrYear = myfunsry(3);
	LPWSTR search1 = calloc(COUNT, sizeof(WCHAR));
	search1 = L"Иванова";
	myfunSearch = (MyFunSeachSur)GetProcAddress(hMyDll, "Search");
	lenght1 = myfunSearch(lenght1, search1);
	MyFunSrYInan myfunsryi = (MyFunSrYInan)GetProcAddress(hMyDll, "SearchSrYearInan");
	float SrYearIvan = myfunsryi(lenght1);
	MyFunWrite1 myfunWrite1 = (MyFunWrite1)GetProcAddress(hMyDll, "WriteFileCSV1");
	myfunWrite1(lenght1, SrYearIvan);

	FreeLibrary(hMyDll);

}