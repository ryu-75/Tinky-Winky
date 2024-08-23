#include "../ticky.h"

void	SvcInstall(SC_HANDLE& scm, TCHAR* path)
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
		createServiceManageError(GetLastError());
		CLOSESERVICE(scm);
		return;
	}

	printf("Service installed successfully\n");
	LogEvent(SVCNAME, SVC_INSTALLED_SUCCESS, EVENTLOG_SUCCESS, TEXT("Success: Ticky service started correctly."));
	
	CLOSESERVICE(schService);
	CLOSESERVICE(scm);
	return;
}

DWORD	SvcStart(SC_HANDLE scm, char* path) {
	SC_HANDLE	schService;
	SERVICE_STATUS_PROCESS	ssStatus = { 0 };
	DWORD dwBytesNeeded;

	schService = OpenService(
		scm,				// SCM Database
		SVCNAME,			// name of service
		SERVICE_ALL_ACCESS	// full access
	);

	if (!schService)
	{
		openServiceManageError(GetLastError());
		CLOSESERVICE(scm);
		return 0;
	}

	const char* arg[] = { path };

	// Attempt to start the service
	if (!StartService(schService, 1, arg))
	{
		startServiceManageError(GetLastError());
		CLOSESERVICE(schService);
		CLOSESERVICE(scm);
		return 0;
	}
	if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssStatus, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
	{
		queryServiceStatusExManageError(GetLastError());
		CLOSESERVICE(schService);
		CLOSESERVICE(scm);
		return 0;
	}
	printf("Service %s started correctly\n", SVCNAME);
	LogEvent(SVCNAME, SVC_STARTED_SUCCESS, EVENTLOG_INFORMATION_TYPE, TEXT("Success: Service ticky started correctly."));
	CLOSESERVICE(schService);
	CLOSESERVICE(scm);
	return 1;
}

DWORD	SvcStop(SC_HANDLE scm)
{
	SERVICE_STATUS_PROCESS	ssp = { 0 };
	SC_HANDLE	schService;
	DWORD	dwBytesNeeded;

	// Get a handle to the service

	schService = OpenService(scm, SVCNAME, SERVICE_STOP | SERVICE_QUERY_STATUS | SERVICE_ENUMERATE_DEPENDENTS);

	if (!schService)
	{
		openServiceManageError(GetLastError());
		CLOSESERVICE(scm);
		return 0;
	}
	if (!ControlService(schService, SERVICE_CONTROL_STOP, (LPSERVICE_STATUS)&ssp))
	{
		controlServiceManageError(GetLastError());
		CLOSESERVICE(scm);
		CLOSESERVICE(schService);
		return 0;
	}
	
	// Check is service is already stopped
	if (ssp.dwCurrentState == SERVICE_STOP)
	{
		printf("%d: Service is already stopped.\n", GetLastError());
		LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Service is already stopped."));
		CLOSESERVICE(scm);
		CLOSESERVICE(schService);
		return 0;
	}

	// Stop the service

	do
	{
		Sleep(1000);
		if (!QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded))
		{
			queryServiceStatusExManageError(GetLastError());
			CLOSESERVICE(scm);
			CLOSESERVICE(schService);
			return 0;
		}

		switch (ssp.dwCurrentState)
		{
		case SERVICE_STOP_PENDING:
			continue;
		case SERVICE_STOPPED:
			break;
		case SERVICE_RUNNING:
			printf("%d: Service is currently running\n", ssp.dwCurrentState);
			LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Service is currently running"));
			break;
		case SERVICE_START_PENDING:
			printf("%d: Service start pending\n", ssp.dwCurrentState);
			LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Service start pending"));
			break;
		case SERVICE_CONTINUE_PENDING:
			printf("Service is in state %d waiting...\n", ssp.dwCurrentState);
			LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_INFORMATION_TYPE, TEXT("Service continue pending"));
			break;
		default:
			printf("Unexpected service state detected: %d\n", ssp.dwCurrentState);
			LogEvent(SVCNAME, SVC_STOPPED_ERROR, EVENTLOG_ERROR_TYPE, TEXT("Unexpected service state detected"));
			CLOSESERVICE(schService);
			CLOSESERVICE(scm);
			return 0;
		}

	} while (ssp.dwCurrentState != SERVICE_STOPPED);

	printf("Service stopped successfully\n");
	LogEvent(SVCNAME, SVC_STOPPED_SUCCESS, EVENTLOG_INFORMATION_TYPE, TEXT("Success: Service stopped correctly."));
	CLOSESERVICE(scm);
	CLOSESERVICE(schService);
	return 1;
}

DWORD	SvcDelete(SC_HANDLE scm)
{
	SC_HANDLE	schService;
	SERVICE_STATUS	ssStatus;

	// Get a handle to the service

	schService = OpenService(
		scm,		// SCM database
		SVCNAME,	// Name of service
		DELETE		// need a delete access
	);

	if (!schService)
	{
		openServiceManageError(GetLastError());
		CLOSESERVICE(scm);
		return 0;
	}

	// Delete the service

	if (!DeleteService(schService))
	{
		deleteServiceManageError(GetLastError());
		CLOSESERVICE(scm);
		CLOSESERVICE(schService);
		return 0;
	}
	printf("Service deleted successfully\n");
	LogEvent(SVCNAME, SVC_DELETED_SUCCESS, EVENTLOG_INFORMATION_TYPE, TEXT("Success: Service deleted correctly"));
	CLOSESERVICE(scm);
	CLOSESERVICE(schService);
	return 1;
}