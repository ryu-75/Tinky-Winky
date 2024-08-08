#include "../ticky.h"

DWORD	SvcInstall(SC_HANDLE& scm, TCHAR* path)
{
	SC_HANDLE	schService;

	// Create the service
	schService = CreateService(
		scm,						// SCM Database
		SVCNAME,					// name of service
		SVCNAME,					// service name to display
		SERVICE_ALL_ACCESS,			// desired access
		SERVICE_WIN32_OWN_PROCESS,	// service type
		SERVICE_DEMAND_START,		// start type
		SERVICE_ERROR_NORMAL,		// error control type
		path,						// path to service's binary
		NULL,						// no load ordering group
		NULL,						// no tag identifier
		NULL,						// no dependencies
		NULL,						// LocalSystem account
		NULL);						// no password

	if (schService == NULL)
	{
		printf("%d: Service is already installed\n", GetLastError());
		LogEvent(SVCNAME, SVC_ALREADY_INSTALLED, EVENTLOG_INFORMATION_TYPE, TEXT("Info: The service is already installed."));
		CLOSESERVICE(scm);
		return 0;
	}

	printf("Service installed successfully\n");
	LogEvent(SVCNAME, SVC_INSTALLED_SUCCESS, EVENTLOG_SUCCESS, TEXT("Success: Ticky service started correctly."));
	
	CLOSESERVICE(schService);
	CLOSESERVICE(scm);
	return 1;
}

DWORD	SvcStart(SC_HANDLE scm, char* path) {
	SC_HANDLE	schService;
	SERVICE_STATUS_PROCESS	ssStatus = { 0 };
	DWORD dwBytesNeeded;
	DWORD	err;

	schService = OpenService(
		scm,				// SCM Database
		SVCNAME,			// name of service
		SERVICE_ALL_ACCESS	// full access
	);

	if (!schService)
	{
		printf("Service is not installer\n");
		LogEvent(SVCNAME, SVC_STARTED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: Service is not installed"));
		return 0;
	}

	const char* arg[] = { path };

	// Attempt to start the service
	if (!StartService(schService, 1, arg))
	{
		err = GetLastError();

		if (err == ERROR_SERVICE_ALREADY_RUNNING)
		{
			printf("The service is already running\n");
			LogEvent(SVCNAME, SVC_ALREADY_STARTED, EVENTLOG_INFORMATION_TYPE, TEXT("Info: The service is already started."));
		}
		else
		{
			printf("%d: Start or control request not respond\n", GetLastError());
			LogEvent(SVCNAME, SVC_STARTED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: The service could not be started."));
		}
		CLOSESERVICE(schService);
		CLOSESERVICE(scm);
		return 0;
	}
	if (QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
	{
		printf("Service %s started correctly\n", SVCNAME);
		LogEvent(SVCNAME, SVC_STARTED_SUCCESS, EVENTLOG_INFORMATION_TYPE, TEXT("Success: Ticky service started correctly."));
	}
	else
	{
		err = GetLastError();
		printf("QueryServiceStatusEx failed (%d)\n", err);
		LogEvent(SVCNAME, SVC_STARTED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: QueryServiceStatusEx failed."));
		CLOSESERVICE(schService);
		CLOSESERVICE(scm);
		return 0;
	}
	CLOSESERVICE(schService);
	CLOSESERVICE(scm);
	return 1;
}

// NEED TO BE REVIEW
DWORD	SvcStop(SC_HANDLE scm)
{
	SERVICE_STATUS_PROCESS	ssp = { 0 };
	SC_HANDLE	schService;
	DWORD	dwBytesNeeded;

	schService = OpenService(
		scm,
		SVCNAME,
		SERVICE_STOP | SERVICE_QUERY_STATUS | SERVICE_ENUMERATE_DEPENDENTS
	);

	if (!schService)
	{
		printf("%d: The service doesn't exist\n", GetLastError());
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: Service is not installed"));
	}

	if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
	{
		printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: QueryServiceStatusEx failed"));
		CLOSESERVICE(scm);
		CLOSESERVICE(schService);
		return 0;
	}
	if (ssp.dwCurrentState == SERVICE_STOPPED)
	{
		printf("Service is already stopped\n");
		LogEvent(SVCNAME, SVC_ALREADY_STOPPED, EVENTLOG_INFORMATION_TYPE, TEXT("Info: The service is already stop."));
		CLOSESERVICE(scm);
		CLOSESERVICE(schService);
		return 0;
	}

	if (!ControlService(
		schService,
		SERVICE_CONTROL_STOP,
		(LPSERVICE_STATUS)&ssp))
	{
		printf("ControlService failed (%d)\n", GetLastError());
		CLOSESERVICE(scm);
		CLOSESERVICE(schService);
		return 0;
	}

	while (ssp.dwCurrentState != SERVICE_STOPPED)
	{
		if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
		{
			printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
			LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Error: QueryServiceStatusEx failed"));
			CLOSESERVICE(scm);
			CLOSESERVICE(schService);
			return 0;
		}
		if (ssp.dwCurrentState == SERVICE_STOPPED)
			break;
	}
	printf("Service stopped successfully\n");
	LogEvent(SVCNAME, SVC_STOPPED_SUCCESS, EVENTLOG_INFORMATION_TYPE, TEXT("Success: Service stopped correctly."));
	return 1;
}

VOID	WINAPI SvcDelete();