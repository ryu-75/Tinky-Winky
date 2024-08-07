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

#define SVCNAME TEXT("tinky")
#define EXECNAME TEXT("winky")

#define CLOSESERVICE(service) CloseServiceHandle(service)


extern SERVICE_STATUS			gSvcStatus;
extern SERVICE_STATUS_HANDLE	gSvcStatusHandle;
extern HANDLE					ghSvcStopEvent;

// Options
DWORD	SvcInstall(SC_HANDLE& scm, TCHAR* path);
DWORD	SvcStart(SC_HANDLE scm, char* path);
DWORD	SvcStop(SC_HANDLE scm);
VOID	writeLogsToFile(const std::wstring& logMessage);

// Process
void	createProcess(const char* arg);
DWORD	findProcessById(const char* svcName);
void	killProcessById(DWORD pid);

// Service
VOID	writeLogsToFile(const std::wstring& logMessage);
VOID	WINAPI svcCtrlHandler(DWORD dwCtrl);
VOID	WINAPI svcMain(DWORD argc, LPTSTR* argv);
VOID	svcInit(DWORD argc, LPTSTR* argv);
VOID	ReportSvcStatus(DWORD currentState, DWORD win32ExitCode, DWORD waitHint);
#endif