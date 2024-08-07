#include "../tinky.h"

void	findProcessById(TCHAR svcName)
{
	HANDLE	hSnapshot;
	PROCESSENTRY32	processEntry;
	BOOL	hResult;

	// snapshot of all processes in the system
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot) 
		return;

	// initializing size: needed for using Process32First
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	// info about first process encountered in a system snapshot
	hResult = sizeof(PROCESSENTRY32);

	// infor about first process encoutered in a system snapshot
}

void	createProcess(const char* arg)
{
	STARTUPINFO	si;
	PROCESS_INFORMATION	pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcess(
		NULL,				// No module name (use command line)
		(LPSTR)arg,		// Command line
		NULL,				// Process handle not inheritable
		NULL,				// Thread handle not inheritable
		FALSE,				// Set handle inheritance to FALSE
		0,					// No creation flags
		NULL,				// Use parent's environment block
		NULL,				// Use parent's starting directory
		&si,				// Pointer to STARTUPINFO structure
		&pi					// Pointe to PROCESS_INFORMATION structure
	))
	{
		printf("CreateProcess failed %d\n", GetLastError());
		return;
	}

	// Wait until child process exits
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

VOID WINAPI	svcCtrlHandler(DWORD dwCtrl)
{
	switch (dwCtrl)
	{
	case SERVICE_CONTROL_STOP:
		// Add reportServiceStatus
		printf("HEY\n");
		return;
	}
}

VOID WINAPI	svcMain(DWORD argc, LPTSTR* argv) {
	// Register the handler function for the service

	SERVICE_STATUS_HANDLE	gSvcStatusHandle = RegisterServiceCtrlHandler(
		SVCNAME,
		NULL
	);

	if (!gSvcStatusHandle)
	{
		printf("Service Status Handle failed (%d)\n", GetLastError());
		return;
	}

	gSvcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	gSvcStatus.dwServiceSpecificExitCode = 0;

	svcInit(argc, argv);
}

VOID	svcInit(DWORD argc, LPTSTR* argv) {
	HANDLE	ghSvcStopEvent;
	
	ghSvcStopEvent = CreateEvent(
		NULL,	// default security attributes
		TRUE,	// manual reset event
		FALSE,	// not signaled
		NULL	// no name
	);

	if (!ghSvcStopEvent)
	{
		// reportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
		return;
	}

	// ReportSvcStatus(SERVICE_RUNNING, NO_ERROR, 0);

	while (1)
	{
		// Check whether to stop the service
		WaitForSingleObject(ghSvcStopEvent, INFINITE);
		// reportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
		return;
	}
}