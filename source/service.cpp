#include "../tinky.h"

VOID	writeLogsToFile(const std::wstring& logMessage)
{
	OutputDebugStringW(logMessage.c_str());
}

VOID	WINAPI svcCtrlHandler(DWORD dwCtrl)
{
	switch (dwCtrl)
	{
	case SERVICE_CONTROL_STOP:
		gSvcStatus.dwCurrentState = SERVICE_STOP_PENDING;
		killProcessById(findProcessById(EXECNAME));
		SetServiceStatus(gSvcStatusHandle, &gSvcStatus);
		SetEvent(ghSvcStopEvent);
		ReportSvcStatus(SERVICE_STOP, NO_ERROR, 0);
		return;
	case SERVICE_ACCEPT_PRESHUTDOWN:
		ReportSvcStatus(SERVICE_CONTROL_PRESHUTDOWN, NO_ERROR, 0);
		return;
	default:
		break;
	}
	SetServiceStatus(gSvcStatusHandle, &gSvcStatus);
}

VOID	WINAPI svcMain(DWORD argc, LPTSTR* argv) {
	// Register the handler function for the service
	printf("Service is starting...");
	gSvcStatusHandle = RegisterServiceCtrlHandler(
		SVCNAME,
		svcCtrlHandler
	);

	if (!gSvcStatusHandle)
	{
		printf("Service Status Handle failed (%d)\n", GetLastError());
		return ;
	}

	// Initialize service status
	gSvcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	gSvcStatus.dwServiceSpecificExitCode = 0;
	gSvcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	gSvcStatus.dwCurrentState = SERVICE_START_PENDING;
	gSvcStatus.dwWin32ExitCode = NO_ERROR;
	gSvcStatus.dwCheckPoint = 0;
	gSvcStatus.dwWaitHint = 3000;
	
	if (!SetServiceStatus(gSvcStatusHandle, &gSvcStatus))
	{
		printf("SetService failed\n");
		return ;
;	}
	
	ghSvcStopEvent = CreateEvent(
		NULL,	// default security attributes
		TRUE,	// manual reset event
		FALSE,	// not signaled
		NULL	// no name
	);

	if (!ghSvcStopEvent)
	{
		ReportSvcStatus(SERVICE_STOPPED, GetLastError(), 0);
		return ;
	}

	ReportSvcStatus(SERVICE_RUNNING, NO_ERROR, 0);

	WaitForSingleObject(ghSvcStopEvent, INFINITE);

	ReportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
	return ;
}

VOID	ReportSvcStatus(DWORD currentState, DWORD win32ExitCode, DWORD waitHint)
{
	static DWORD checkPoint = 1;

	// Fill in the SERVICE_STATUS structure

	gSvcStatus.dwCurrentState = currentState;
	gSvcStatus.dwWin32ExitCode = win32ExitCode;
	gSvcStatus.dwWaitHint = waitHint;

	if (currentState == SERVICE_START_PENDING)
		gSvcStatus.dwControlsAccepted = 0;
	else gSvcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;

	if ((currentState == SERVICE_RUNNING) ||
		(currentState == SERVICE_STOPPED))
		gSvcStatus.dwCheckPoint = 0;
	else gSvcStatus.dwCheckPoint = checkPoint++;

	// Report the status of the service to the SCM
	SetServiceStatus(gSvcStatusHandle, &gSvcStatus);
}