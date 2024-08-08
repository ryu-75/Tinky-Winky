#include "../ticky.h"

VOID	writeLogsToFile(const std::wstring& logMessage)
{
	OutputDebugStringW(logMessage.c_str());
}

void	LogEvent(const TCHAR* source, DWORD dwEventID, WORD wType, const char* pMessage)
{
	HANDLE	hEventLog = RegisterEventSource(NULL, SVCNAME);
	if (hEventLog)
	{
		LPCTSTR messages[] = { pMessage };
		ReportEvent(
			hEventLog, 
			wType,
			0,
			dwEventID, 
			NULL, 
			1, 
			0, 
			messages, 
			NULL
		);
		DeregisterEventSource(hEventLog);
	}
	else
	{
		printf("Failed to regiser event source (%d)\n", GetLastError());
	}
}

VOID	WINAPI SvcCtrlHandler(DWORD dwCtrl)
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

VOID	WINAPI SvcMain(DWORD argc, LPTSTR* argv) {
	// Register the handler function for the service
	gSvcStatusHandle = RegisterServiceCtrlHandler(
		SVCNAME,
		SvcCtrlHandler
	);

	if (!gSvcStatusHandle)
	{
		ReportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
		printf("Service Status Handle failed (%d)\n", GetLastError());
		LogEvent(SVCNAME, SVC_STARTED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: Service Status Handle failed"));
		return ;
	}

	// Initialize service status
	gSvcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	gSvcStatus.dwServiceSpecificExitCode = 0;
	gSvcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	gSvcStatus.dwCurrentState = SERVICE_START_PENDING;
	gSvcStatus.dwWin32ExitCode = NO_ERROR;
	gSvcStatus.dwCheckPoint = 0;
	gSvcStatus.dwWaitHint = 5000;
	
	if (!SetServiceStatus(gSvcStatusHandle, &gSvcStatus))
	{
		ReportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
		printf("SetService failed\n");
		LogEvent(SVCNAME, SVC_STARTED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: SetService failed"));
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
		LogEvent(SVCNAME, SVC_STARTED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: Stop event service initialization failed"));
		return ;
	}

	ReportSvcStatus(SERVICE_RUNNING, NO_ERROR, 0);

	WaitForSingleObject(ghSvcStopEvent, INFINITE);

	ReportSvcStatus(SERVICE_STOPPED, NO_ERROR, 0);
	LogEvent(SVCNAME, SVC_STARTED_SUCCESS, EVENTLOG_INFORMATION_TYPE, TEXT("Success: Ticky service started correctly."));
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