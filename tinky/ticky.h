#pragma once

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
#include "sample.h"

#define SVCNAME TEXT("ticky")
#define EXECNAME TEXT("winky")

#define CLOSESERVICE(service) CloseServiceHandle(service)

extern SERVICE_STATUS			gSvcStatus;
extern SERVICE_STATUS_HANDLE	gSvcStatusHandle;
extern HANDLE					ghSvcStopEvent;
extern DWORD					eventId;

// Options
void	SvcInstall(SC_HANDLE& scm, TCHAR* path);
DWORD	SvcStart(SC_HANDLE scm, char* path);
DWORD	SvcStop(SC_HANDLE scm);
DWORD	SvcDelete(SC_HANDLE scm);


// Process
void	createProcess(const char* arg);
DWORD	findProcessById(const char* svcName);
void	killProcessById(DWORD pid);

// Service
VOID	writeLogsToFile(const std::wstring& logMessage);
void	LogEvent(const TCHAR* source, DWORD dwEventID, WORD wType, const char* pMessage);
VOID	WINAPI SvcCtrlHandler(DWORD dwCtrl);
VOID	WINAPI SvcMain(DWORD argc, LPTSTR* argv);
VOID	svcInit(DWORD argc, LPTSTR* argv);
VOID	ReportSvcStatus(DWORD currentState, DWORD win32ExitCode, DWORD waitHint);

// Manage error service
void	startServiceManageError(DWORD err);
void	controlServiceManageError(DWORD err);
void	queryServiceStatusExManageError(DWORD err);
void	openServiceManageError(DWORD err);
void	createServiceManageError(DWORD err);
void	deleteServiceManageError(DWORD err);
