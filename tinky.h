#ifndef TICKY_H
#define TICKY_H

#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Shlwapi.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <tlhelp32.h>

#define SVCNAME TEXT("svc")

extern SERVICE_STATUS			gSvcStatus;
extern SERVICE_STATUS_HANDLE	gSvcStatusHandle;
extern HANDLE					ghSvcStopEvent;

VOID	SvcInstall(SC_HANDLE &scm, TCHAR* path);
VOID	writeLogsToFile(const std::wstring& logMessage);
void	createProcess(const char* arg);

VOID WINAPI	svcCtrlHandler(DWORD dwCtrl);
VOID WINAPI	svcMain(DWORD argc, LPTSTR* argv);
VOID	svcInit(DWORD argc, LPTSTR* argv);
#endif