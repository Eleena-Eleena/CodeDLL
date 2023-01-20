#pragma once
#include <Windows.h>

typedef int(_cdecl* MyFunction)(int, int);
struct user
{
	LPWSTR surname;
	LPWSTR name;
	LPWSTR othername;
	LPWSTR year;
};
int ReadFileCSV();
void WriteFileCSV(int k);
void WriteFileCSV1(int k);
void CleanBuffer(LPWSTR buffer);
void CleanBuffer1();
LPWSTR AddBuffer(LPWSTR buffer);
int add(LPWSTR buffer1, LPWSTR addbuffer2, int d, char ch);
BOOL Containts(wchar_t param1, wchar_t param2);
int Search(int k, LPWSTR search);
float SearchSrYear(int number);
float SearchSrYearInan(int number, float SrYI);