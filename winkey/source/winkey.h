#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <strsafe.h>

//#define NUMHOOKS 7
//#define EXECNAME TEXT("winkey")

typedef struct _MYHOOKDATA
{
	int	nType;
	HOOKPROC	hookProc;
	HHOOK		hhook;
}	MYHOOKDATA;

using namespace std;

